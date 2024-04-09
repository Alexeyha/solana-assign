#pragma once

#include "IStorage.hpp"

#include <jsoncons/json.hpp>

#include <queue>
#include <chrono>
#include <mutex>
#include <optional>
#include <set>
#include <cmath>

namespace core {

template <std::uint64_t PERIOD>
class Storage : public IStorage {
public:
    void add_result(std::uint64_t latency,
                    std::uint64_t timestamp,
                    const jsoncons::json &data) override {
        std::scoped_lock lock(buffer_mutex, period_mutex);
        buffer.emplace(latency, timestamp, data);
        add_in_period(latency, timestamp, data);
    }

    [[nodiscard]] std::optional<StorageUnit> retrieve_oldest() override {
        std::lock_guard lock(buffer_mutex);
        if (buffer.empty()) return std::nullopt;
        auto res = *buffer.begin();
        buffer.erase(buffer.begin());
        return res;
    }

    [[nodiscard]] long double get_latency_variation() const override {
        std::lock_guard lock(period_mutex);
        if (period.empty()) [[unlikely]] return 0;
        long double mean = static_cast<long double>(sum) / period.size();
        return std::sqrt(static_cast<long double>(sum_squares) / period.size() - mean * mean);
    }

private:
    void add_in_period(std::uint64_t latency,
                       std::uint64_t timestamp,
                       const jsoncons::json &data) {
        auto it = period.emplace(latency, timestamp, data);
        sum += latency;
        sum_squares += latency * latency;
        auto last_timestamp = (--buffer.end())->timestamp - std::min(PERIOD, (--buffer.end())->timestamp);
        while (period.begin()->timestamp < last_timestamp) {
            sum -= period.begin()->latency;
            sum_squares -= (period.begin()->latency * period.begin()->latency);
            period.erase(period.begin());
        }
    }

    std::multiset<StorageUnit> buffer;
    std::multiset<StorageUnit> period;
    std::uint64_t sum = 0;
    std::uint64_t sum_squares = 0;
    mutable std::mutex buffer_mutex;
    mutable std::mutex period_mutex;
};

}
