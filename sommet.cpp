//
// Created by Sizov on 24.01.2020.
//

#include "sommet.h"

double sommet::det(sommet s1, sommet s2) {
    return s1.x * s2.y - s1.y * s2.x;
}

sommet sommet::operator+=(const sommet &s2) {
    x += s2.x;
    y += y2.y;
    return *this;
}

sommet sommet::operator-=(const sommet &s2) {
    x -= s2.x;
    y -= y2.y;
    return *this;
}

sommet sommet::operator*=(const double &scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}
