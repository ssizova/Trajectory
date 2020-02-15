#pragma once
#include "sommet.h"

class segment {
private:
  sommet beg_;
  sommet end_;
  double length_;

public:
  segment() = default;
  segment(const segment&) = default;
  segment(const sommet&, const sommet&);

  const sommet& begin() const;
  const sommet& end() const;
  double length() const;
  sommet outer_normal() const;

  void swap(segment&);
  segment& operator=(const segment &) = default;
};

bool operator==(const segment&, const segment&);
bool operator!=(const segment&, const segment&);
bool intersection(const segment&, const segment&);