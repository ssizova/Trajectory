//
// Created by Sizov on 24.01.2020.
//

#ifndef TRAJECTORY_SOMMET_H
#define TRAJECTORY_SOMMET_H


class sommet {
private:
    double x;
    double y;
public:
    sommet(double coor_x, double coor_y);

    double det(sommet s1, sommet s2);

    sommet operator=(const sommet &s1);

    sommet operator+=(const sommet &s2);

    sommet operator-=(const sommet &s2);

    sommet operator*=(const double &scalar);

};

sommet operator+(const sommet &s1, const sommet &s2) {
    sommet s = s1;
    return s += s2;
}


#endif //TRAJECTORY_SOMMET_H
