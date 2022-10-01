#include "Graphic.hpp"
Game::Game(float d, float s, float a, float c, int n)
    : flock{d, s, a, c, n}
 {}

float angle(vettore const& v) {
  float angle = (float)(atan2(v.get_x(), -v.get_y()) * 180 / M_PI);
  return angle;
}

void Game::predator_movement() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
    predator_check = false;
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    predator_check = true;
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    flock.set_predator({flock.get_predator().Get_Position() + vettore{-7, 0},
                        flock.get_predator().Get_Velocity()});
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    flock.set_predator({flock.get_predator().Get_Position() + vettore{7, 0},
                        flock.get_predator().Get_Velocity()});
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    flock.set_predator({flock.get_predator().Get_Position() + vettore{0, -7},
                        flock.get_predator().Get_Velocity()});
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    flock.set_predator({flock.get_predator().Get_Position() + vettore{0, 7},
                        flock.get_predator().Get_Velocity()});
  };
}

void Game::set_immages() {

  
  Boid_i.setOutlineThickness(1.f);
  Boid_i.setFillColor(sf::Color(28, 229, 198));

  predator_shape.setOutlineThickness(1.f);
  predator_shape.setFillColor(sf::Color::Red);

  Flock_Center.setOutlineThickness(1.f);
  Flock_Center.setFillColor(sf::Color::Red);

  Data.setFillColor(sf::Color::Transparent);
  Data.setOutlineThickness(2.f);
  Data.setPosition(2., (display_height - data_height - 2));

  Sdv_Flock_Velocity.setFillColor(sf::Color::Blue);
}

void Game::close_window() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    window.close();
    std::cout << "program terminated" << '\n';
    exit(0);
  };
}

bool Game::get_play_check() const { return play_check; }
void Game::set_play_check(bool const b) { play_check = b; }

void Game::Draw() {
  for (int i = 0; i < flock.get_flock().size(); i++) {
    Boid_i.setPosition(flock.get_flock()[i].Get_Position().get_x(),
                       flock.get_flock()[i].Get_Position().get_y());
    float theta = angle(flock.get_flock()[i].Get_Velocity());
    Boid_i.setRotation(theta);
    window.draw(Boid_i);
  }
  predator_shape.setPosition(flock.get_predator().Get_Position().get_x(),
                             flock.get_predator().Get_Position().get_y());
  predator_movement();
  window.draw(predator_shape);

  float graph_height =
      display_height - (data_height * (flock.medium_velocity().norm() / 75));
  sf::RectangleShape Graph(sf::Vector2f(10, graph_height));
  Graph.setFillColor(sf::Color::Red);
  Graph.setOutlineThickness(1.f);
  Graph.setPosition(10, graph_height);

  Flock_Center.setFillColor(sf::Color::Red);
  Flock_Center.setPosition(
      (flock.center_of_mass().get_x() / 5) - 3,
      display_height - data_height + (flock.center_of_mass().get_y() / 5) - 3);

  sf::CircleShape Sdv_Flock_Center(flock.sdv_center_of_mass() / 5);
  Sdv_Flock_Center.setOutlineThickness(1.f);
  Sdv_Flock_Center.setFillColor(sf::Color::Transparent);
  Sdv_Flock_Center.setPosition(
      Flock_Center.getPosition() -
      sf::Vector2f(flock.sdv_center_of_mass() / 5 - 3,
                   flock.sdv_center_of_mass() / 5 - 3));

  Sdv_Flock_Velocity.setPosition(10.,
                                 (graph_height - flock.sdv_medium_velocity()));
  Sdv_Flock_Velocity.setPosition(10.,
                                 (graph_height + flock.sdv_medium_velocity()));

  window.draw(Flock_Center);
  window.draw(Sdv_Flock_Center);
  window.draw(Graph);
  window.draw(Sdv_Flock_Velocity);
  window.draw(Data);
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Simulation");
                          window.setFramerateLimit(fps);
  set_immages();
  int t = 0;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    while (t < 30000) {
      std::cout << "t=" << t << '\n';
      window.clear(sf::Color(22, 28, 72));
      // play(flock);
      if (get_play_check()) {
        flock.simulation(get_p_check());
      }
      Draw();
      window.display();
      t++;
    }
  }
}