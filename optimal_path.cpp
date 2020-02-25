#include "optimal_path.h"

list<const sommet*>
optimal_path(
	const sommet& start,
	const sommet& finish,
	const vector<obstacle>& obstacles
)
{
	auto num_obstacles = obstacles.size();
	list<const sommet*> res;

	size_t n = 2;
	for (const auto& obstacle_i : obstacles) {
		n += obstacle_i.vertices.size();
		if (obstacle_i.contains_inside(start) || obstacle_i.contains_inside(finish))
			return res;
	}

	auto correct_segment = [&](const segment& s) {
		for (const auto& curr : obstacles) {
			auto num_vertices_of_curr = curr.vertices.size();
			for (id_t k = 0; k < num_vertices_of_curr; k++) {
				const auto& other_s = curr.segments(k);
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
		res.push_back(&start);
		res.push_back(&finish);
		return res;
	}
	
	spar_no_graph g(n);

	vector<const sommet*> vertex_ptrs;
	vertex_ptrs.reserve(n);

	vertex_ptrs.emplace_back(&start );
	vertex_ptrs.emplace_back(&finish);
	id_t index_end = 2;
	for (const auto& obstacle_j : obstacles) {
		const auto& vertices_of_j = obstacle_j.vertices;
		for (const auto& end : vertices_of_j) {
			s = segment{ start, end };
			if (correct_segment(s))
				g.cost(0, index_end) = s.length();
			s = segment{ finish, end };
			if (correct_segment(s))
				g.cost(1, index_end) = s.length();
			++index_end;
		}
	}

	id_t obstacle_i = 0;
	const auto* vertices_of_i = &(obstacles[obstacle_i].vertices);
	auto num_vertices_of_i = vertices_of_i->size();

	id_t vertex_k = 0;
	for (id_t index_beg = 2; index_beg < n-1; ++index_beg) {
		const sommet* beg = &((*vertices_of_i)[vertex_k]);
		vertex_ptrs.emplace_back(beg);
		id_t index_end = index_beg + 1;
		for (id_t vertex_l = vertex_k + 1; vertex_l < num_vertices_of_i; ++vertex_l) {
			const sommet& end = (*vertices_of_i)[vertex_l];
			segment s{ *beg, end };
			if (correct_segment(s))
				g.cost(index_beg, index_end) = s.length();
			++index_end;
		}
		for (id_t obstacle_j = obstacle_i + 1; obstacle_j < num_obstacles; ++obstacle_j) {
			const auto& vertices_of_j = obstacles[obstacle_j].vertices;
			auto num_vertices_of_j = vertices_of_j.size();
			for (id_t vertex_l = 0; vertex_l < num_vertices_of_j; ++vertex_l) {
				const sommet& end = vertices_of_j[vertex_l];
				segment s{ *beg, end };
				if (correct_segment(s))
					g.cost(index_beg, index_end) = s.length();
				++index_end;
			}
		}
		if (++vertex_k == num_vertices_of_i) {
			vertex_k = 0;
			vertices_of_i = &(obstacles[++obstacle_i].vertices);
			num_vertices_of_i = vertices_of_i->size();
		}
	}

	auto indices = dijkstra(0, 1, g);
	for (auto i : indices)
		res.emplace_back(vertex_ptrs[i]);

	return res;
}