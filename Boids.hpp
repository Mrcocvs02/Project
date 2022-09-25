#include "Vettore.hpp"


#ifndef BOID_HPP
#define BOID_HPP

class Boid {
    
  vettore Position;
  vettore Velocity;
  bool Predator_Check;

 public:
  Boid();
  inline void Set_Position(vettore& P);
   vettore Get_Position();
  inline void Set_Velocity(vettore& V);
  inline const vettore Get_Velocity();
  inline void Set_Predator_Check(bool c);
  inline bool Get_Predator_Check();
  void Wall_Hit();
};

#endif