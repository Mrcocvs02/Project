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
  std::vector<Boid> flock;

 public:
  Flock(float d_, float s_, float a_, float c_, int n_);
  std::vector<Boid> get_flock(){return flock;};
};
#endif