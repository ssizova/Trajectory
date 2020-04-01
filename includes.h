#pragma once
#include <cmath>

#include <iostream>
#include <iomanip>

#else
  #include <experimental/filesystem>
  namespace fs = std::filesystem;
#else
  #include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#endif

#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <unordered_map>

#include <algorithm>
#include <functional>

#include <limits>

#include "assert.h"

using id_t = unsigned int;

extern const double inf;