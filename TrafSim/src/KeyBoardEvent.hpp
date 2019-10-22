#pragma once

#include "Event.hpp"

namespace TrafSim
{

class KeyPressedEvent : public Event
{
public:
    KeyPressedEvent(const unsigned int key_code);
    inline EventType GetType() const { return EventType::KeyPressed; }
    unsigned int getKeyCode() const { return key_code_; }

private:
    const unsigned int key_code_;
};

class KeyReleasedEvent : public Event
{
public:
    KeyReleasedEvent(const unsigned int key_code);
    inline EventType GetType() const { return EventType::KeyReleased; }
    unsigned int getKeyCode() const { return key_code_; }

private:
    const unsigned int key_code_;
};

} // namespace TrafSim
