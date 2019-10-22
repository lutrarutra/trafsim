#pragma once

namespace TrafSim
{

enum class EventType
{
    None = 0,
    WindowResize,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseScrolled,
};

//Abstract base class for different type of events
class Event
{
public:
    virtual EventType GetType() const = 0;
protected:
    bool handled_ = false;

};
} // namespace TrafSim