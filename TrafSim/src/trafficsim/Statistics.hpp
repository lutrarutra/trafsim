#pragma once

#include <climits> // UINT_MAX

#include <SFML/Graphics.hpp>
#include <fstream>
#include "core/Window.hpp"
#include "Map.hpp"

namespace ts
{
class Statistics
{
public:
  Statistics(Map &map, const Window &window, std::vector<std::string> &logs);

  // Handle mouse input to select the map
  void handleInput(const sf::Event &ev);
  void drawGUI();
  void exportCSV(const char *file_name, const std::vector<std::uint16_t> &car_data);

private:
  Map &map_;
  const Window &window_;
  // Stores highlighted tile, which was left clicked
  unsigned int selected_tile_index_ = UINT_MAX;
  void selectTile(const sf::Vector2f &pos);
  void unSelectTile();
  std::vector<std::string> &logs_;
};
} // namespace ts