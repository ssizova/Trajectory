#include "optimal_path.h"

list<sommet>
optimal_path(
	const sommet& start,
	const sommet& finish,
	const vector<obstacle>& obstacles
)
{
	list<sommet> path;
	auto num_obstacles = obstacles.size();
	size_t num_vertices = 2;
	for (const auto& obstacle_i : obstacles) {
		num_vertices += obstacle_i.vertices.size();
		if (obstacle_i.contains_inside(start) || obstacle_i.contains_inside(finish))
			return path;
	}

	auto correct_segment = [&](const segment& s) {
		for (const auto& curr : obstacles) {
			bool is_segment_of_curr = false;
			auto num_vertices_of_curr = curr.vertices.size();
			for (auto k = 0; k < num_vertices_of_curr; k++) {
				const auto& other_s = curr.segments(k);
				if (s == other_s) {
					is_segment_of_curr = true;
					constexpr double eps = 1e-10;
					// to avoid approving of segments which lie fully inside its obstacle (case of
					// self-intersections in the obstacle etc.)
					sommet adjusted_mid = 0.5 * (s.begin() + s.end()) + eps * other_s.outer_normal();
					if (curr.contains_inside(adjusted_mid))
						return false;
				}
				if (intersection(s, other_s))
					return false;
			}
			if (!is_segment_of_curr) {
				sommet mid = 0.5 * (s.begin() + s.end());
				if (curr.contains_inside(mid))
					return false;
			}
		}
		return true;
	};

	segment s{ start, finish };
	if (correct_segment(s)) {
		path.push_back(start);
		path.push_back(finish);
		return path;
	}

	spar_no_graph g(num_vertices);
	vector<sommet> all_vertices;
	all_vertices.reserve(num_vertices);
	all_vertices.emplace_back(start);
	all_vertices.emplace_back(finish);
	for (const auto& next_obstacle : obstacles) {
		for (const auto& next_vertex : next_obstacle.vertices) {
			auto n = all_vertices.size();
			for (auto i = 0; i < n; i++) {
				s = segment{ all_vertices[i], next_vertex };
				if (correct_segment(s)) {
					g.cost(i, n) = s.length();
				}
			}
			all_vertices.emplace_back(next_vertex);
		}
	}
	auto path_indices = dijkstra(0, 1, g);
	for (auto i : path_indices)
		path.emplace_back(all_vertices[i]);
	return path;
}