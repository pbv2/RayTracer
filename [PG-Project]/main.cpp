#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
//#include <cstdlib>
//#include <cstdio>
//#include <cassert>

#define INFINITY 1e8
#define MAX_RAY_DEPTH 5

#include "Imagem.cpp"
#include "Vec3.cpp"
#include "Sphere.cpp"
#include "Ray.cpp"



/*
float mix(const float &a, const float &b, const float &mix) {
    return b * mix + a * (1 - mix);
}
*/

Vector Tracing (Ray *ray, std::vector<Sphere> &spheres, int CurrentDepth) {
    double MoreCloser = INFINITY;
    Sphere* MoreCloserSphere = NULL;

    for (int i = 0; i < spheres.size(); i++) {                                              //Tracando raios para todas as esferas
        double Distance = INFINITY;                                                         //Distancia Infinita caso nao haja intersecao

        if (spheres[i].intersection(ray->getOrigin(), ray->getDirection(), Distance)) {     //Calculo da intersecao
            if (Distance < MoreCloser) {                                                    //Distancia ate a intersecao mais perto
                MoreCloser = Distance;
                MoreCloserSphere = &spheres[i];                                             //Guardando a esfera mais perto
            }
        }
    }

    if (!MoreCloserSphere) return Vector (1);
    if (MoreCloserSphere) return Vector (0);
/*    Vec3f surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
    Vec3f phit = rayorig + raydir * tnear; // point of intersection
    Vec3f nhit = phit - sphere->center; // normal at the intersection point
    nhit.normalize(); // normalize normal direction
    // If the normal and the view direction are not opposite to each other
    // reverse the normal direction. That also means we are inside the sphere so set
    // the inside bool to true. Finally reverse the sign of IdotN which we want
    // positive.
    float bias = 1e-4; // add some bias to the point from which we will be tracing
    bool inside = false;
    if (raydir.dot(nhit) > 0) nhit = -nhit, inside = true;
    if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) {
        float facingratio = -raydir.dot(nhit);

        // change the mix value to tweak the effect
        float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);

        // compute reflection direction (not need to normalize because all vectors
        // are already normalized)
        Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
        refldir.normalize();
        Vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1);
        Vec3f refraction = 0;

        // if the sphere is also transparent compute refraction ray (transmission)
        if (sphere->transparency) {
            float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
            float cosi = -nhit.dot(raydir);
            float k = 1 - eta * eta * (1 - cosi * cosi);
            Vec3f refrdir = raydir * eta + nhit * (eta * cosi - sqrt(k));
            refrdir.normalize();
            refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
        }

        // the result is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColor = (
        reflection * fresneleffect +
        refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
    } else {
        // it's a diffuse object, no need to raytrace any further
        for (unsigned i = 0; i < spheres.size(); ++i) {
            if (spheres[i].emissionColor.x > 0) {
                // this is a light
                Vec3f transmission = 1;
                Vec3f lightDirection = spheres[i].center - phit;
                lightDirection.normalize();
                for (unsigned j = 0; j < spheres.size(); ++j) {
                    if (i != j) {
                        float t0, t1;

                        if (spheres[j].intersect(phit + nhit * bias, lightDirection, t0, t1)) {
                            transmission = 0;
                            break;
                        }
                    }
                }

                surfaceColor += sphere->surfaceColor * transmission *
                std::max(float(0), nhit.dot(lightDirection)) * spheres[i].emissionColor;
            }
        }
    }

    return surfaceColor + sphere->emissionColor;*/
}

void Rendering(Imagem *img, std::vector<Sphere> sphere, double d, double fov) {
    Vector pixels (0);
    int Width = img->getWidth();                    //Largura
    int Height = img->getHeight();                  //Altura

    double xPixelLength = 1/(double)Width;          //Usado para normalizar x
    double yPixelLength = 1/(double)Height;         //Usado para normalizar y

    double Aspectratio = Width/(double)Height;      //Proporcao da tela

    double Alpha = atan(1/d) * 2;                   //Arco do angulo 'Radianos'

    float Angle = tan(Alpha*fov/float(180));        //Angulo de visao

    for (int y = 0; y < Height; ++y) {              //Loop por toda a Imagem (Width x Height)
        for (int x = 0; x < Width; ++x) {
            float xPixel = x + 0.5;                 //Centro do Pixel
            float yPixel = y + 0.5;                 //Centro do Pixel

            xPixel = xPixel*xPixelLength;           //Normalizar [0:1]
            yPixel = yPixel*yPixelLength;           //normalizar [0:1]

            xPixel = 2*xPixel - 1;                  //Range [-1:1]
            yPixel = (2*yPixel - 1) * -1;           //Range [-1:1]

            xPixel = xPixel*Angle;                  //Angulo 'Grau'
            yPixel = yPixel*Angle;                  //Angulo 'Grau'

            if (Width>=Height) {                    //Compensar a diferenca de proporcao
                xPixel = xPixel*Aspectratio;
            } else {
                yPixel = yPixel/Aspectratio;
            }

            Vector rayDir (xPixel, yPixel, -1);
            rayDir.normalize();

            Ray *ray = new Ray (Vector (0), rayDir);

            pixels = Tracing (ray, sphere, 0);
            img->setPixels(pixels.getX(), pixels.getY(), pixels.getZ(), (y*Width) + x);
        }
    }

    img->SaveAsPPM();
}

int main(int argc, char **argv) {
    Imagem *img = new Imagem (1280,720);
    std::vector<Sphere> sphere;

    sphere.push_back(Sphere(Vector(0, -10004, -20), 10000, Vector(0.20, 0.20, 0.20), Vector(0), 0, 0));
    sphere.push_back(Sphere(Vector(0, 0, -20), 4, Vector(1, 0.32, 0.36), Vector(0), 1, 0.5));
    sphere.push_back(Sphere(Vector(5, -1, -15), 2, Vector(0.90, 0.76, 0.46), Vector(0), 1, 0));
    sphere.push_back(Sphere(Vector(5, 0, -25), 3, Vector(0.65, 0.77, 0.97), Vector(0), 1, 0));
    sphere.push_back(Sphere(Vector(-5.5, 0, -15), 3, Vector(0.90, 0.90, 0.90), Vector(0), 1, 0));

    // light
    //sphere.push_back(Sphere(Vector(0, 20, -30), 3, Vector(0, 0, 0),Vector(3), 0, 0));

    Rendering(img, sphere, 1, 30);

    return 0;
}
