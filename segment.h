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
  segment(const sommet&, const sommet&) noexcept;

  const sommet& begin() const noexcept;
  const sommet& end() const noexcept; 
  double length() const noexcept;
  sommet outer_normal() const noexcept;

  void swap(segment&) noexcept;
  segment& operator=(const segment &) = default;
};

bool operator==(const segment&, const segment&) noexcept;
bool operator!=(const segment&, const segment&) noexcept;
bool intersection(const segment&, const segment&) noexcept;