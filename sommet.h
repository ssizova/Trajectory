#pragma once
#include "includes.h"

class sommet {
private:
  double x_;
  double y_;

public:
  sommet() = default;
  sommet(const sommet&);
  sommet(double, double);

  double x() const;
  double y() const;

  void swap(sommet&);
  sommet& operator= (const sommet&);
  sommet& operator+=(const sommet&);
  sommet& operator-=(const sommet&);
  sommet& operator*=(double);
};

bool operator==(const sommet&, const sommet&);
bool operator!=(const sommet&, const sommet&);
sommet operator+(sommet, const sommet&);
sommet operator-(sommet, const sommet&);
sommet operator*(double, sommet);
sommet operator*(sommet, double);
double det(const sommet&, const sommet&);
