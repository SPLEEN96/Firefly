#pragma once
#include "FFLY_CORE.h"
#include "PCH_CORE.h"

namespace Firefly {

enum EventType {
    E_NONE = 0,
    E_WINDOW_CLOSE,
    E_WINDOW_RESIZE,
    E_WINDOW_FOCUS,
    E_WINDOW_LOST_FOCUS,
    E_WINDOW_MOVED,
    E_APP_TICK,
    E_APP_UPDATE,
    E_APP_RENDER,
    E_KEY_PRESSED,
    E_KEY_RELEASED,
    E_KEY_TYPED,
    E_MOUSE_BUTTON_PRESSED,
    E_MOUSE_BUTTON_RELEASED,
    E_MOUSE_MOVED,
    E_MOUSE_SCROLLED
};

enum EventCategory {
    ECATEGORY_NONE        = 0,
    ECATEGORY_APPLICATION = BIT(0),
    ECATEGORY_INPUT       = BIT(1),
    ECATEGORY_KEYBOARD    = BIT(2),
    ECATEGORY_MOUSE       = BIT(3),
    ECATEGORY_MOUSEBUTTON = BIT(4)
};

class Event {
    friend class EventDispatcher;

  public:
    virtual const EventType& GetType() const { return m_type; }
    virtual const uint8&     GetCategoryFlags() const { return m_category; }
    virtual const char*      GetName() const { return EventNames[m_type]; }
    virtual std::string      ToString() const = 0;

  protected:
    Event(EventType type = E_NONE, EventCategory category = ECATEGORY_NONE)
        : m_type(type), m_category(category) {}

    const EventType     m_type;
    const EventCategory m_category;

  private:
    bool m_handled = false;

    const char* EventNames[16]{"None",
                               "WindowClosed",
                               "WindowResize",
                               "WindowFocus",
                               "WindoWLostFocus",
                               "WindowMoved",
                               "AppTick",
                               "AppUpdate",
                               "AppRender",
                               "KeyPressed",
                               "KeyReleased",
                               "KeyTyped",
                               "MouseButtonPressed",
                               "MouseButtonReleased",
                               "MouseMoved",
                               "MouseScrolled"};
};


class EventDispatcher {
  public:
    EventDispatcher(Event& e) : m_event(e) {}

    bool Dispatch(EventType e_type, bool(EventFn)(Event* e)) {
        if (m_event.GetType() == e_type) {
            EventFn(&m_event);
            return true;
        }
        return false;
    }

  private:
    Event& m_event;
};

// class EventHandler {
//   public:
//     static void SetupGLFWEvents() {}
// };

} // namespace Firefly
