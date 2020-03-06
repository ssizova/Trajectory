#include "config.h"

namespace {
  bool section_find(ifstream& in, const string& sectname, const fs::path& filename) {
    string line;
    while (getline(in, line) && line.find(sectname) != 0);
    if (in.eof()) {
      cerr << "EOF while looking for " << sectname << " section" << endl;
      return false;
    }
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

int io_file_manager(int argc, char** argv) {
  if (--argc > 0)
    input_path() = argv[1];
  else {
    cerr << "WARNING expected first console argument. ";
    const string default_input_name = "input.txt";
    cerr << "Replacing with " << default_input_name << " . . ." << endl;
    input_path() = fs::path{ default_input_name };
  }
  if (--argc > 0)
    output_path() = argv[2];
  else {
    cerr << "WARNING expected second console argument. ";
    const string default_output_name = "output.txt";
    cerr << "Replacing with " << default_output_name << " . . ." << endl;
    output_path() = fs::path{ default_output_name }; 
  }
  if (--argc > 0) {
    cerr << "WARNING too many arguments : last arguments in input ignored" << endl;
  }
  return 0;
}
fs::path& input_path() {
  static fs::path res{};
  return res;
}
fs::path& output_path() {
  static fs::path res{};
  return res;
}

int
parse_map(
  const fs::path& filepath,
  sommet* const start,
  sommet* const finish,
  vector<obstacle>* const obstacles
) {
  //  Create input stream, constructor (5) from here:
  //  https://en.cppreference.com/w/cpp/io/basic_ifstream/basic_ifstream
  ifstream conf(filepath);

  //Check file consistency
  if (!conf.good()) {
    cerr << "Cannot open map file" << endl;
    return -1;
  }

  double x, y, r;

  //Parse $Start section
  if (!section_find(conf, "[$Start]", filepath)) return -1;
  conf >> x >> y >> r;
  *start = sommet{ x,y };

  //Parse $Finish section
  if (!section_find(conf, "[$Finish]", filepath)) return -1;
  conf >> x >> y;
  *finish = sommet{ x,y };

  //Parse $Obstacles section
  if (!section_find(conf, "[$NumObstacles]", filepath)) return -1;
  id_t num_obstacles;
  conf >> num_obstacles;
  if (out_of_numeric_limits(num_obstacles)) return -1;
  obstacles->reserve(num_obstacles);

  // Parse $Nodes section
  if (!section_find(conf, "[$PtsObstacles]", filepath)) return -1;
  for (id_t i = 0; i < num_obstacles; i++) {
    obstacles->emplace_back(obstacle{});
    auto* const vertices_of_i = &((*obstacles)[i].vertices);
    id_t num_nodes_i;
    conf >> num_nodes_i;
    if (out_of_numeric_limits(num_nodes_i)) return -1;
    if (num_nodes_i < 3) {
      cerr << "Invalid number of nodes in obstacle " << i << endl;
      return -1;
    }

    // here we introduce a simple algorithm how to parse a graph

    // this lambda not only checks whether segments of construction are parallel
    // but also parses to the obstacle object as many nodes of a construction as needed
    auto segments_analyzer = [&](vector<sommet> * const vertices,
      sommet * const prev,
      sommet * const curr,
      const sommet & next) {
      bool res = true;

      auto n1 = segment{ *prev, *curr }.outer_normal();
      auto n2 = segment{ *curr,  next }.outer_normal();

      double sin_phi = det(n1, n2); // sin of angle between n1 and n2

      constexpr double tol = 1e-12;
      if (abs(sin_phi) >= tol) {
        // ok, segments are not parallel, thus, its intersection
        // is significant
        res = false;
        // we consider 2 cases
        if (sin_phi < 0.) {
          // polygon obstacle_i is concave in vertex curr
          // no smooth reconstruction of the 
          // boundary needed
          // we adjust boundary on radius r
          double cos_phi = prod(n1, n2);
          double k = sin_phi / (1. + cos_phi);
          sommet inner_angle_shift = r * sommet{ n1.x() - k * n1.y(), k * n1.x() + n1.y() };
          vertices->emplace_back(*curr + inner_angle_shift); // curr + shift = new angle point
        }
        else {
          // polygon obstacle_i is convex in vertex curr
          // compute smooth arc betwenn 2 successive shifts of curr

          if (r < tol)
            vertices->emplace_back(*curr);
          else {
            constexpr double arc_0 = 1e-2; // relative length to consider
            int num_parts = (int)(r*sin_phi/arc_0) + 1;
            for (int k = 0; k <= num_parts; k++) {
              double sin_phi_k = k * sin_phi / num_parts;
              double cos_phi_k = sqrt(1. - sin_phi_k * sin_phi_k);
              sommet outer_angle_shift = r * sommet{ cos_phi_k * n1.x() - sin_phi_k * n1.y(),
                                                     sin_phi_k * n1.x() + cos_phi_k * n1.y() };
              vertices->emplace_back(*curr + outer_angle_shift);
            }
          }
        }
        *prev = *curr; 
      }
      *curr = next; // we do a step forward in our cycle
      return res;
    };

    conf >> x >> y;
    sommet prev{ x,y };  // read firse vertex
    conf >> x >> y;
    sommet curr{ x,y };  // read second vertex

    sommet first = prev;
    sommet second = curr; // memorize them in special variables
                          // we will get back to them later

    auto reading_segment = bind(segments_analyzer, vertices_of_i, &prev, &curr, placeholders::_1);

    for (id_t j = 3; j <= num_nodes_i; j++) {
      conf >> x >> y;
      sommet next{ x,y }; // read next vertex
      reading_segment(next);
    }
    // but there are still two missing constructions to consider
    reading_segment(first);
    if (reading_segment(second))
    // the last segment is parallel to the first one
      (*vertices_of_i)[0] = prev;
    // all the nodes of this obstacle processed
  } // all obstacles processed
  conf.close();
  return 0;
}