#pragma once
#include "segment.h"
using namespace std;

struct obstacle {
	vector<sommet> vertices;
	segment segments(id_t) const;
	bool contains_inside(sommet const&) const;
};