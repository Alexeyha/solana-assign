#pragma once

#include <curl-wrapper/CurlWrapper.hpp>
#include <jsoncons/json.hpp>

#include <chrono>
#include <optional>

namespace network {

struct RequestResult {
    std::chrono::nanoseconds latency;
    std::string result_data;
};

class RequestManager {
public:
    [[nodiscard]] RequestResult make_request(std::string_view method,
                                            const std::optional<jsoncons::json> &params = std::nullopt);

private:
    network::CurlWrapper curl_wrapper;

    static constexpr std::string_view SOLANA_URL = "https://api.devnet.solana.com";

    const jsoncons::json REQ_TEMPLATE = jsoncons::json::parse(
            R"({
                "id":1,
                "jsonrpc":"2.0"
            })");
};

}
