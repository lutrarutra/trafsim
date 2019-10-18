#include <iostream>
#include <cstdlib>

#include "Application.hpp"

int main(int argc, char *argv[])
{
    std::cout << "TrafSim running: " << argc << " " << argv[0] << std::endl;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    TrafSim::Application app(1280, 720, "TrafSim", settings);
    app.run();
}