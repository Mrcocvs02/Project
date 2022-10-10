#include "Flock.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

class Game {
 private:
     const int Display_Height;
      const int Display_Width;
  sf::CircleShape Boid_i;

  sf::CircleShape Predator_Shape;
  sf::CircleShape Flock_Center;
  sf::RectangleShape Data;
  sf::RectangleShape Sdv_Flock_Velocity;
  sf::CircleShape Obstacle_i;

int pause_frame=0;
int Current_Frame=0;
  const int FPS = 30;

  bool Play_Button = true;

  const float data_height = (Display_Height / 5);
  const float data_width = (Display_Width / 5 + 15);

  Flock flock;
  bool predator_check = true;

 public:
  Game(float d, float s, float a, float c, int n);
  void Set_Immages();
  void Run(sf::RenderWindow* window);
  void Close_Window(sf::RenderWindow* window);

  bool Get_Play_Check() const;
  void Set_Play_Check(bool const b);
  bool Set_Predator_Check() { return predator_check; };
  void Set_Predator_Check(bool a) { predator_check = a; };

  void Play_button();
  void predator_movement();
  void Draw(sf::RenderWindow* window);
};
float Angle(vettore const& v);

#endif
