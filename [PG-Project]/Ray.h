#include "Vec3.h"
#include <float.h>

class Ray {
private:
    Vec3F origin;
    Vec3F direction;
public:
    Ray(Vec3F origin, Vec3F direction) {
        this->origin = origin;
        this->direction = direction;
    }

    Vec3F getOrigin() {
        return this->origin;
    }

    Vec3F getDirection() {
        return this->direction;
    }
};