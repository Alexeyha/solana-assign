#include "CurlWrapper.hpp"

namespace network {

static size_t write_response(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
}

std::string CurlWrapper::post_json_request(std::string_view url, std::string_view data) {
    CURL *curl;
    CURLcode return_code;
    std::string response;
    curl = curl_easy_init();
    if (curl) [[likely]] {
        add_json_header(curl);
        add_post_options(curl, data);
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        return_code = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    } else [[unlikely]] {
        throw std::runtime_error("Curl initialization is failed");
    }
    return response;
}

void CurlWrapper::add_json_header(CURL *curl) {
    struct curl_slist *slist = nullptr;
    slist = curl_slist_append(slist, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
}

void CurlWrapper::add_post_options(CURL *curl, std::string_view data) {
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.data());
}

}
