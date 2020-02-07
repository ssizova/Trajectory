#include "obstacle.h"

segment obstacle::segments(id_t i) const {
	return segment{ i, (i + 1)%vertices.size() };
}



bool obstacle::contains_inside(sommet const& p) {
  int counter = 0; // the  winding number counter
  auto n = vertices.size();
  for (int i = 0; i < n; i++) {
    sommet beg = vertices[i];
    sommet end = vertices[(i + 1) % n];
    if (beg.y() <= p.y()) { 
      if ((end.y() >  p.y()) && (det(end - beg, p - beg) > 0))  // p left of  edge
        ++counter; // have  a valid up intersect
    }
    else {                      
      if ((end.y() <= p.y()) && (det(end - beg, p - end) < 0))  // p right of edge
        --counter; // have  a valid down intersect
    }
  }
  return counter!=0;
}
}