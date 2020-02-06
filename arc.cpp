//
// Created by Sizov on 31.01.2020.
//

#include "arc.h"

arc::arc(const sommet &a, const sommet &b) : s1_(a), s2_(b),
                                             length_(sqrt((s1_.x() - s2_.x()) * (s1_.x() - s2_.x()) +
                                                          (s1_.y() - s2_.y()) * (s1_.y() - s2_.y()))),
                                             weight(0) {}

double arc::length() const {
    return length_;
}

const sommet &arc::begin() const {
    return s1_;
}

const sommet &arc::end() const {
    return s2_;
}

arc &arc::operator=(const arc &s) {
    s1_ = s.s1_;
    s2_ = s.s2_;
    length_ = s.length_;
    weight = s.weight;
    return *this;
}

arc::arc(const arc &s) : s1_(s.s1_), s2_(s.s2_), length_(s.length_), weight(s.weight) {}