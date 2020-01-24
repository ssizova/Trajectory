#include "sommet.h"
sommet::sommet(double coor_x, double coor_y) {
    x_ = coor_x;
    y_ = coor_y;
    next_ = nullptr;
    return *this;
}

sommet &sommet::operator+=(const sommet &s2) {
    x_ += s2.x;
    y_ += y2.y;
    return *this;
}

sommet &sommet::operator-=(const sommet &s2) {
    x_ -= s2.x;
    y_ -= y2.y;
    return *this;
}

sommet &sommet::operator*=(const double &scalar) {
    x_ *= scalar;
    y_ *= scalar;
    return *this;
}

sommet &sommet::operator=(const sommet &s1) {
    x = s1.x;
    y = s1.y;
    return *this;
}




double sommet::x() {
    return x_;
}

double sommet::y() {
    return y_;
}
