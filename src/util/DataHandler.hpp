#pragma once

#include <SFML/Graphics.hpp>
#include "trafficsim/MapBuilder.hpp"

#include <map>
#include <memory>
#include <string>
#include <utility>

namespace ts
{

class DataHandler
{

public:
    DataHandler(std::vector<std::string> &logs)
        : logs_(logs){};
    // Loads texture from file
    void loadTexture(const char *src, const char *texture_key);
    void loadTexturesFromFile(const char *src);

    void loadMap(const char *file_name, MapBuilder &builder, Grid &grid) const;
    void saveMap(const char *file_name, Grid &grid) const;
    const char *getCurrentFileName() const { return current_file_.c_str(); }

    const sf::Texture *getTexture(const char *texture_name) { return textures_[texture_name].get(); }

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textures_;
    mutable std::string current_file_;
    std::vector<std::string> &logs_;
};

} // namespace ts
