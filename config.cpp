#include "config.h"

namespace config {
	path& input_file(value_type* arg = nullptr) {
		static path res{ arg };
		return res;
	}
	path& output_file(value_type* arg = nullptr) {
		static path res{ arg };
		return res;
	}
	template<class Container>
	void output(const Container& c) {
		filesystem::copy_file(input_file(), output_file(), filesystem::copy_options::overwrite_existing);
		ofstream out(output_file(), ios::app);
		out << endl;
		out << "[$OptPath]" << endl;
		for (const auto& elem : c) {
			out << elem << endl;
		}
		out.close();
	}

  namespace {
    bool section_find(ifstream& in, const string& sectname, const path& filename) {
      string line;

      while (getline(in, line) && line.find(sectname) != 0);
      if (in.eof()) {
        cerr << "EOF while looking for " << sectname << " section" << endl;
        return false;
      }
      cerr << line << endl;
      return true;
    }
    bool out_of_numeric_limits(id_t x) {
      if (x >= numeric_limits<id_t>::max()) {
        cerr << "Format id_t is too small to handle" << endl;
        return true;
      }
      return false;
    }
  }

  int
  read_map(
      const path& filename,
      sommet* start,
      sommet* finish,
      vector<obstacle>* obstacles
    ) {
    //Create input stream
    ifstream conf(filename);

    //Check file consistency
    if (!conf.good()) {
      cerr << "Cannot open map file" << endl;
      return -1;
    }

    double x, y, r;

    string_type section;

    //Parse $Start section

    if (!section_find(conf, "[$Start]", filename)) return -1;
    conf >> x >> y;
    *start = sommet{ x,y };

    //Parse $Finish section
    if (!section_find(conf, "[$Finish]", filename)) return -1;
    conf >> x >> y;
    *finish = sommet{ x,y };

    //Parse $Obstacles section
    if (!section_find(conf, "[$NumObstacles]", filename)) return -1;
    id_t num_obstacles;
    conf >> num_obstacles;
    if (out_of_numeric_limits(num_obstacles)) return -1;
    obstacles->reserve(num_obstacles);

    // Parse $Nodes section
    if (!section_find(conf, "[$Nodes]", filename)) return -1;
    for (id_t i = 0; i < num_obstacles; i++) {
      obstacles->emplace_back(obstacle{});
      auto& curr = (*obstacles)[i];
      id_t num_nodes_i;
      conf >> num_nodes_i;
      if (out_of_numeric_limits(num_nodes_i)) return -1;
      if (num_nodes_i < 3) {
        cerr << "Invalid number of nodes in obstacle " << i << endl;
        return -1;
      }
      curr.vertices.reserve(num_nodes_i);
      for (id_t j = 0; j < num_nodes_i; j++) {
        conf >> x >> y;
        curr.vertices.emplace_back(sommet{ x,y });
      }
    }
    conf.close();
    return 0;
  }
}