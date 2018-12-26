#include "Light.h"

Light::Light (Vector position, Vector color, double i) : position(position), color(color), intensity(i) {}

Vector Light::getColor () { return this->color; }
double Light::getIntensity () { return this->intensity; }
Vector Light::getPosition () { return this->position; }

Vector Light::getIntensityPoint (Vector point) {
    //Intensidade da luz em um ponto:
    //IntensidadeLuzPonto = Li / Area, onde
    //Li: intensidade da luz
    //Area: area circular, ou seja, 4 * Pi * R^2

    Vector Distance (this->position - point);
    Vector Li = this->color * this->intensity;
    double Area = 4 * Number_PI * Distance.dotProduct(Distance);

    return Li/Area;
}
double Light::getDistance (Vector point) {
    Vector Distance (this->position - point);
    Vector DistanceN = Distance;
    DistanceN = DistanceN.normalize ();

    return DistanceN.dotProduct(Distance);
}

Vector Light::getDirection (Vector point) {
    return Vector (point - this-> position).normalize();
}