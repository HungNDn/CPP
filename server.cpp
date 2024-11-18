#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::tcp;

void saveVideo(const std::string& videoData, std::size_t length) {
    std::ofstream file("1.mp4", std::ios::binary | std::ios::app);
    // std::cout << "Write data to file 1.mp4" << std::endl;
    if (file.is_open()) {
        file.write(videoData.data(), length);
    } else {
        std::cerr << "Failed to open file for writing" << std::endl;
    }
}

class session : public std::enable_shared_from_this<session> {
public:
    session(tcp::socket socket, boost::asio::ssl::context& context)
    : socket_(std::move(socket), context) {}
    tcp::socket& socket() {
        return socket_.next_layer();
    }
    void start() {
        socket_.async_handshake(boost::asio::ssl::stream_base::server,
            boost::bind(&session::handle_handshake, shared_from_this(),
            boost::asio::placeholders::error));
    }
private:
    void handle_handshake(const boost::system::error_code& error) {
        if (!error) {
            boost::asio::async_read_until(socket_, request_, "\r\n\r\n",
                boost::bind(&session::handle_read, shared_from_this(),
                boost::asio::placeholders::error));
        }
    }

    void do_read_body() {
        auto self(shared_from_this());
        boost::asio::async_read(socket_, request_,
            boost::asio::transfer_at_least(1),
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    sum_ = sum_ + length;
                    // Continue reading the request body
                    std::string request_data(boost::asio::buffers_begin(request_.data()),
                                            boost::asio::buffers_end(request_.data()));

                    if(sum_ == content_length_pos_) {
                        sum_ = 0;
                        std::cout << "Full packets of video files have been received" << std::endl;
                        std::string message = "HTTP/1.1 100 OK\r\n";
                        boost::asio::async_write(socket_, boost::asio::buffer(message),
                                boost::bind(&session::handle_write, shared_from_this(),
                                boost::asio::placeholders::error));
                    }

                    if(length != 0) {
                        saveVideo(request_data, length);
                        request_.consume(length);
                        do_read_body();
                    }
                    

                } else if (ec == boost::asio::error::eof) {
                    // End of request body
                    // std::cout << "length: " << length << std::endl;
                }
            });
    }
    void handle_read(const boost::system::error_code& error) {
        if (!error) {
            std::string message = "HTTP/1.1 200 OK\r\n";
            std::string request_data(boost::asio::buffers_begin(request_.data()),
                                    boost::asio::buffers_end(request_.data()));

            // Find the position of the empty line ("\r\n\r\n") to determine the start of the body
            size_t body_start = request_data.find("\r\n\r\n");
            if (body_start != std::string::npos) {
                // Get the headers portion of the request
                std::string headers = request_data;
                // Find the Content-type header
                size_t content_type_pos = headers.find("Content-Type: ");
                // Find the Content-Length header
                size_t content_length_pos = headers.find("Content-Length: ");
                // Find the Expect header
                size_t expect_pos = headers.find("Expect: ");

                if (content_length_pos != std::string::npos) {
                    // Extract the value of the Content-Type header
                    size_t content_type_start = content_type_pos + strlen("Content-Type: ");
                    size_t content_type_end = headers.find("\r\n", content_type_start);
                    std::string content_type_str = headers.substr(content_type_start, content_type_end - content_type_start);
                    std::cout << "content_type_str: " << content_type_str << std::endl;

                    // Extract the value of the Content-Length header
                    size_t content_length_start = content_length_pos + strlen("Content-Length: ");
                    size_t content_length_end = headers.find("\r\n", content_length_start);
                    std::string content_length_str = headers.substr(content_length_start, content_length_end - content_length_start);
                    content_length_pos_ = std::stoi(content_length_str);         
                    std::cout << "content_length_str: " << content_length_str << std::endl;

                    // Extract the value of the Expect: header
                    size_t expect_start = expect_pos + strlen("Expect: ");
                    size_t expect_end = headers.find("\r\n", expect_start);
                    std::string expect_str = headers.substr(expect_start, expect_end - expect_start);
                    std::cout << "expect_str: " << expect_str << std::endl;

                    if(expect_str == "100-continue") {
                        request_.consume(request_data.size());
                        auto self(shared_from_this());
                        boost::asio::async_write(socket_, boost::asio::buffer("HTTP/1.1 100 Continue\r\n\r\n"),
                        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                            if (!ec) {
                                do_read_body();
                            }
                        });
                    } else {
                        std::cout << "request_data: " << request_data << std::endl;
                        std::string message1 = "HTTP/1.1 100 OK\r\n";
                        boost::asio::async_write(socket_, boost::asio::buffer(message1),
                                boost::bind(&session::handle_write, shared_from_this(),
                                boost::asio::placeholders::error));
                    }
                }
            }
        }
    }
    void handle_write(const boost::system::error_code& error) {}
    boost::asio::ssl::stream<tcp::socket> socket_;
    boost::asio::streambuf request_;
    size_t content_length_pos_;
    int sum_ = 0;
};
class server {
public:
    server(boost::asio::io_context& io_context, unsigned short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
        context_(boost::asio::ssl::context::sslv23) {
        context_.set_options(boost::asio::ssl::context::default_workarounds |
            boost::asio::ssl::context::no_sslv2 |
            boost::asio::ssl::context::no_sslv3 |
            boost::asio::ssl::context::single_dh_use);
        context_.use_certificate_chain_file("/Users/hungnghiem/server.crt");
        context_.use_private_key_file("/Users/hungnghiem/server.key", boost::asio::ssl::context::pem);
        do_accept();
    }
private:
    void do_accept() {
        acceptor_.async_accept(
            [this](const boost::system::error_code& error, tcp::socket socket) {
                if (!error) {
                    std::make_shared<session>(std::move(socket), context_)->start();
                }
                do_accept();
            });
    }
    tcp::acceptor acceptor_;
    boost::asio::ssl::context context_;
};
int main() {
    try {
        std::cout << "Server listening on 443" << std::endl;
        boost::asio::io_context io_context;
        server s(io_context, 443);
        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}


