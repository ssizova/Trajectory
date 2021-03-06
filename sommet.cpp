#include "sommet.h"

sommet::sommet(double x, double y) noexcept : x_(x), y_(y) {}
sommet::sommet(const sommet& s) noexcept : x_(s.x_), y_(s.y_) {};

double sommet::x() const noexcept {
  return x_;
}
double sommet::y() const noexcept {
  return y_;
}

void sommet::swap(sommet& s) noexcept {
  using std::swap;
  swap(x_, s.x_);
  swap(y_, s.y_);
}
sommet& sommet::operator= (const sommet& s) noexcept{
  x_ = s.x_;
  y_ = s.y_;
  return *this;
}
sommet& sommet::operator+=(const sommet& s) noexcept{
  x_ += s.x_;
  y_ += s.y_;
  return *this;
}
sommet& sommet::operator-=(const sommet& s) noexcept{
  x_ -= s.x_;
  y_ -= s.y_;
  return *this;
}
sommet& sommet::operator*=(double scalar) noexcept{
  x_ *= scalar;
  y_ *= scalar;
  return *this;
}

bool operator==(const sommet& p1, const sommet& p2) noexcept {
  return (p1.x() == p2.x()) && (p1.y() == p2.y());
}
bool operator!=(const sommet& p1, const sommet& p2) noexcept {
  return !(p1 == p2);
}
sommet operator+(sommet s1, const sommet &s2) noexcept {
  return s1 += s2;
}
sommet operator-(sommet s1, const sommet &s2) noexcept {
  return s1 -= s2;
}
sommet operator*(double scalar, sommet s) noexcept {
  return s *= scalar;
}
sommet operator*(sommet s, double scalar) noexcept {
  return s *= scalar;
}
double det(const sommet& s1, const sommet& s2) noexcept {
  return s1.x() * s2.y() - s1.y() * s2.x();
}
double prod(const sommet& s1, const sommet& s2) noexcept {
  return s1.x() * s2.x() + s1.y() * s2.y();
}