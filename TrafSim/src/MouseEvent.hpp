#pragma once

#include "Event.hpp"

namespace TrafSim
{

enum MouseButton
{
    LEFTBUTTON = 0,
    RIGHTBUTTON,
    SCROLLBUTTON,
};

class MouseEvent : public Event
{
public:
    MouseEvent(const int x, const int y) : x_(x), y_(y){};
    virtual EventType GetType() const = 0;
    int getX() const { return x_; }
    int getY() const { return x_; }

protected:
    const int x_, y_;
};

class MouseButtonPressedEvent : public MouseEvent
{
public:
    MouseButtonPressedEvent(const int x, const int y, const MouseButton mousebutton);
    inline EventType GetType() const { return EventType::MouseButtonPressed; }
    MouseButton getButton() const { return mousebutton_; }

private:
    const MouseButton mousebutton_;
};

class MouseButtonReleasedEvent : public MouseEvent
{
public:
    MouseButtonReleasedEvent(const int x, const int y, const MouseButton mousebutton);
    inline EventType GetType() const { return EventType::MouseButtonReleased; }
    MouseButton getButton() const { return mousebutton_; }

private:
    const MouseButton mousebutton_;
};

class MouseButtonScrolled : public MouseEvent
{
public:
    MouseButtonScrolled(const int x, const int y, const int direction);
    inline EventType GetType() const { return EventType::MouseScrolled; }
    int getDir() const { return dir_; }

private:
    const int dir_;
};

} // namespace TrafSim
