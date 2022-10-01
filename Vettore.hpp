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
  void set_x(float const x_);
  float get_y() const;
  void set_y(float const y_);

  vettore operator+(vettore const& b) const;
  vettore operator-(vettore const& b) const;
  vettore operator*(float const b) const;
  vettore operator/(float const b) const;
  double norm() const;
  void print() const;
};

float scalar_prod(vettore const& a, vettore const& b);
float angle(vettore const& a, vettore const& b);

#endif
