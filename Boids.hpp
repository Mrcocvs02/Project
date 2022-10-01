#include "Vettore.hpp"

#ifndef BOID_HPP
#define BOID_HPP

class Boid {
  vettore Position;
  vettore Velocity;
  bool Predator_Check;

 public:
  Boid(vettore const& P, vettore const& V);
  void Set_Position(vettore const& P);
   vettore Get_Position();
   void Set_Velocity(vettore const& V);
   vettore Get_Velocity();

  inline void Set_Predator_Check(bool c);
  inline bool Get_Predator_Check();

  void Wall_Hit();
};

#endif