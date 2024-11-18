#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>

// Header callback function to check for 200 OK status code
static size_t HeaderCallback(char *buffer, size_t size, size_t nitems, void *userdata) {
    std::string header(buffer, size * nitems);
    if (header.find("HTTP") != std::string::npos) {
        if (header.find("200 OK") != std::string::npos) {
            return 0; 
        }
    }
    return nitems * size;
}

std::vector<char> readFile(const std::string& filename) {
    // Open the file at the end to get the size
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file\n";
        return {};
    }

    // Get the size and allocate a buffer
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        std::cerr << "Failed to read file\n";
        return {};
    }

    return buffer;
}

int main() {
    CURL *curl;
    CURLcode res;
    long response_code = 0;
    struct curl_slist *headers = NULL; // Initialize a list to hold our headers

    // Replace the path with your actual file path
    std::string filePath = "/Users/hungnghiem/Desktop/snail_6891494/video.mp4";
    std::vector<char> fileContent = readFile(filePath);

    if (fileContent.empty()) {
        std::cerr << "File content is empty\n";
        return 1;
    }

    curl = curl_easy_init();
    if(curl) {
        // Set the URL that is about to receive our POST
        curl_easy_setopt(curl, CURLOPT_URL, "https://127.0.0.1:443/api/intrusion/video/1");
        // Specify the path to the CA certificate for verification
        curl_easy_setopt(curl, CURLOPT_CAINFO, "/Users/hungnghiem/server.crt");
        // Enable verbose output to stderr, similar to --verbose
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // // Specify the POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fileContent.data());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fileContent.size());

        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback); 

        // Set the custom headers
        headers = curl_slist_append(headers, "Content-Type: application/octet-stream");
        headers = curl_slist_append(headers, "Expect: 100-continue");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // Set timeout
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res == CURLE_WRITE_ERROR) {
            std::cout << "Request was aborted successfully after receiving 200 OK." << std::endl;
        } else if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup
        curl_slist_free_all(headers); // free the header list
        curl_easy_cleanup(curl);
    }
    return 0;
}
