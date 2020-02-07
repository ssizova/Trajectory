#include "dijkstra.h"
#include "construct_graph.h"
using namespace std;

double det(sommet s1, sommet s2) {
    return s1.x() * s2.y() - s1.y() * s2.x();
}

int main() {
    sommet x3(0.0, 1.0);
    sommet x4(0.0, 0.0);
    sommet x1(0, 0);
    sommet x2(5, 0);
    segment s1(x1, x2);
    segment s2(x3, x4);
    sommet x = x1 + x2;
    cout << intersection(s1,s2);
    /*
    string filename = "";
    sommet start;
    sommet finish;
    vector<obstacle> obstacles;
    read_map(filename, &start, &finish, &obstacles);
    id_t n = 2;
    for (auto curr : obstacles) {
        n += curr.vertices.size();
    }
    full_no_graph g(n);
    int flag = construct_graph(&g, start, finish, obstacles);
    if (flag == -1) {
        cerr << "start/finish point inside obstacle" << endl;
        return -1;
    }
    if (flag == 1) {
        list<sommet> path = { start, finish };
        output(path);
    }
    auto path_indices = dijkstra(g, 0, 1);
    output(output_indices);
    */
    full_no_graph g{ 3 };
    sommet start { 0., 0. };
    sommet finish{ 1., 2. };
    vector<obstacle> obstacles;
    int flag = construct_graph(&g, finish, start, obstacles);
    return 0;
}