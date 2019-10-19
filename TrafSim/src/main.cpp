#include <iostream>

#include "Random.h"
#include "Application.hpp"

int main(int argc, char *argv[])
{
    if (argc > 0)
        std::cout << "TrafSim running from: " << argv[0] << std::endl;


    TrafSim::Random r;
    r.distribution_test(100);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    TrafSim::Application app(1280, 720, "TrafSim", settings);
    app.run();
}