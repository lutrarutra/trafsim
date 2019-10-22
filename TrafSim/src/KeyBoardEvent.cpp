#include "KeyBoardEvent.hpp"

namespace TrafSim
{

/*
    Key pressed
*/

KeyPressedEvent::KeyPressedEvent(const unsigned int key_code)
    : key_code_(key_code)
{

}

KeyReleasedEvent::KeyReleasedEvent(const unsigned int key_code)
    : key_code_(key_code)
{

}

} // namespace TrafSim
