#include "sommet.h"
#include <memory>

sommet::sommet(double coor_x, double coor_y) {
    x_ = coor_x;
    y_ = coor_y;
    next_.push_back(nullptr);
}

sommet &sommet::operator=(const sommet &s1) {
    x_ = s1.x_;
    y_ = s1.y_;
    for (auto &i : s1.next_) {
        next_.push_back(std::move(i));
    }
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

double sommet::x() const {
    return x_;
}

double sommet::y() const {
    return y_;
}

sommet::sommet(const sommet &s) {
    x_ = s.x_;
    y_ = s.y_;
    for (const auto &i : s.next_) {
        next_.push_back(std::move(i));
    }
}

sommet operator+(sommet s1, const sommet &s2) {

    return s1 += s2;
}

sommet operator-(sommet s1, const sommet &s2) {
    return s1 -= s2;
}

sommet operator*(const double &scalar, sommet s2) {
    return s2 *= scalar;
}

sommet operator*(sommet s2, const double &scalar) {
    return s2 *= scalar;
}