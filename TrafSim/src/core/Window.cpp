#include "Window.hpp"

#include "Application.hpp"
#include "GUI.hpp"

namespace TrafSim
{

Window::Window(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : m_window(sf::VideoMode(width, height), title, sf::Style::Default, settings), m_mapView(sf::View(sf::FloatRect(0, 0, width, height))),
      m_clearColor(sf::Color::Black)
{
    m_window.setView(m_mapView);
    //If turned on, it will limit fps to 60
    m_window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(m_window);
    m_window.resetGLStates();
    ImGui::SFML::Update(m_window, m_clock.restart());
    ImGui::SFML::Render(m_window);
    ImGui::GetFont()->Scale = 3.0f;
}

void Window::moveViewWithMouse(const sf::Vector2i &delta_mp)
{
    m_mapView.move(delta_mp.x * m_zoom, delta_mp.y * m_zoom);
    m_window.setView(m_mapView);
}

void Window::zoomView(sf::Vector2i relative_to, float zoom_dir)
{
    std::cout << m_zoom << "\n";
    if (zoom_dir == 0)
        return;
    const sf::Vector2f beforeCoord{m_window.mapPixelToCoords(relative_to)};
    const float zoomfactor = 1.1f;
    m_zoom = m_zoom * (zoom_dir < 0 ? zoomfactor : 1.f / zoomfactor);
    m_mapView.setSize(m_window.getSize().x * m_zoom, m_window.getSize().y * m_zoom);
    m_window.setView(m_mapView);
    const sf::Vector2f afterCoord{m_window.mapPixelToCoords(relative_to)};
    const sf::Vector2f offsetCoords{beforeCoord - afterCoord};
    m_mapView.move(offsetCoords);
    m_window.setView(m_mapView);
}

bool Window::isVisible(const sf::Vector2f &point, float offscreen) const
{
    sf::Vector2i convertedPoint = convert(point);
    const int minx = getWidth() * (1 - offscreen);
    const int miny = getHeight() * (1 - offscreen);
    const int maxx = getWidth() * offscreen;
    const int maxy = getHeight() * offscreen;
    return (convertedPoint.x > minx && convertedPoint.x < maxx && convertedPoint.y > miny && convertedPoint.y < maxy);
}

void Window::setClearColor(const sf::Color &color)
{
    m_clearColor = color;
}

void Window::clear()
{
    ImGui::SFML::Update(m_window, m_clock.restart());
    m_window.clear(m_clearColor);
}

void Window::draw(const sf::Drawable &shape)
{
    m_window.draw(shape);
}

void Window::display()
{
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void Window::moveView(int dx, int dy)
{
    //Higher sensivity -> quicker moves
    const float sensivity = 0.5f;
    dx *= m_zoom * sensivity;
    dy *= m_zoom * sensivity;
    //divide dx and dy by zoom factor so when we are zoomed in it will not move so quickly
    m_mapView.setCenter(m_mapView.getCenter().x + dx, m_mapView.getCenter().y + dy);
    m_window.setView(m_mapView);
}

//Events
void Window::pollEvent()
{
    auto app = Application::GetInstance();
    sf::Event e;
    while (m_window.pollEvent(e))
    {
        ImGui::SFML::ProcessEvent(e);
        if (e.type == sf::Event::Closed)
        {
            m_window.close();
        }
        //Catch resizing
        else if (e.type == sf::Event::Resized)
        {
            //When window resizes it will give us larger view of our map
            //it does not change size of our entities on screen, we can just see more entities
            m_mapView = sf::View(sf::FloatRect(0.f, 0.f, e.size.width, e.size.height));
            m_window.setView(m_mapView);
        }
        else if (e.type == sf::Event::MouseWheelScrolled)
        {
            zoomView(sf::Vector2i(e.mouseWheelScroll.x, e.mouseWheelScroll.y), e.mouseWheelScroll.delta);
            app->handleEvent(e);
        }
        //Mouse buttons
        else if (e.type == sf::Event::MouseButtonPressed)
            app->handleEvent(e);

        else if (e.type == sf::Event::MouseButtonReleased)
            app->handleEvent(e);

        //Keyboard keys
        else if (e.type == sf::Event::KeyPressed)
            app->handleEvent(e);

        else if (e.type == sf::Event::KeyReleased)
            app->handleEvent(e);
    }
}

void Window::close()
{
    m_window.close();
}

} // namespace TrafSim
