#pragma once

namespace Firefly {

enum EventType { EventWindow, EventApplication, EventInput };

class Event {
  public:
    Event();
    ~Event();

    EventType GetType() { return m_type; }

  private:
    EventType m_type;
};

} // namespace Firefly