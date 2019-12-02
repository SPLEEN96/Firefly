#pragma once
#include "Events/Event.h"

namespace Firefly {
class WindowCloseEvent : public Event {
  public:
    WindowCloseEvent() : Event(E_WINDOW_CLOSE, ECATEGORY_APPLICATION) {}
    ~WindowCloseEvent() {}

    static const EventType GetStaticType() { return EventType::E_WINDOW_CLOSE; }
    const EventType        GetType() const override { return GetStaticType(); }

    std::string ToString() const override {
        std::stringstream sstream;
        sstream << "WindowCloseEvent";
        return sstream.str();
    }
};
}; // namespace Firefly