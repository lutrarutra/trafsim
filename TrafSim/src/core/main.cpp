#include <iostream>

#include "Application.hpp"



int main(int argc, char *argv[])
{
    if (argc > 0)
        std::cout << "TrafSim running from: " << argv[0] << std::endl;


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    int height = sf::VideoMode::getDesktopMode().height;
    int width = sf::VideoMode::getDesktopMode().width;
    TrafSim::Application app(width / 2, height / 2, "TrafSim", settings);
    app.run();
}