#pragma once
#include "includes.h"
#unclude "sommet.h"
#include "segment.h"

using namespace std;

struct {
	vector<sommet> vertices;
	segment segments(id_t) const;
	bool contains_inside(sommet const&) const;
};