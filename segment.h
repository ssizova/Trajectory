//
// Created by Sizov on 24.01.2020.
//

#ifndef TRAJECTORY_SEGMENT_H
#define TRAJECTORY_SEGMENT_H

#include "sommet.h"

class segment {
private:
    sommet s1;
    sommet s2;
    double length;
public:
    segment(sommet s1, sommet s2);
};


#endif //TRAJECTORY_SEGMENT_H
