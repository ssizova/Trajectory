#include "no_graph.h"

//const double inf = numeric_limits<double>::infinity();
const double inf = std::numeric_limits<double>::infinity();
//Full graph

full_no_graph::full_no_graph(id_t n) 
: costs_(n*(n-1)/2, inf) {
  n_ = n;
}
double  full_no_graph::cost(id_t beg, id_t end) const {
  assert((beg < n_) && (end < n_));
  if   (end == beg) { return 0.; }
  id_t i, j;
  if   (end  < beg) { i = end; j = beg; }
  else              { i = beg; j = end; }
  return costs_[((2*n_ - i - 1)*i)/2 + j - i - 1]; 
}
double& full_no_graph::cost(id_t beg, id_t end) {
  assert((beg < n_) && (end < n_));
  assert(beg != end);
  id_t i, j;
  if   (end < beg) { i = end; j = beg; }
  else              { i = beg; j = end; }
  return costs_[((2*n_ - i - 1)*i)/2 + j - i - 1]; 
}

//Sparse graph

spar_no_graph::spar_no_graph(id_t n)
: arcs_(37) {
  n_ = n;
  arcs_.max_load_factor(0.3);
}
size_t spar_no_graph::arc_hasher::operator()
(arc const& a) const noexcept {
  size_t h_beg = hash<id_t>()(a.beg);
  size_t h_end = hash<id_t>()(a.end);
  return h_end ^ (h_beg << 1);
}
bool spar_no_graph::arc_equal_to::operator()
(arc const& a1, arc const& a2) const noexcept {
  return ((a1.beg == a2.beg) && (a1.end == a2.end)) ||
         ((a1.beg == a2.end) && (a1.end == a2.beg));
}
double  spar_no_graph::cost(id_t beg, id_t end) const {
  assert((beg < n_) && (end < n_));
  if (beg == end) return 0.;
  auto it = arcs_.find(arc{beg, end});
  if (it == arcs_.end())
    return inf;
  else
    return it->second;
}
double& spar_no_graph::cost(id_t beg, id_t end) {
  assert((beg < n_) && (end < n_));
  assert(beg != end);
  return arcs_[arc{beg, end}];
}
