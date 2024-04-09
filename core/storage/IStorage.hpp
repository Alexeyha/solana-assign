#pragma once

#include <jsoncons/json.hpp>

namespace core {

struct StorageUnit {
    StorageUnit(std::uint64_t latency_, std::uint64_t timestamp_, jsoncons::json data_)
        : latency(latency_), timestamp(timestamp_), data(std::move(data_)) {
    }

    std::uint64_t latency;
    std::uint64_t timestamp;
    jsoncons::json data;

    bool operator<(const StorageUnit &other) const {
        return timestamp < other.timestamp;
    }
};

class IStorage {
public:
    virtual void add_result(std::uint64_t latency,
                    std::uint64_t timestamp,
                    const jsoncons::json &data) = 0;

    virtual std::optional<StorageUnit> retrieve_oldest() = 0;

    virtual long double get_latency_variation() const = 0;

    virtual ~IStorage() = default;

};

}
