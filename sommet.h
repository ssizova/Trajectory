//
// Created by Sizov on 24.01.2020.
//

#ifndef TRAJECTORY_SOMMET_H
#define TRAJECTORY_SOMMET_H

#include <memory>
#include <vector>
//#include "STL.h"


class sommet {
    using sommet_ptr = std::shared_ptr<sommet>;
private:
    double x_;
    double y_;
    std::vector<sommet_ptr> next_;

public:
    sommet(const sommet &);

    sommet() = default;

    sommet(double coor_x, double coor_y);

    sommet &operator=(const sommet &s1);

    sommet &operator+=(const sommet &s2);

    sommet &operator-=(const sommet &s2);

    sommet &operator*=(const double &scalar);

    double x() const;

    double y() const;
};

sommet operator+(sommet s1, const sommet &s2);

sommet operator-(sommet s1, const sommet &s2);

sommet operator*(const double &scalar, sommet s2);

sommet operator*(sommet s2, const double &scalar);

double det(sommet s1, sommet s2);


#endif //TRAJECTORY_SOMMET_H
