//
// Created by Sizov on 24.01.2020.
//

#ifndef TRAJECTORY_SEGMENT_H
#define TRAJECTORY_SEGMENT_H

#include "sommet.h"
#include <memory>

class segment {
private:
    sommet s1_;
    sommet s2_;
    double length_;

public:
    segment(const sommet &a, const sommet &b);
    double length();
    sommet begin();
    sommet end();
    segment &operator=(const segment &s);

};


#endif //TRAJECTORY_SEGMENT_H
