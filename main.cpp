#include <iostream>
#include "segment.h"

double det(sommet s1, sommet s2) {
    return s1.x() * s2.y() - s1.y() * s2.x();
}

int main() {
    sommet x3(0.0, 1.0);
    sommet x4(0.0, 0.0);
    sommet x1(0, 0);
    sommet x2(5, 0);
    segment s1(x1, x2);
    segment s2(x3, x4);
    sommet x = x1 + x2;
    std::cout<< intersection(s1,s2);

    return 0;


}