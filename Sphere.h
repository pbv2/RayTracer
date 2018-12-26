#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "Material.h"

class Sphere {
public:
    Material material;
    Vector center;
    double radius;
    double radius2;
//public:
    //Construtor
    Sphere (Vector center, double radius, Material material);

    //Metodos
    Vector getCenter ();
    double getRadius ();
    Material getMaterial ();
    
    //Normal do ponto de intersecao na esfera
    Vector getNormal (Vector point);

    //Indica se houve ou nao intersecao com a esfera
    bool intersection (Vector rayOrigin, Vector rayDirection, double &distance);
};