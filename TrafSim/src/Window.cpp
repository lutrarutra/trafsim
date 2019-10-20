#include "Window.hpp"

namespace TrafSim
{

Window::Window(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : window_(sf::VideoMode(width, height), title, sf::Style::Default, settings),
      clear_color_(sf::Color::Black)
{
    window_.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window_);
    window_.resetGLStates();
}
void Window::setClearColor(const sf::Color &color)
{
    clear_color_ = color;
}

void Window::clear()
{
    ImGui::SFML::Update(window_, clock_.restart());
    window_.clear(clear_color_);
}

void Window::draw(const sf::Shape &shape)
{
    window_.draw(shape);
}

void Window::display()
{
    ImGui::SFML::Render(window_);
    window_.display();
}

//Events
void Window::pollEvent()
{
    sf::Event e;
    while (window_.pollEvent(e))
    {
        ImGui::SFML::ProcessEvent(e);
        if (e.type == sf::Event::Closed)
            close();
        //Catch resizing
        else if (e.type == sf::Event::Resized)
        {
            std::cout << window_.getSize().x << " " << window_.getSize().y << std::endl;
        }
    }
}

void Window::close()
{
    window_.close();
}

} // namespace TrafSim
