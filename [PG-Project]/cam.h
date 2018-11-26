#pragma once
#include "Vec3.h"
#include "Ray.h"

class Camera {
private:
    Vector position;
    //Vector axisX;
    //Vector axisY;
    //Vector axisZ;
    double fov;
    double near;
public:
    //Construtor
    Camera(Vector position, double fov, double near);

    //Metodos
    Ray GetRay(double x, double y, int width, int height);
};