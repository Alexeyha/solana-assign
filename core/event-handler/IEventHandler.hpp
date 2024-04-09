#pragma once

namespace core {

enum class EventType {
    INVOKE,
    NOTHING,
    ERROR
};

class IEventHandler {
public:
    virtual void handle_event(EventType event) = 0;
    virtual ~IEventHandler() = default;
};

}
