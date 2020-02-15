#include "no_graph.h"

const double inf = numeric_limits<double>::infinity();

//Full graph

full_no_graph::full_no_graph(size_t n) 
: costs_(n*(n-1)/2, inf) {
  n_ = n;
}
double  full_no_graph::cost(id_t i, id_t j) const {
  assert((i < n_) && (j < n_));
  if (i == j) { return 0.; }
  if (i > j) std::swap(i, j);
  return costs_[((2*n_ - i - 1)*i)/2 + j - i - 1];
}
double& full_no_graph::cost(id_t i, id_t j) {
  assert((i < n_) && (j < n_));
  assert(i != j);
  if (i > j) std::swap(i, j);
  return costs_[((2*n_ - i - 1)*i)/2 + j - i - 1];
}

//Sparse graph

spar_no_graph::spar_no_graph(size_t n)
: arcs_(37) {
  n_ = n;
  arcs_.max_load_factor(3);
}
size_t spar_no_graph::arc_hasher::operator()
(arc const& a) const noexcept {
  size_t h_beg = hash<id_t>()(a.beg);
  size_t h_end = hash<id_t>()(a.end);
  return h_end ^ (h_beg << 1);
}
bool spar_no_graph::arc_equal_to::operator()
(arc const& a1, arc const& a2) const noexcept {
  return (a1.beg == a2.beg) && (a1.end == a2.end);
}
double  spar_no_graph::cost(id_t i, id_t j) const {
  assert((i < n_) && (j < n_));
  if (i == j) return 0.;
  if (i > j) std::swap(i, j);
  auto it = arcs_.find(arc{i, j});
  if (it == arcs_.end())
    return inf; 
  else
    return it->second;
}
double& spar_no_graph::cost(id_t i, id_t j) {
  assert((i < n_) && (j < n_));
  assert(i != j);
  if (i > j) std::swap(i, j);
  return arcs_[arc{i, j}];
}