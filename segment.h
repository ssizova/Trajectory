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
    segment() = default;
    segment(const segment &s);
    segment(const sommet &a, const sommet &b);
    double length() const;
    const sommet &begin() const;
    const sommet &end() const;
    segment &operator=(const segment &s);
};
bool intersection(const segment &s1, const segment &s2);

#endif //TRAJECTORY_SEGMENT_H
