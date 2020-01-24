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
    double det(sommet s1, sommet s2);

    sommet operator+=(const sommet &s2);

    sommet operator-=(const sommet &s2);

    sommet operator*=(const double &scalar);


};


#endif //TRAJECTORY_SOMMET_H
