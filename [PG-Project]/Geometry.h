#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "ObjectIntersection.h"
#include <cmath>

class Geometry {
private:
    virtual bool intersect(const Ray& r, ObjectIntersection* info = NULL) const = 0;

    virtual Vec3 getPoint() const = 0;
};

class Sphere : public Geometry {
private:
    Vec3F center;
    double radius;
    double radius2;

public:
    Sphere(Vec3F center, double radius) {
        this->center = center;
        this->radius = radius;
        this->radius2 = radius*radius;
    }

    bool intersect(const Ray& r, ObjectIntersection* info = NULL) const override;

    Vec3F getPoint() const override;
};