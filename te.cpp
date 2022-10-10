#include <chrono>
#include <numeric>
#include <random>
#include <vector>
#include <iostream>

#include "Boids.hpp"
#include "Vettore.hpp"

int main() {
  for (int i = 0; i < 10; i++) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 random_generator(seed);
    std::uniform_real_distribution<float> position_x(425, 575);
    std::uniform_real_distribution<float> position_y(300, 450);
    float p_x = position_x(random_generator);
    float p_y = position_y(random_generator);

    std::normal_distribution<float> velocity(110., 60.);
    std::uniform_int_distribution<int> sign_x(0, 1);
    float v_x = velocity(random_generator) * (sign_x(random_generator) - 0.5);
    float v_y = velocity(random_generator) * (sign_x(random_generator) - 0.5);
    std::cout <<p_x<<","<<p_y<<"~"<<v_x<<","<<v_y<<'\n';
  }
}