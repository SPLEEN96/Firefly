#pragma once
#include "FFLY_CORE.h"
#include "PCH_CORE.h"

namespace Firefly {

enum class EventType {
    NONE = 0,
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
    NONE                  = 0,
    ECATEGORY_APPLICATION = BIT(0),
    ECATEGORY_INPUT       = BIT(1),
    ECATEGORY_KEYBOARD    = BIT(2),
    ECATEGORY_MOUSE       = BIT(3),
    ECATEGORY_MOUSEBUTTON = BIT(4)
};

#define EVENT_CLASS_TYPE(type)                                                 \
    static const EventType   GetStaticType() { return EventType::type; }     \
    virtual const EventType& GetType() const override {                        \
        return GetStaticType();                                                \
    }                                                                          \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                         \
    virtual const ui8& GetCategoryFlags() const override { return category; }



class Event {
    friend class EventDispatcher;

  public:
    virtual const EventType& GetType() const          = 0;
    virtual const ui8&       GetCategoryFlags() const = 0;
    virtual const char*      GetName() const          = 0;
    virtual std::string      ToString() const         = 0;

  private:
    bool m_handled = false;
};

class EventDispatcher {};

class EventHandler {
  public:
    static void SetupGLFWEvents() {}
};

} // namespace Firefly
