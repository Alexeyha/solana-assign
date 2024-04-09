#include "EventHandler.hpp"

#include <boost/asio/post.hpp>

#include <iostream>
#include <future>

namespace core {

EventHandler::EventHandler(const std::shared_ptr<IStorage> &storage_) : storage(storage_) {
}

void EventHandler::handle_event(core::EventType event) {
    switch (event) {
        case EventType::ERROR: {
            std::cerr << "Error event received" << std::endl;
            break;
        }
        case EventType::INVOKE: {
            boost::asio::post(pool, [this]() {
                try {
                    auto response = request_manager.make_request(SOLANA_METHOD);
                    jsoncons::json parsed_data = jsoncons::json::parse(response.result_data);
                    auto timestamp = parsed_data["result"]["context"]["slot"].as<std::uint64_t>();
                    storage->add_result(std::chrono::duration_cast<std::chrono::milliseconds>(response.latency).count(), timestamp, parsed_data);
                } catch (const std::exception &e) {
                    std::cerr << "Something went wrong during the invocation: " << e.what();
                }
            });
            break;
        }
        case EventType::NOTHING: {
            // nothing
        }
    }
}

}
