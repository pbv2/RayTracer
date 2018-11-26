#pragma once
#include "Vec3.h"
#include "Ray.h"

class Sphere {
public:
    //Material material;
    Vector center;
    double radius;
    double radius2;

    Vector surfaceColor, emissionColor; /// surface color and emission (light)
    double transparency, reflection; /// surface transparency and reflectivity

//public:
    //Construtor
    //Sphere (Vector center, double radius);
    Sphere (Vector center, double radius, Vector surfaceColor, Vector emissionColor, double transparency, double reflection);

    //Metodos
    Vector getCenter ();
    double getRadius ();

    bool intersection(Vector rayOrigin, Vector rayDirection, double &distance);
};
