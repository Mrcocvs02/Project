#include <iostream>
#include "Graphic.hpp"

int main(){
    srand (time(NULL));
     int n;
  std::cout << "insert the number of birds you want in the flock" << '\n';
  std::cin >> n;
    while (n <= 0 || n > 1000)
  { // Controlla che il numero inserito sia valido e in caso contrario dà il relativo messaggio di errore
    if (n > 1000)
    {
      std::cout << "Do you want to hurt your pc? If you care about it reduce the number of boids otherwise you will overload it. Please re-enter the number of boids you would like to see in the flock (possibly a valid one this time): ";
      std::cin >> n;
    }
    else
    {
      if (n == 0)
      {
        std::cout << "I can assure you that a flock with zero boids isn't very fun to watch... Please re-enter the number of boids you would like to see in the flock (possibly a valid one this time): ";
        std::cin >> n;
      }
      else
      {
        std::cout << "Have you ever seen a flock with a NEGATIVE number of boids? Please re-enter the number of boids you would like to see in the flock (possibly a valid one this time): ";
        std::cin >> n;
      }
    }
  }
  std::cout << "press d to use default parameters," << '\n'
            << "or press s to choose them" << '\n';
  char condition;
  std::cin >> condition;
  std::cout << '\n';
  if ((condition != 100) && (condition != 115)) {
    throw std::runtime_error("invalid condition");
  }
  if (condition == 100) {
    std::cout << "P = stop-start flock movement" << '\n'
              << "C = stop predator movement" << '\n'
              << "A = start predator movement" << '\n'
              << "left-right-up-down = move the predator" << '\n'
              << "esc = close the simulation" << '\n';
    sf::RenderWindow window(sf::VideoMode(1200, 650), "Simulation");
    Game game(10., 0.5, 0.05, 0.01, n);
    game.Run(&window);
  }
  if (condition == 115) {
    std::cout << "insert separation distance" << '\n';
    float d;
    std::cin >> d;
    std::cout << '\n' << "insert separation coefficient" << '\n';
    float s;
    std::cin >> s;
    std::cout << '\n' << "insert allineament coefficient" << '\n';
    float a;
    std::cin >> a;
    std::cout << '\n' << "insert cohesion coefficient" << '\n';
    float c;
    std::cin >> c;
    std::cout << '\n'
              << "P = stop-start flock movement" << '\n'
              << "C = stop predator movement" << '\n'
              << "A = start predator movement" << '\n'
              << "left-right-up-down = move the predator" << '\n'
              << "esc = close the simulation" << '\n'
              << '\n'
              << "insert any key to start the simulation" << '\n';
     sf::RenderWindow window(sf::VideoMode(1200,650),
                          "Simulation");
     Game game(d, s, a, c,n);
     game.Run(&window);
  }
}
