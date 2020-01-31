//
// Created by Sizov on 31.01.2020.
//

#ifndef TRAJECTORY_GRAPHE_H
#define TRAJECTORY_GRAPHE_H


#include <list>
#include "arc.h"
#include <queue>

class graphe {
private:
    std::list<arc> edges;
    std::queue<sommet> bypass; //for marking visited sommets. Maybe it will be necessary
    void add_arc(const arc &a1);

};


#endif //TRAJECTORY_GRAPHE_H
