#include "construct_graph.h"

int
construct_graph(
	full_no_graph* g,
	sommet const& start,
	sommet const& finish,
	vector<obstacle> const& obstacles
)
{
	auto n = g->num_vertices();
	for (auto curr : obstacles) {
		if (curr.contains_inside(start) || curr.contains_inside(finish))
			return -1;
	}

	id_t vertex_i = 0;
	id_t obstacle_i = 0;
	auto obstacle_size = obstacles[obstacle_i].vertices.size();

	auto correct_segment = [&](segment const& s) {
		for (id_t i = obstacle_i; i < obstacles.size(); i++) {
			auto const& curr = obstacles[obstacle_i];
			if (curr.contains_inside(0.5 * (s.beg() + s.end()))) return false;
			for (id_t j = 0; j < curr.vertices.size(); j++)
				if (intersect(s, curr.segments(j))) return false;
		}
		return true;
	}

	segment s{ start, finish };
	if (correct_segment(s)) return 1;

	for (id_t obstacle_j = 0; obstacle_j < obstacles.size(); obstacle_j++) {
		for (auto end : obstacles[j].vertices) {
			s = segment{ start, end };
			if (correct_segment(s))
				g->cost(0, obstacle_j) = s.length();
			s = segment{ finish, end };
			if (correct_segment(s))
				g->cost(1, obstacle_j) = s.length();
		}
	}

	for (id_t index_beg = 2; index_beg < n; index_beg++) {
		sommet beg = obstacles[obstacle_i].vertices[vertex_i];
		id_t index_end = index_beg + 1;
		for (id_t vertex_j = vertex_i + 1; vertex_j < obstacle_size; vertex_j++) {
			sommet end = obstacles[obstacle_i].vertices[vertex_j];
			segment s{ beg, end };
			if (correct_segment(s))
				g->cost(index_beg, index_end) = s.length();
			index_end++;
		}
		for (id_t obstacle_j = obstacle_i + 1; obstacle_j < obstacles.size(); obstacle_j++) {
			for (id_t vertex_j = 0; vertex_j < obstacles[j].vertices.size(); vertex_j++) {
				sommet end = obstacles[j].vertices[vertex_j];
				segment s{ beg, end };
				if (correct_segment(s))
					g->cost(index_beg, index_end) = s.length();
				index_end++;
			}
		}
		if (vertex_i < obstacle_size - 1)
			vertex_i++;
		else {
			vertex_i = 0;
			obstacle_i++;
			obstacle_size = obstacles[obstacle_i].size();
		}
	}

	return 0;
}