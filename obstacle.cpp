#include "obstacle.h"

segment obstacle::segments(size_t i) const {
  auto n = vertices.size();
  assert(i < n);
	return segment{vertices[i], vertices[(i + 1) % n]};
}
bool obstacle::contains_inside(const sommet& p) const {
  int counter = 0; // the  winding number counter
  auto n = vertices.size();
  for (size_t i = 0; i < n; i++) {
    const sommet& beg = vertices[i];
    const sommet& end = vertices[(i + 1) % n];
    if (beg.y() <= p.y()) { 
      if ((end.y() >  p.y()) && (det(end - beg, p - beg) > 0.)) // p left of edge
        ++counter; // a valid up intersect
    }
    else {                      
      if ((end.y() <= p.y()) && (det(end - beg, p - beg) < 0.)) // p right of edge
        --counter; // a valid down intersect
    }
  }
  return (counter != 0);
}
