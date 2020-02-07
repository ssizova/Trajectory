//
// Created by Sizov on 24.01.2020.
//

#include "segment.h"
#include <math.h>
#include <iostream>

segment::segment(const sommet &a, const sommet &b) : s1_(a), s2_(b),
                                                     length_(sqrt((s1_.x() - s2_.x()) * (s1_.x() - s2_.x()) +
                                                                  (s1_.y() - s2_.y()) * (s1_.y() - s2_.y()))) {}

double segment::length() const {
    return length_;
}

const sommet &segment::begin() const {
    return s1_;
}

const sommet &segment::end() const {
    return s2_;
}

segment &segment::operator=(const segment &s) {
    s1_ = s.s1_;
    s2_ = s.s2_;
    length_ = s.length_;
    return *this;
}

segment::segment(const segment &s) : s1_(s.s1_), s2_(s.s2_), length_(s.length_) {}

bool intersection(const segment &segment1, const segment &segment2) {
    double alpha1 = det(segment2.end() - segment2.begin(), segment1.begin() - segment2.begin());
    double alpha2 = det(segment2.end() - segment2.begin(), segment1.end() - segment2.begin());
    double alpha3 = det(segment1.end() - segment1.begin(), segment2.begin() - segment1.begin());
    double alpha4 = det(segment1.end() - segment1.begin(), segment2.end() - segment1.begin());


    return (((alpha1 * alpha2 < 0) && (alpha3 * alpha4 < 0) )||(alpha1*alpha2 ==0 && alpha3*alpha4!=0)||
            (alpha3*alpha4 ==0 && alpha1*alpha2!=0));
}



