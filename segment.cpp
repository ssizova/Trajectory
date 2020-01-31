//
// Created by Sizov on 24.01.2020.
//

#include "segment.h"
#include <math.h>

segment::segment(const sommet &a, const sommet &b) :s1_(a),s2_(b){
//    s1_ = a;
//    s2_ = b;
    length_ = sqrt((s1_.x() - s2_.x()) * (s1_.x() - s2_.x()) + (s1_.y() - s2_.y()) * (s1_.y() - s2_.y()));
}

double segment::length() {
    return length_;
}

sommet segment::begin() {
    return s1_;
}

sommet segment::end() {
    return s2_;
}

segment& segment::operator=(const segment &s) {
    s1_ = s.s1_;
    s2_ = s.s2_;
    length_ = s.length_;
    return *this;
}


