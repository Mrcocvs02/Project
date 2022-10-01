#include <numeric>
#include <vector>

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
  std::vector<Boid> flock_;
  Boid predator;

 public:
  Flock(float d_, float s_, float a_, float c_, int n_);

  std::vector<Boid> get_flock() { return flock_; };
  Boid get_predator() { return predator; };
  void set_predator(Boid const& a) { predator = a; };

  vettore medium_velocity();
  float sdv_medium_velocity();
  vettore center_of_mass();
  float sdv_center_of_mass();

  vettore v_separation_i(int j);
  vettore v_allignement1_i(int j);
  vettore v_cohesion_i(int j);
  vettore predator_repulsion(int j);

  std::vector<int> boids_seen(int j);
  void rules(int j);
  void set_velocities(int j);

  void predator_simulation();
  void simulation(bool p_check);
};
#endif