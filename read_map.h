#pragma once
#include "includes.h"
#include "sommet.h"
#include "obstacle"
using namespace std;

int
read_map(
          string const& filename,
          sommet * start,
          sommet * finish,
          vector<obstacle> * obstacles
        );