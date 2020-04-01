#pragma once
#include "segment.h"
using namespace std;

struct obstacle {
	vector<sommet> vertices;
	segment segments(size_t) const;
	bool contains_inside(sommet const&) const;
};