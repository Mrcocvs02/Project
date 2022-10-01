#include "Vettore.hpp"

float vettore::get_x() const { return x; };
float vettore::get_y() const { return y; };
void vettore::set_x(float const x_) { x = x_; };
void vettore::set_y(float const y_) { y = y_; };
vettore vettore::operator+(vettore const& b) const {
  return {(x + b.get_x()), (y + b.get_y())};
};
vettore vettore::operator-(vettore const& b) const {
  return {(x - b.get_x()), (y - b.get_y())};
};
vettore vettore::operator*(float const b) const { return {(x * b), (y * b)}; };
vettore vettore::operator/(float const b) const {
  assert(b != 0);
  return {x / b, y / b};
};
double vettore::norm() const { return {std::sqrt(x * x + y * y)}; };
void vettore::print() const {
  std::cout << "(" << x << ", " << y << ")" << '\n';
};

float scalar_prod(vettore const& a, vettore const& b) {
  return a.get_x() * b.get_x() + a.get_y() * b.get_y();
};
float angle
(vettore const& a, vettore const& b) {
  return acos(scalar_prod(a, b) / (a.norm() * b.norm()));
};
