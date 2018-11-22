#pragma once

#include <vector>
#include "Vec3.h"

class Image {
    private:
    int width, heigth;
    std::vector,Vec3. buffer;

    public:
    Image(in width, int heigth);

    void SetPixel(int x,int y, cont Vec3& color);

    void SaveAsPBM(const std::string& filePath) const;
}