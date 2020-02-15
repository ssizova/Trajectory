#pragma once
#include "includes.h"
using namespace std;

struct no_graph {
  inline size_t num_vertices() const {
    return n_;
  }
  virtual double  cost(id_t, id_t) const = 0;
  virtual double& cost(id_t, id_t) = 0;
protected:
  size_t n_;
};

struct full_no_graph : no_graph {
  explicit full_no_graph(size_t);
  virtual double  cost(id_t, id_t) const override;
  virtual double& cost(id_t, id_t) override;
private:
  vector<double> costs_;
};

struct spar_no_graph : no_graph {
  explicit spar_no_graph(size_t);
  virtual double  cost(id_t, id_t) const override;
  virtual double& cost(id_t, id_t) override;
private:
  struct arc {
    id_t beg, end;
  };
  struct arc_hasher {
    size_t operator()(arc const&) const noexcept;
  };
  struct arc_equal_to {
    bool operator()(arc const&, arc const&) const noexcept;
  };
  unordered_map<arc,double,arc_hasher,arc_equal_to> arcs_;
};