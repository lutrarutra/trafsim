#include "MouseEvent.hpp"

namespace TrafSim
{

/*

MouseButtonPressedEvent

*/
MouseButtonPressedEvent::MouseButtonPressedEvent(const int x, const int y, const MouseButton mousebutton)
    : MouseEvent(x, y), mousebutton_(mousebutton)
{
}

/*

MouseButtonReleasedEvent

*/
MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int x, const int y, const MouseButton mousebutton)
    : MouseEvent(x, y), mousebutton_(mousebutton)
{
}

/*

MouseButtonScrolled

*/
MouseButtonScrolled::MouseButtonScrolled(const int x, const int y, const int direction)
    : MouseEvent(x, y), dir_(direction)
{
}

} // namespace TrafSim
