#pragma once
#include "includes.h"
using namespace std;

int
read_map(
          string const& filename,
          sommet * start,
          sommet * finish,
          vector<obstacle> * obstacles
        );