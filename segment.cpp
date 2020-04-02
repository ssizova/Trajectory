#include "segment.h"

segment::segment(const sommet& beg, const sommet& end) noexcept
  : beg_(beg), end_(end), length_(sqrt((beg_.x() - end_.x())* (beg_.x() - end_.x()) +
  (beg_.y() - end_.y()) * (beg_.y() - end_.y()))) {}

const sommet& segment::begin() const noexcept {
  return beg_;
}

const sommet& segment::end() const noexcept {
  return end_;
}

double segment::length() const noexcept {
  return length_;
}

sommet segment::outer_normal() const noexcept {
  return sommet{ end_.y() - beg_.y(), beg_.x() - end_.x() } *(1. / length());
}

void segment::swap(segment& s) noexcept {
  beg_.swap(s.beg_);
  end_.swap(s.end_);
}

bool operator==(const segment& s1, const segment& s2) noexcept {
  return ((s1.begin() == s2.begin()) && (s1.end() == s2.end())) ||
    ((s1.begin() == s2.end()) && (s1.end() == s2.begin()));
}

bool operator!=(const segment& s1, const segment& s2) noexcept {
  return !(s1 == s2);
}

bool intersection(const segment& s1, const segment& s2) noexcept {

  double alpha1 = det(s2.begin() - s1.begin(), s1.end() - s1.begin());
  double alpha2 = det(s2.end() - s1.begin(), s1.end() - s1.begin());
  double alpha3 = det(s1.begin() - s2.begin(), s2.end() - s2.begin());
  double alpha4 = det(s1.end() - s2.begin(), s2.end() - s2.begin());

  return ((alpha1 * alpha2 <= 0) && (alpha3 * alpha4 < 0)) || ((alpha1 * alpha2 < 0) && (alpha3 * alpha4 <= 0));
}
