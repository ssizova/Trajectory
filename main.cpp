#include "config.h"
#include "read_map.h"
#include "dijkstra.h"
#include "construct_graph.h"
using namespace std;

int main(int argc, config::value_type** argv) {
	config::file_name(argv[0]);

	sommet start;
	sommet finish;
	vector<obstacle> 	obstacles;

	int flag_reading = read_map(config::input_file(), &start, &finish, &obstacles);
	cout << flag_reading << endl << endl;

	size_t n = 2;
	for (const auto& curr : obstacles)
		n += curr.vertices.size();
	spar_no_graph G{ n };

	int flag_construction = construct_graph(&G, start, finish, obstacles);
	cout << flag_construction << endl << endl;

	auto path = dijkstra(0, 1, G);

	config::output(path);

	return 0;
}
