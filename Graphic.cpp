#include "Graphic.hpp"
Game::Game(float d, float s, float a, float c, int n)
    : flock{d, s, a, c, n},
      Display_Height{650},
      Display_Width{1200},
      Boid_i{2.f, 3},
      Predator_Shape{4.f},
      Flock_Center{2.0f},
      Obstacle_i{4.0f},
      Data{sf::Vector2f((Display_Width / 5 + 15),(Display_Height / 5))},
      Sdv_Flock_Velocity{sf::Vector2f(10.f, 2.f)} {}

float Angle(vettore const& v) {
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
    flock.set_predator({flock.get_predator().Get_Position() + vettore{-5, 0},
                        flock.get_predator().Get_Velocity()});
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    flock.set_predator({flock.get_predator().Get_Position() + vettore{5, 0},
                        flock.get_predator().Get_Velocity()});
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    flock.set_predator({flock.get_predator().Get_Position() + vettore{0, -5},
                        flock.get_predator().Get_Velocity()});
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    flock.set_predator({flock.get_predator().Get_Position() + vettore{0, 5},
                        flock.get_predator().Get_Velocity()});
  };
}

void Game::Set_Immages() {
  Boid_i.setOutlineThickness(1.f);
  Boid_i.setFillColor(sf::Color(28, 229, 198));

  Predator_Shape.setOutlineThickness(1.f);
  Predator_Shape.setFillColor(sf::Color::Red);

  Flock_Center.setOutlineThickness(1.f);
  Flock_Center.setFillColor(sf::Color::Red);

  Data.setFillColor(sf::Color::Transparent);
  Data.setOutlineThickness(2.f);
  Data.setPosition(2., (Display_Height - data_height - 2));

  Obstacle_i.setOutlineThickness(1.f);
  Obstacle_i.setFillColor(sf::Color(108,25,44));

  Sdv_Flock_Velocity.setFillColor(sf::Color::Blue);
}

void Game::Close_Window(sf::RenderWindow* window) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    window->close();
    std::cout << "program terminated" << '\n';
    exit(0);
  };
}

bool Game::Get_Play_Check() const { return Play_Button; }
void Game::Set_Play_Check(bool const b) { Play_Button = b; }
void Game::Play_button() {
  if (Get_Play_Check()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
      Set_Play_Check(false);
      pause_frame=Current_Frame;
    };
  } else {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
      Set_Play_Check(true);
    }

    for (unsigned long int i = 0; i < flock.get_flock().size(); i++) {
      flock.get_flock()[i].Set_Velocity(flock.Predator_Repulsion(i));
      flock.get_flock()[i].Wall_Hit();
      flock.get_flock()[i].Set_Position(flock.get_flock()[i].Get_Position() + (flock.get_flock()[i].Get_Velocity() / FPS));
    }
  }
}

void Game::Draw(sf::RenderWindow* window) {
  for (int i = 0; i < flock.get_flock().size(); i++) {
    Boid_i.setPosition(flock.get_flock()[i].Get_Position().get_x(),
                       flock.get_flock()[i].Get_Position().get_y());
    float theta = Angle(flock.get_flock()[i].Get_Velocity());
    Boid_i.setRotation(theta);
    window->draw(Boid_i);
  }

  for (int i = 0; i < flock.Get_Obstacles().size(); i++) {
    Obstacle_i.setPosition(flock.Get_Obstacles()[i].get_x(),flock.Get_Obstacles()[i].get_y());
    window->draw(Obstacle_i);
  }

  Predator_Shape.setPosition(flock.get_predator().Get_Position().get_x(),
                             flock.get_predator().Get_Position().get_y());
  predator_movement();
  window->draw(Predator_Shape);

  float graph_height =
      Display_Height - (data_height * (flock.Medium_Velocity().norm() / 75));
  sf::RectangleShape Graph(sf::Vector2f(10, graph_height));
  Graph.setFillColor(sf::Color::Red);
  Graph.setOutlineThickness(1.f);
  if(graph_height<Display_Height- data_height) graph_height=Display_Height- data_height;

  Graph.setPosition(10, graph_height);

  Flock_Center.setFillColor(sf::Color::Red);
  Flock_Center.setPosition(
      (flock.Center_Of_Mass().get_x() / 5) - 3,
      Display_Height - data_height + (flock.Center_Of_Mass().get_y() / 5) - 3);

  sf::CircleShape Sdv_Flock_Center(flock.Sdv_Center_Of_Mass() / 5);
  Sdv_Flock_Center.setOutlineThickness(1.f);
  Sdv_Flock_Center.setFillColor(sf::Color::Transparent);
  Sdv_Flock_Center.setPosition(
      Flock_Center.getPosition() -
      sf::Vector2f(flock.Sdv_Center_Of_Mass() / 5 - 3,
                   flock.Sdv_Center_Of_Mass() / 5 - 3));

  Sdv_Flock_Velocity.setPosition(10.,
                                 (graph_height - flock.Sdv_Medium_Velocity()));
  Sdv_Flock_Velocity.setPosition(10.,
                                 (graph_height + flock.Sdv_Medium_Velocity()));

  window->draw(Flock_Center);
  window->draw(Sdv_Flock_Center);
  window->draw(Graph);
  window->draw(Sdv_Flock_Velocity);
  window->draw(Data);
}

void Game::Run(sf::RenderWindow* window) {
    
window->setFramerateLimit(FPS);
  Set_Immages();
  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) window->close();
    }
    while (Current_Frame/30 <600) {
            Close_Window(window);
      window->clear(sf::Color(22, 28, 72));
      Play_button();
      if (Get_Play_Check()) {
        flock.Simulation(Set_Predator_Check());
      }
      Draw(window);
      window->display();
      Current_Frame++;
    }
  }
}