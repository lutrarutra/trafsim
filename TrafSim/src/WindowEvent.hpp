#pragma once

#include "Event.hpp"

namespace TrafSim
{
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(const int new_width, const int new_height);
    inline EventType GetType() const { return EventType::WindowResize; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

private:
    const int width_, height_;
};
} // namespace TrafSim
