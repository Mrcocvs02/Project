#include <cassert>
#include <cmath>
#include <iostream>

#ifndef VETTORE_HPP
#define VETTORE_HPP

class vettore {
  float x;
  float y;

 public:
  vettore(float x_, float y_) : x{x_}, y{y_} {}

  float get_x() const;
  void set_x(float x_);
  float get_y() const;
  void set_y(float x_);

  vettore operator+(vettore const& b) const;
  vettore operator-(vettore const& b) const;
  vettore operator*(float const b) const;
  vettore operator/(float const b) const;
  double norm() const;
  void print() const;
};

float scalar_prod(vettore const& a, vettore const& b);
float angle_between_vectors(vettore const& a, vettore const& b);

#endif
