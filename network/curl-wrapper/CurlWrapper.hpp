#pragma once

#include <curl/curl.h>
#include <string_view>
#include <string>

namespace network {

class CurlWrapper {
public:
    [[nodiscard]] std::string post_json_request(std::string_view url, std::string_view data);

private:
    void add_json_header(CURL *curl);
    void add_post_options(CURL *curl, std::string_view data);
};

}
