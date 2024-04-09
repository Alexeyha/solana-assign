#include "Engine.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>

namespace engine {

Engine::Engine() : storage(std::make_shared<core::Storage<PERIOD>>()),
                   event_handler(std::make_shared<core::EventHandler>(storage)) {
}

void Engine::latency_tracking() {
    using namespace std::chrono_literals;
    std::mt19937 gen(time(nullptr));
    while (true) {
        auto rand = gen() % 3;
        if (rand == 0) {
            event_handler->handle_event(core::EventType::INVOKE);
        } else if (rand == 1) {
            event_handler->handle_event(core::EventType::ERROR);
        } else if (rand == 2) {
            event_handler->handle_event(core::EventType::NOTHING);
        }
        std::this_thread::sleep_for(1000ms);
        std::cout << storage->get_latency_variation() << std::endl;
    }
}

void Engine::cli_app() {
    std::cout << usage << std::endl;
    while (true) {
        std::cout << "> ";
        std::string command;
        std::cin >> command;
        if (command == "invoke") {
            event_handler->handle_event(core::EventType::INVOKE);
        } else if (command == "nothing") {
            event_handler->handle_event(core::EventType::NOTHING);
        } else if (command == "error") {
            event_handler->handle_event(core::EventType::ERROR);
        } else if (command == "latency") {
            std::cout << storage->get_latency_variation() << std::endl;
        } else if (command == "oldest") {
            if (auto res = storage->retrieve_oldest(); res.has_value()) {
                std::cout << res->data.to_string() << std::endl;
            } else {
                std::cout << "Buffer is empty" << std::endl;
            }
        } else {
            std::cout << "Invalid command\n" << usage << std::endl;
        }
    }
}

}
