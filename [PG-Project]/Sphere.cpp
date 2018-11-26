#include "sphere.h"

//Sphere::Sphere (Vector center, double radius) : center(center), radius(radius), radius2(radius*radius) {}
Sphere::Sphere (Vector center, double radius, Vector surfaceColor, Vector emissionColor, double transparency, double reflection) :
        center (center), radius (radius), radius2 (radius*radius), surfaceColor (surfaceColor),
        emissionColor (emissionColor), transparency (transparency), reflection (reflection) {}

Vector Sphere::getCenter () { return this->center; }
double Sphere::getRadius () { return this->radius; }

bool Sphere::intersection(Vector rayOrigin, Vector rayDirection, double &distance) {
        Vector centerToSphere = this->center - rayOrigin;
        double centerToSphereLength = centerToSphere.dotProduct(rayDirection);

        if (centerToSphereLength >=0 ) {                                            //Menor que ' 0 ' significa que esta atras da Camera
            double h2 = centerToSphere.dotProduct(centerToSphere) - pow(centerToSphereLength,2);

            if (this->radius2>=h2) {                                                      //Menor que o raio significa que nao toca na esfera
                double sidePointToIntersection = sqrt (this->radius2-h2);
                distance = centerToSphereLength - sidePointToIntersection;

                if (distance < 0) {                                                 //Toca a esfera em um ponto atras da Camera
                    distance = centerToSphereLength + sidePointToIntersection;
                }

                return true;
            }
        }

        return false;
}
