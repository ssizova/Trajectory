//
// Created by Sizov on 24.01.2020.
//

#ifndef TRAJECTORY_SOMMET_H
#define TRAJECTORY_SOMMET_H

#include <memory>
#include <vector>
#include "STL.h"


class sommet {
    using sommet_ptr = unique_ptr<sommet>;
private:
    double x_;
    double y_;
    std::vector<sommet_ptr> next_;

public:
    sommet(double coor_x, double coor_y);

    sommet &operator=(const sommet &s1);

    sommet &operator+=(const sommet &s2);

    sommet &operator-=(const sommet &s2);

    sommet &operator*=(const double &scalar);

    double x();

    double y();

};

sommet operator+(const sommet &s1, const sommet &s2) {
    sommet s = s1;
    return s += s2;
}

sommet operator-(const sommet &s1, const sommet &s2) {
    sommet s = s1;
    return s -= s2;
}

sommet operator*(const double &scalar, sommet s2) {
    return s2 *= scalar;
}

sommet operator*(sommet s2, const double &scalar) {
    return s2 *= scalar;
}

double det(sommet s1, sommet s2) {
    return s1.x() * s2.y() - s1.y() * s2.x();
}

#endif //TRAJECTORY_SOMMET_H
