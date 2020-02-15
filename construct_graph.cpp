#include "construct_graph.h"

int
construct_graph(
	no_graph * g,
	sommet const& start,
	sommet const& finish,
	vector<obstacle> const& obstacles
) {
	auto num_obstacles = obstacles.size();
	if (num_obstacles == 0) {
		g->cost(0, 1) = segment{start, finish}.length();
		return 1;
	}

	auto n = g->num_vertices();
	for (const auto& curr : obstacles) {
		if (curr.contains_inside(start) || curr.contains_inside(finish))
			return -1;
	}

	id_t obstacle_i = 0;
	auto num_vertices_of_i = obstacles[obstacle_i].vertices.size();

	auto correct_segment = [&](const segment& s) {
		for (id_t i = obstacle_i; i < num_obstacles; i++) {
			const auto& curr = obstacles[i];
			auto num_vertices_of_curr = curr.vertices.size();
			for (id_t j = 0; j < num_vertices_of_curr; j++) {
				const auto& other_s = curr.segments(j);
				if (s == other_s) {
					constexpr double eps = 1e-10;
					sommet adjusted_mid = 0.5 * (s.begin() + s.end()) + eps * other_s.outer_normal();
					return !curr.contains_inside(adjusted_mid);
				}
				if (intersection(s, other_s))
					return false;
			}
			sommet mid = 0.5 * (s.begin() + s.end());
			if (curr.contains_inside(mid))
				return false;
		}
		return true;
	};

	segment s{ start, finish };
	if (correct_segment(s)) {
		g->cost(0, 1) = s.length();
		return 1;
	}
	
	id_t index_end = 2;
	for (id_t obstacle_j = 0; obstacle_j < num_obstacles; ++obstacle_j) {
		const auto& vertices_of_j = obstacles[obstacle_j].vertices;
		for (const auto& end : vertices_of_j) {
			s = segment{ start, end };
			if (correct_segment(s))
				g->cost(0, index_end) = s.length();
			s = segment{ finish, end };
			if (correct_segment(s))
				g->cost(1, index_end) = s.length();
			++index_end;
		}
	}

	id_t vertex_k = 0;
	for (id_t index_beg = 2; index_beg < n-1; ++index_beg) {
		const auto& vertices_of_i = obstacles[obstacle_i].vertices;
		sommet beg = vertices_of_i[vertex_k];
		id_t index_end = index_beg + 1;
		for (id_t vertex_l = vertex_k + 1; vertex_l < num_vertices_of_i; ++vertex_l) {
			sommet end = vertices_of_i[vertex_l];
			segment s{ beg, end };
			if (correct_segment(s))
				g->cost(index_beg, index_end) = s.length();
			++index_end;
		}
		for (id_t obstacle_j = obstacle_i + 1; obstacle_j < num_obstacles; ++obstacle_j) {
			const auto& vertices_of_j = obstacles[obstacle_j].vertices;
			auto num_vertices_of_j = vertices_of_j.size();
			for (id_t vertex_l = 0; vertex_l < num_vertices_of_j; ++vertex_l) {
				sommet end = vertices_of_j[vertex_l];
				segment s{ beg, end };
				if (correct_segment(s))
					g->cost(index_beg, index_end) = s.length();
				++index_end;
			}
		}
		if (++vertex_k == num_vertices_of_i) {
			vertex_k = 0;
			num_vertices_of_i = obstacles[++obstacle_i].vertices.size();
		}
	}

	return 0;
}