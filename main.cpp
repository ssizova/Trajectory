#include "config.h"
#include "optimal_path.h"
using namespace std;

int main(int argc, char** argv) {
	cout << "Searching for IO files . . ." << endl;
	io_file_manager(argc, argv);

	cout << "Parsing a map . . ." << endl;
	sommet start;
	sommet finish;
	vector<obstacle> 	obstacles;
	parse_map(input_path(), &start, &finish, &obstacles);

	cout << "Applying Dijkstra algorithm . . ." << endl;
	auto path = optimal_path(start, finish, obstacles);

	cout << "Writing data to output file . . ." << endl;
	write_ptrs(path);

	cout << "Success. See chosen output file for the result!" << endl;
	return 0;
}
