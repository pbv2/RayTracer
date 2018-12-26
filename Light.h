#pragma once
#include "Vec3.h"

class Light {
private:
    Vector position;
    Vector color;
    double intensity;
public: 
    //Construtor
    Light (Vector position, Vector color, double i);
    
    //Metodos
    Vector getColor (); 
    double getIntensity ();
    Vector getPosition ();
    
    Vector getIntensityPoint (Vector point);
    double getDistance (Vector point);
    Vector getDirection (Vector point);
};