#include "RequestManager.hpp"

namespace network {

[[nodiscard]] RequestResult RequestManager::make_request(std::string_view method,
                                                        const std::optional<jsoncons::json> &params) {
    jsoncons::json request_json = REQ_TEMPLATE;
    request_json["method"] = method;
    if (params.has_value()) {
        request_json["params"] = params.value();
    }

    auto start = std::chrono::steady_clock::now();
    std::string response = curl_wrapper.post_json_request(SOLANA_URL, request_json.to_string());
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    return {duration, response};
}

}
