#include <iostream>
#include <string>
#include <curl/curl.h>

// Header callback function to check for 200 OK status code
static size_t HeaderCallback(char *buffer, size_t size, size_t nitems, void *userdata) {
    std::string header(buffer, size * nitems);
    std::cout << "LKKKKKK: " << header <<std::endl;
    if (header.find("HTTP") != std::string::npos) {
        if (header.find("200 OK") != std::string::npos) {
            return 0; 
        }
    }
    return nitems * size;
}

int main() {
    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (curl) {
        // The JSON data you want to send
        std::string jsonData = "{\"key\":\"value\"}";

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://127.0.0.1:443/api/intrusion/video/1");
        // Specify the path to the CA certificate for verification
        curl_easy_setopt(curl, CURLOPT_CAINFO, "/Users/hungnghiem/server.crt");
        // Enable verbose output to stderr, similar to --verbose
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // Set the POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        // Set the content type header
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
        // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HeaderCallback);

        // Set timeout
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        // Perform the request, and get the response code
        CURLcode res = curl_easy_perform(curl);
        // Check for errors
        if (res == CURLE_WRITE_ERROR) {
            std::cout << "Request was aborted successfully after receiving 200 OK." << std::endl;
        } else if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return 0;
}