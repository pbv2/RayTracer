#include "Object.h"
#include "ObjectIntersection.h"
#include <vector>

class Scene {
private:
    std::vector<Object*> objects;

public:
    bool intersect(const Ray& r, ObjectIntersection* info = NULL) const;

    Vec3 trace(const Ray& r, int recursionLevel = 0) const;

    void add(Object* object);
};