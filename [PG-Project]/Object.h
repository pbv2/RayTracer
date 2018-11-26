#pragma once
#include "Geometry.h"
#include "Material.h"
#include "ObjectIntersection.h"

class Object {
private:
    Geometry* geometry;
    Material* material;

public:
    Object(Geometry* geometry, Material* material);

    bool intersect(const Ray& r, ObjectIntersection* info = NULL);
};