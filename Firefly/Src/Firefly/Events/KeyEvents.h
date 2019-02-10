#pragma once
#include "Event.h"

namespace Firefly {

class KeyEvent : public Event {
  public:
    const uint16& GetKeyCode() const { return m_keycode; }

  protected:
    KeyEvent(EventType type, uint16 keycode)
        : Event(type, (EventCategory)(ECATEGORY_INPUT | ECATEGORY_KEYBOARD)),
          m_keycode(keycode) {}
    uint16 m_keycode;
};

class KeyPressedEvent : public KeyEvent {
  public:
    KeyPressedEvent(uint16 keycode, int16 repeat_count)
        : KeyEvent(E_KEY_PRESSED, keycode), m_repeat_count(repeat_count) {}

    std::string ToString() const override {
        std::stringstream sstream;
        sstream << "KeyPressedEvent:" << m_keycode << "(" << m_repeat_count
                << "repeats)";
        return sstream.str();
    }
    static const EventType& GetStaticType() { return E_KEY_PRESSED; }
    const int16&            GetRepeatCount() const { return m_repeat_count; }

  private:
    int16 m_repeat_count;
};

class KeyReleasedEvent : public KeyEvent {
  public:
    KeyReleasedEvent(uint16 keycode) : KeyEvent(E_KEY_RELEASED, keycode) {}

    std::string ToString() const override {
        std::stringstream sstream;
        sstream << "KeyReleasedEvent:" << m_keycode;
        return sstream.str();
    }
    static const EventType& GetStaticType() { return E_KEY_RELEASED; }
};

class KeyTypedEvent : public KeyEvent {
  public:
    KeyTypedEvent(uint16 keycode) : KeyEvent(E_KEY_TYPED, keycode) {}

    std::string ToString() const override {
        std::stringstream sstream;
        sstream << "KeyPressedEvent:" << m_keycode;
        return sstream.str();
    }
    static const EventType& GetStaticType() { return E_KEY_PRESSED; }
};

// struct KeyEventStruct {
//     union {
//         /* Key Pressed */
//         struct {} key_pressed;
//         struct {} key_released;
//     };
// };

} // namespace Firefly