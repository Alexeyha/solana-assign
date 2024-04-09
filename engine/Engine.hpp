#pragma once

#include <core/storage/IStorage.hpp>
#include <core/storage/Storage.hpp>
#include <core/event-handler/IEventHandler.hpp>
#include <core/event-handler/EventHandler.hpp>

#include <memory>
#include <string_view>

#define PERIOD 100

namespace engine {

class Engine {
public:
    Engine();

    void latency_tracking();

    void cli_app();

private:
    std::shared_ptr<core::IStorage> storage;
    std::shared_ptr<core::IEventHandler> event_handler;

    static constexpr std::string_view usage = R"(Usage:
                                                invoke - event with INVOKE type
                                                nothing - event with NOTHING type
                                                error - event with ERROR type
                                                latency - get standard deviation of latency
                                                oldest - retrieve oldest GET request's result)";

};

}
