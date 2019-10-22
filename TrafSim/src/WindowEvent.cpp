#include "WindowEvent.hpp"

namespace TrafSim
{
WindowResizeEvent::WindowResizeEvent(const int new_width, const int new_height)
    : width_(new_width), height_(new_height)
{
}
} // namespace TrafSim
