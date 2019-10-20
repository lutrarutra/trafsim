#include "Window.hpp"

namespace TrafSim
{

Window::Window(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : window_(sf::VideoMode(width, height), "TrafSim", sf::Style::Default, settings),
      clear_color_(sf::Color::Black)
{
    window_.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window_);
    window_.setTitle(title);
    window_.resetGLStates();
}
void Window::setClearColor(const sf::Color &color)
{
    clear_color_ = color;
}
void Window::draw(const sf::Shape &shape)
{
    window_.draw(shape);
}

void Window::gui()
{
    float color[4];
    color[0] = clear_color_.r;
    color[1] = clear_color_.g;
    color[2] = clear_color_.b;
    color[3] = clear_color_.a;
    ImGui::SFML::Update(window_, clock_.restart());
    ImGui::Begin("Sample window");
    ImGui::SetWindowFontScale(2.5f);
    if (ImGui::ColorEdit4("Background color", color))
    {
        // this code gets called if color value changes, so
        // the background color is upgraded automatically!
        clear_color_.r = static_cast<sf::Uint8>(color[0] * 255.f);
        clear_color_.g = static_cast<sf::Uint8>(color[1] * 255.f);
        clear_color_.b = static_cast<sf::Uint8>(color[2] * 255.f);
        clear_color_.a = static_cast<sf::Uint8>(color[3] * 255.f);
    }
    // Window title text edit
    ImGui::InputText("Window title", title_, 255);

    if (ImGui::Button("Update window title"))
    {
        // this code gets if user clicks on the button
        // yes, you could have written if(ImGui::InputText(...))
        // but I do this to show how buttons work :)
        window_.setTitle(title_);
    }
    ImGui::End();
    ImGui::SFML::Render(window_);
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
