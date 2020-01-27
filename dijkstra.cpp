#include "dijkstra.h"

double  no_graph::cost(id_t beg, id_t end) const {
  assert((beg < n_) && (end < n_));
  if   (end == beg) { return 0.; }
  id_t i, j;
  if   (end  < beg) { i = end; j = beg; }
  else              { i = beg; j = end; }
  return costs_[((2*n_ - i - 1)*i)/2 + j - i - 1]; 
}
double& no_graph::cost(id_t beg, id_t end) {
  assert((beg < n_) && (end < n_));
  assert(beg != end);
  id_t i, j;
  if   (end  < beg) { i = end; j = beg; }
  else              { i = beg; j = end; }
  return costs_[((2*n_ - i - 1)*i)/2 + j - i - 1]; 
}

list<id_t> dijkstra(id_t s, id_t t, no_graph const& g) {
  auto n = g.num_vertices();
  vector<double> path_l(n, inf);
  path_l.shrink_to_fit();
  path_l[s] = 0.;
  vector<id_t> path_p;
  path_p.reserve(n);
  list<id_t> unvisited;
  for (id_t i = 0; i < n; i++) {
    unvisited.push_back(i);
  } // list contains 0, 1, 2, ..., n-1
  id_t curr = s;
  while (curr != t) {
    auto iter = min_element(unvisited.begin(), unvisited.end(),
                [&](id_t i1, id_t i2)->bool {
                  return path_l[i1] < path_l[i2];                    
                }); // find where we 
    curr = *iter;
    unvisited.erase(iter);
    for (auto next : unvisited) {
      double way = path_l[curr] + g.cost(curr, next);
      if (way < path_l[next]) {
        path_p[next] = curr;
        path_l[next] = way;
      }
    }
  }
  list<id_t> path(1, curr);
  while (curr != s) {
    curr = path_p[curr];
    path.push_front(curr);
  }
  return path;
}