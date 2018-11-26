#pragma once
#include "Vec3.h"

class Ray {
private:
    Vector origin;
    Vector direction;
public:
    //Construtor
    Ray(Vector origin, Vector direction);

    //Metodos
    Vector getOrigin();
    Vector getDirection();
};
