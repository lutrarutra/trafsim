#include "Window.hpp"

namespace TrafSim
{

Window::Window(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : window_(sf::VideoMode(width, height), title, sf::Style::Default, settings), map_view_(sf::View(sf::FloatRect(0, 0, width, height))),
      clear_color_(sf::Color::Black)
{
    window_.setView(map_view_);
    //If turned on, it will limit fps to 60
    window_.setVerticalSyncEnabled(false);
    ImGui::SFML::Init(window_);
    window_.resetGLStates();
    ImGui::SFML::Update(window_, clock_.restart());
    ImGui::SFML::Render(window_);
    ImGui::GetFont()->Scale = 3.0f;
}

void Window::zoom(int z)
{
    if(z == 0)
        return;
    std::cout << z << std::endl;
    const float zoomfactor = 1.1f;
    zoom_ = zoom_ * (z > 0 ? zoomfactor : 1.f / zoomfactor);
    map_view_.setSize(window_.getSize().x * zoom_, window_.getSize().y * zoom_);
    window_.setView(map_view_);
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
            //When window resizes it will give us larger view of our map
            //it does not change size of our entities on screen, we can just see more entities
            map_view_ = sf::View(sf::FloatRect(0.f, 0.f, e.size.width, e.size.height));
            window_.setView(map_view_);
        }
        else if (e.type == sf::Event::MouseWheelScrolled)
        {
            zoom(e.mouseWheelScroll.delta);
        }
    }
}

void Window::close()
{
    window_.close();
}

} // namespace TrafSim
