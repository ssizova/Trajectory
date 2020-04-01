cmake_minimum_required(VERSION 3.12)
project(Trajectory)
set(CMAKE_CXX_STANDARD 17)
set ( CMAKE_C_FLAGS "lstdc++fs")
add_executable(Trajectory main.cpp sommet.cpp segment.cpp obstacle.cpp dijkstra.cpp optimal_path.cpp config.cpp no_graph.cpp)


##for gtest
add_subdirectory(gtest)
include_directories(.)
include_directories(test)
add_executable(runTests test/tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

