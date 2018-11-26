#include "Ray.h"

Ray::Ray(Vector origin, Vector direction) : origin(origin), direction(direction) {}

Vector Ray::getOrigin() { return this->origin; }
Vector Ray::getDirection() { return this->direction; }
