#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>
#include "assert.h"
using namespace std;

const double inf = numeric_limits<double>::infinity(); 

using id_t       = unsigned int;
//using vertex_ptr = shared_ptr<sommet>;

class no_graph {
  vector<double> costs_;
  id_t n_;
public:
  no_graph(vector<double> && costs, id_t n)
    : costs_(costs)
    , n_    (n    )
    {}
    
  inline id_t num_vertices() const { return n_; }
  
  double  cost(id_t beg, id_t end) const;
  double& cost(id_t beg, id_t end);
};

list<id_t> dijkstra(id_t, id_t, no_graph const&);