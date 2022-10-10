#include <numeric>
#include <vector>
#include <random>
#include <chrono>

#include "Boids.hpp"
#include "Vettore.hpp"

#ifndef FLOCK_HPP
#define FLOCK_HPP

class Flock {
  float d;
  float s;
  float a;
  float c;
  int n;
  std::vector<Boid> Flock_;
  Boid Predator;
std::vector<vettore> Obstacles;

 public:
  Flock(float d_, float s_, float a_, float c_, int n_);

  std::vector<Boid> get_flock() { return Flock_; };
  Boid get_predator() { return Predator; };
  void set_predator(Boid const& a) { Predator = a; };
  
  std::vector<vettore> Get_Obstacles(){return Obstacles;};

  vettore Medium_Velocity();
  float Sdv_Medium_Velocity();
  vettore Center_Of_Mass();
  float Sdv_Center_Of_Mass();

  vettore V_Separation_i(int i);
  vettore V_Allignement1_i(int i);
  vettore V_Cohesion_i(int i);
  vettore Predator_Repulsion(int i);
  vettore Obstacles_Repulsion(int i);

  std::vector<int> Boids_Seen(int i);
  void Rules(int i);
  void Set_Velocity(int i);

  void Predator_Simulation();
  void Simulation(bool p_check);
};
#endif