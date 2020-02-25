#pragma once
#include "dijkstra.h"
#include "obstacle.h"
using namespace std;

list<const sommet*>
optimal_path(
	const sommet& start,
	const sommet& finish,
	const vector<obstacle>& obstacles
);
