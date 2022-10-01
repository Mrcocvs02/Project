#include "Boids.hpp"

#include "Vettore.hpp"

Boid::Boid(vettore const& P, vettore const& V)
    : Position{P}, Velocity{V}, Predator_Check{false} {}

 void Boid::Set_Position(vettore const& P) { Position = P; }
 vettore Boid::Get_Position() { return Position; }
 void Boid::Set_Velocity(vettore const& V) { Velocity = V; }
 vettore Boid::Get_Velocity() { return Velocity; }

inline void Boid::Set_Predator_Check(bool c) {}
inline bool Boid::Get_Predator_Check() { return Predator_Check; }
void Boid::Wall_Hit() {
  if ((Position.get_x() <= 25) || (Position.get_x() >= 1175)) {
    Velocity.set_x(1.5 * Velocity.get_x());
  }
  if ((Position.get_y() <= 25) || (Position.get_y() >= 625)) {
    Velocity.set_y(1.5 * Velocity.get_y());
  }
}
