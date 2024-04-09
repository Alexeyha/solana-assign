#pragma once

#include "IEventHandler.hpp"

#include <storage/IStorage.hpp>
#include <network/request-manager/RequestManager.hpp>
#include <boost/asio/thread_pool.hpp>

#include <coroutine>

namespace core {

class EventHandler: public IEventHandler {
public:
    explicit EventHandler(const std::shared_ptr<IStorage> &storage_);

    void handle_event(EventType event) override;

private:
    network::RequestManager request_manager;
    std::shared_ptr<IStorage> storage;
    boost::asio::thread_pool pool;

    static constexpr std::string_view SOLANA_METHOD = "getLatestBlockhash";
};

}
