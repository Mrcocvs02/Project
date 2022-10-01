#include "Flock.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

class Game {
 private:
  sf::RenderWindow window;
        sf::CircleShape Boid_i{2.f, 3};
      sf::CircleShape predator_shape{4.f};
      sf::CircleShape Flock_Center{2.0f};
      sf::RectangleShape Data{sf::Vector2f(data_width, data_height)};
      sf::RectangleShape Sdv_Flock_Velocity{sf::Vector2f(10.f, 2.f)};
  const int fps = 30;

  const int display_height = 650;
  const int display_width = 1200;
  bool play_check = true;

  const float data_height = (display_height / 5);
  const float data_width = (display_width / 5 + 15);

  Flock flock;
  bool predator_check = true;

 public:
  Game(float d, float s, float a, float c, int n);
  void set_immages();
  void run();
  void close_window();

  bool get_play_check() const;
  void set_play_check(bool const b);
  bool get_p_check() { return predator_check; };
  void set_p_check(bool a) { predator_check = a; };

  void play(Flock& flock);
  void predator_movement();
  void Draw();
};
float angle(vettore const& v);

#endif
