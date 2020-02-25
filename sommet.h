#pragma once
#include "includes.h"

class sommet {
private:
  double x_;
  double y_;

public:
  sommet() = default;
  sommet(const sommet&) noexcept;
  sommet(double, double) noexcept;

  double x() const noexcept;
  double y() const noexcept;

  void swap(sommet&) noexcept;
  sommet& operator= (const sommet&) noexcept;
  sommet& operator+=(const sommet&) noexcept;
  sommet& operator-=(const sommet&) noexcept;
  sommet& operator*=(double) noexcept;
};

bool operator==(const sommet&, const sommet&) noexcept;
bool operator!=(const sommet&, const sommet&) noexcept;
sommet operator+(sommet, const sommet&) noexcept;
sommet operator-(sommet, const sommet&) noexcept;
sommet operator*(double, sommet) noexcept;
sommet operator*(sommet, double) noexcept;
double det(const sommet&, const sommet&) noexcept;
double prod(const sommet&, const sommet&) noexcept;