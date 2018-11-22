#include "Vec3.h"
#include "Ray.h"
#include <cmath>

class Camera {
private:
    Vec3F position;
    Vec3F axisX;
    Vec3F axisY;
    Vec3F axisZ;
    double fov;
    double near;

public:
    Camera(Vec3F position, Vec3F target, Vec3F up, double fov, double near) {
        this->position = position;
        this->target = target;
        this->up = up;
        this->fov = fov;
        this->near = near;
    }

    Ray GetRay(double x, double y, int width, int height) {
        
    }
};