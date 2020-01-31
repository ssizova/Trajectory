#include "sommet.h"

sommet::sommet(double coor_x, double coor_y) {
    x_ = coor_x;
    y_ = coor_y;
}

sommet &sommet::operator=(const sommet &s1) {
    x_ = s1.x_;
    y_ = s1.y_;
//    next_ = s1.next_;
    return *this;
}

sommet &sommet::operator+=(const sommet &s2) {
    x_ += s2.x_;
    y_ += s2.y_;
    return *this;
}

sommet &sommet::operator-=(const sommet &s2) {
    x_ -= s2.x_;
    y_ -= s2.y_;
    return *this;
}

sommet &sommet::operator*=(const double &scalar) {
    x_ *= scalar;
    y_ *= scalar;
    return *this;
}

//sommet &sommet::operator=(const sommet &s1) {
//    x_ = s1.x_;
//    y_ = s1.y_;
////    next_ = s1.next_;
//    return *this;
//}


double sommet::x() {
    return x_;
}

double sommet::y() {
    return y_;
}

sommet::sommet(const sommet &s) {
    x_ = s.x_;
    y_ = s.y_;
}

