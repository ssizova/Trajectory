#pragma once
#include "config.h"
#include "obstacle.h"
using namespace std;

int read_map(
             const filesystem::path& filename,
             sommet * start,
             sommet * finish,
             vector<obstacle> * obstacles
            );