#include "sphere.h"

Sphere::Sphere (Vector center, double radius, Material material) : center (center), radius (radius), radius2 (radius*radius), material(material) {}

Vector Sphere::getCenter () { return this->center; }
double Sphere::getRadius () { return this->radius; }
Material Sphere::getMaterial () { return this->material; }

bool Sphere::intersection (Vector rayOrigin, Vector rayDirection, double &distance) {
    Vector centerToSphere = this->center - rayOrigin;                                           //Vetor que aponta para o centro da esfera
    double centerToSphereLength = centerToSphere.dotProduct(rayDirection);                      //Projecao do vetor centerToSphere no vetor rayDirection

    if (centerToSphereLength >=0) {                                                            //Menor que '0' significa que esta atras da Camera
        double h2 = centerToSphere.dotProduct(centerToSphere) - pow(centerToSphereLength, 2);

        if (this->radius2 >= h2) {                                                             //Menor que o raio significa que nao toca na esfera
            double sidePointToIntersection = sqrt (this->radius2 - h2);
            distance = centerToSphereLength - sidePointToIntersection;

            if (distance < 0) {                                                                 //Toca a esfera em um ponto atras da Camera
                distance = centerToSphereLength + sidePointToIntersection;
            }

            return true;
        }
    }

    return false;
}

Vector Sphere::getNormal (Vector point) {
    return (point - this->center).normalize();
}
