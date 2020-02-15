#include "segment.h"

segment::segment(const sommet& beg, const sommet& end)
: beg_(beg)
, end_(end)
, length_(sqrt((beg_.x() - end_.x()) * (beg_.x() - end_.x()) +
               (beg_.y() - end_.y()) * (beg_.y() - end_.y()))) 
{}

const sommet& segment::begin() const {
  return beg_;
}
const sommet& segment::end() const {
  return end_;
}
double segment::length() const {
  return length_;
}
sommet segment::outer_normal() const {
  return sommet{ end_.y() - beg_.y(), beg_.x() - end_.x() } * (1./length());
}

void segment::swap(segment& s) {
  beg_.swap(s.beg_);
  end_.swap(s.end_);
}

bool operator==(const segment& s1, const segment& s2) {
  return ((s1.begin() == s2.begin()) && (s1.end() == s2.end())) ||
    ((s1.begin() == s2.end()) && (s1.end() == s2.begin()));
}
bool operator!=(const segment& s1, const segment& s2) {
  return !(s1 == s2);
}
bool intersection(const segment &s1, const segment &s2) {
  double alpha1 = det(s2.end() - s2.begin(), s1.begin() - s2.begin());
  double alpha2 = det(s2.end() - s2.begin(), s1.end()   - s2.begin());
  double alpha3 = det(s1.end() - s1.begin(), s2.begin() - s1.begin());
  double alpha4 = det(s1.end() - s1.begin(), s2.end()   - s1.begin());
  return ((alpha1 * alpha2 < 0) && (alpha3 * alpha4 < 0));
}



