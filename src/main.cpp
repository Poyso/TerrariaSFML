#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

float pos_y = 0;
float pos_x = 0;
int main() {
  auto window =
      sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
  sf::RectangleShape player({100, 100});
  sf::RectangleShape block({100, 100});
  sf::CircleShape dot(1);
  block.setFillColor(sf::Color::Red);
  block.setPosition({500, 500});
  player.setFillColor(sf::Color::Blue);
  player.setPosition({pos_x, pos_y});
  dot.setFillColor(sf::Color::White);
  dot.setPosition({block.getPosition().x, block.getPosition().y + 100.f});
  // std::cout << "x: " << block.getPoint(0).x << "y: " << block.getPoint(0).y
  // << std::endl;
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    sf::FloatRect player_bounds = player.getGlobalBounds();
    sf::FloatRect block_bounds = block.getGlobalBounds();
    bool right_side = (!block_bounds.contains(
                          {player.getPosition().x, player.getPosition().y})) &&
                      !block_bounds.contains({player.getPosition().x,
                                              player.getPosition().y + 100});
    bool left_side = (!player_bounds.contains(block.getPosition()) &&
                      !player_bounds.contains({block.getPosition().x,
                                               block.getPosition().y + 100}));
    bool top_side = (!block_bounds.contains({player.getPosition().x,
                                             player.getPosition().y + 100}) &&
                     !block_bounds.contains({player.getPosition().x + 100,
                                             player.getPosition().y + 100}));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      pos_x++;
      player.setPosition({pos_x, pos_y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && top_side) {
      pos_y++;
      player.setPosition({pos_x, pos_y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
      pos_y--;
      player.setPosition({pos_x, pos_y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && right_side) {
      pos_x--;
      player.setPosition({pos_x, pos_y});
    }

    window.clear();
    window.draw(player);
    window.draw(block);
    window.draw(dot);
    window.display();
  }
}
