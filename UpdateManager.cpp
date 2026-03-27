//
// Created by administrateur on 3/27/26.
//

#include "UpdateManager.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void UpdateManager::Init() {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        else
            std::cout << response << std::endl;

        curl_easy_cleanup(curl);
    }
}