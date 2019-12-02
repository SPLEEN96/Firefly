#pragma once
#include "Events/Event.h"

namespace Firefly {

class MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(float x, float y)
        : Event(E_MOUSE_MOVED, (EventCategory)(ECATEGORY_INPUT | ECATEGORY_MOUSE)),
          m_mouseX(x), m_mouseY(y) {}

    float X() const { return m_mouseX; }
    float Y() const { return m_mouseY; }

    static const EventType GetStaticType() { return E_MOUSE_MOVED; }
    const EventType        GetType() const override { return GetStaticType(); }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
        return ss.str();
    }

  private:
    float m_mouseX, m_mouseY;
};

class MouseButtonEvent : public Event {
  public:
    int GetMouseButton() const { return m_button; }

  protected:
    MouseButtonEvent(EventType type, int button)
        : Event(type, (EventCategory)(ECATEGORY_INPUT | ECATEGORY_MOUSE)),
          m_button(button) {}

    int m_button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
  public:
    MouseButtonPressedEvent(int button)
        : MouseButtonEvent(E_MOUSE_BUTTON_PRESSED, button) {}

    static const EventType GetStaticType() { return E_MOUSE_BUTTON_PRESSED; }
    const EventType        GetType() const override { return GetStaticType(); }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_button;
        return ss.str();
    }
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
  public:
    MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(E_MOUSE_BUTTON_RELEASED, button) {}

    static const EventType GetStaticType() { return E_MOUSE_BUTTON_RELEASED; }
    const EventType        GetType() const override { return GetStaticType(); }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_button;
        return ss.str();
    }
};

} // namespace Firefly