#pragma once
#include "Event.h"

namespace Firefly {

class KeyEvent : public Event {
  public:
    const ui16& GetKeyCode() const { return m_keycode; }

  protected:
    KeyEvent(EventType type, ui16 keycode)
        : Event(type, (EventCategory)(ECATEGORY_INPUT | ECATEGORY_KEYBOARD)),
          m_keycode(keycode) {}
    ui16 m_keycode;
};

class KeyPressedEvent : public KeyEvent {
  public:
    KeyPressedEvent(ui16 keycode, i16 repeat_count)
        : KeyEvent(E_KEY_PRESSED, keycode), m_repeat_count(repeat_count) {}

    std::string ToString() const override {
        std::stringstream sstream;
        sstream << "KeyPressedEvent:" << m_keycode << "(" << m_repeat_count
                << "repeats)";
        return sstream.str();
    }

    const i16& GetRepeatCount() const { return m_repeat_count; }

  private:
    i16 m_repeat_count;
};

class KeyReleasedEvent : public KeyEvent {
  public:
    KeyReleasedEvent(ui16 keycode) : KeyEvent(E_KEY_RELEASED, keycode) {}

    std::string ToString() const override {
        std::stringstream sstream;
        sstream << "KeyReleasedEvent:" << m_keycode;
        return sstream.str();
    }
};

} // namespace Firefly