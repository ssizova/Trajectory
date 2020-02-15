#pragma once
#include "no_graph.h"
#include "obstacle.h"
using namespace std;

int
construct_graph(
	no_graph * g,
	sommet const& start,
	sommet const& finish,
	vector<obstacle> const& obstacles
);
