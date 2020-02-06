//
// Created by Sizov on 31.01.2020.
//

#ifndef TRAJECTORY_ARC_H
#define TRAJECTORY_ARC_H


#include "sommet.h"

class arc {
private:
    sommet s1_;
    sommet s2_;
    double length_;
    double weight;
public:
    arc() = default;
    arc(const arc &s);
    arc(const sommet &a, const sommet &b);
    double length() const;
    const sommet &begin() const;
    const sommet &end() const;
    arc &operator=(const arc &s);
};


#endif //TRAJECTORY_ARC_H
