#pragma once
#include "Vec3.h"
#include "Ray.h"

class Camera {
private:
    Vector position;
    Vector target;
    Vector up;
    Vector Forward;
    Vector right;
    double fov;
    double d;
    double MatrizCam [4][4];
public:
    //Construtor
    Camera ();
    Camera (Vector position, Vector target, Vector up, double fov, double d);

    //Configurar vetores da Camera
    void setConfig ();

    //Metodos
    Vector getPosition ();
    Vector getTarget ();
    Vector getUp ();
    Vector getForward ();
    Vector getRight ();
    double getFov ();
    double getD ();

    void setPosition (double px, double py, double pz);
    void setTarget (double tx, double ty, double tz);
    void setUp (double ux, double uy, double uz);
    void setFov (double fovn);
    void setD (double dn);
    
    //Criar raio de Ray Tracing
    Ray* getRay (double x, double y, int width, int height);

    //Criar matriz de conversao Camera->Mundo
    void setMatrizCam ();

    //Operacoes da matriz
    Vector MatrizToConvertPoint (Vector point);
    Vector MatrizToConvertVector (Vector vector);
};