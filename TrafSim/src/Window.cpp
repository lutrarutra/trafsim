#include "Window.hpp"

namespace TrafSim
{

Window::Window(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : window_(sf::VideoMode(width, height), title, sf::Style::Default, settings),
      clear_color_(sf::Color::White)
{
}
void Window::setClearColor(const sf::Color &color)
{
    clear_color_ = color;
}
void Window::draw(const sf::Shape &shape)
{
    window_.draw(shape);
}

//Events
void Window::pollEvent()
{
    sf::Event e;
    while (window_.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            close();
        //Catch resizing
        else if (e.type == sf::Event::Resized)
        {
            std::cout << window_.getSize().x << " " << window_.getSize().y << std::endl;
        }
    }
}

} // namespace TrafSim
