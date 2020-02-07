cmake_minimum_required(VERSION 3.12)
project(Trajectory)
set(CMAKE_CXX_STANDARD 17)

add_executable(Trajectory main.cpp sommet.cpp segment.cpp no_graph.cpp dijkstra.cpp read_map.cpp test/tests.cpp)

##for gtest
#include_directories(.)
#find_package(GTest REQUIRED)
#include_directories(test)
#add_executable(runTests test/tests.cpp)
#target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
#
##add_executable(Trajectory main.cpp sommet.cpp segment.cpp arc.cpp graphe.cpp dijkstra.cpp)
#add_executable(Trajectory main.cpp sommet.cpp segment.cpp arc.cpp graphe.cpp dijkstra.cpp)
