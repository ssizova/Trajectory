#include "dijkstra.h"

list<size_t> dijkstra(const size_t s, const size_t t, const no_graph& g) {
  auto n = g.num_vertices();
  vector<double> path_l(n, inf);
  path_l[s] = 0.;
  vector<size_t> path_p(n);
  forward_list<size_t> unvisited;
  for (auto i = 0; i < n; i++) {
    unvisited.emplace_front(i);
  } // list of unvisited vertices
  auto curr = s;
  while (curr != t) {
    auto it_before_min = unvisited.before_begin();
    auto it_min  = unvisited.begin();
    auto it_last = unvisited.end();
    auto it_prev = unvisited.begin();
    auto it_curr = it_prev;
    ++it_curr;
    while (it_curr != it_last) {
      if (path_l[*it_curr] < path_l[*it_min]) {
        it_min        = it_curr;
        it_before_min = it_prev;
      }
      ++it_prev;
      ++it_curr;
    }
    curr = *it_min;
    unvisited.erase_after(it_before_min);
    for (const auto next : unvisited) {
      double way = path_l[curr] + g.cost(curr, next);
      if (way < path_l[next]) {
        path_p[next] = curr;
        path_l[next] = way;
      }
    }
  }
  list<size_t> path(1, curr);
  while (curr != s) {
    curr = path_p[curr];
    path.push_front(curr);
  }
  return path;
}