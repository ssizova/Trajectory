#pragma once
#include "dijkstra.h"
#include "obstacle.h"
using namespace std;

list<sommet>
optimal_path(
	const sommet& start,
	const sommet& finish,
	const vector<obstacle>& obstacles
);
