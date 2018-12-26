#include "Cam.h"

Camera::Camera () {}
Camera::Camera (Vector position, Vector target, Vector up, double fov, double d) :
position(position), target(target), up(up), fov(fov), d(d), right(Vector (0)), Forward(Vector (0)) {
    setConfig ();
}

void Camera::setConfig () {
    this->Forward = (this->position - this->target).normalize();        //Aponta para a parte de tras da Camera -> eixo 'Z' positivo
    this->up = this->up.normalize();                                    //Para cima -> eixo 'Y' positivo
    this->right = this->up.crossProduct(this->Forward).normalize();     //Aponta direita -> eixo 'X' positivo
    setMatrizCam ();
}

Vector Camera::getPosition () { return this->position; }
Vector Camera::getTarget () { return this->target; }
Vector Camera::getUp () { return this->up; }
Vector Camera::getForward () { return this->Forward; }
Vector Camera::getRight () { return this->right; }
double Camera::getFov () { return this->fov; }
double Camera::getD () { return this->d; }

void Camera::setPosition (double px, double py, double pz) {this->position = Vector (px, py, pz); }
void Camera::setTarget (double tx, double ty, double tz) { this->target = Vector (tx, ty, tz); }
void Camera::setUp (double ux, double uy, double uz) { this->up = Vector (ux, uy, uz); }
void Camera::setFov (double fovn) { this->fov = fovn; }
void Camera::setD (double dn) { this->d = dn; }

Ray* Camera::getRay (double x, double y, int Width, int Height) {
    double xPixelLength = 1/(double)Width;              //Usado para normalizar x
    double yPixelLength = 1/(double)Height;             //Usado para normalizar y

    double Aspectratio = Width/(double)Height;          //Proporcao da tela

    double Alpha = atan(1/this->d) * 2;                 //Arco do angulo 'Radianos'

    float Angle = tan(Alpha*this->fov/float(180));      //Angulo de visao

    float xPixel = x + 0.5;                             //Centro do Pixel
    float yPixel = y + 0.5;                             //Centro do Pixel

    xPixel = xPixel*xPixelLength;                       //Normalizar [0:1]
    yPixel = yPixel*yPixelLength;                       //normalizar [0:1]

    xPixel = 2*xPixel - 1;                              //Range [-1:1]
    yPixel = (2*yPixel - 1) * -1;                       //Range [-1:1]

    xPixel = xPixel*Angle;                              //
    yPixel = yPixel*Angle;                              //

    xPixel = xPixel*Aspectratio;                        //Compensar a diferenca de proporcao

    Ray *ray = new Ray (this->position, Vector (xPixel, yPixel, -1).normalize());

    return ray;
}

void Camera::setMatrizCam () {
    //Eixo 'X'
    MatrizCam[0][0] = this->right.getX();
    MatrizCam[0][1] = this->right.getY();
    MatrizCam[0][2] = this->right.getZ();
    MatrizCam[0][3] = double (0);

    //Eixo 'Y'
    MatrizCam[1][0] = this->up.getX();
    MatrizCam[1][1] = this->up.getY();
    MatrizCam[1][2] = this->up.getZ();
    MatrizCam[1][3] = double (0);

    //Eixo 'Z'
    MatrizCam[2][0] = this->Forward.getX();
    MatrizCam[2][1] = this->Forward.getY();
    MatrizCam[2][2] = this->Forward.getZ();
    MatrizCam[2][3] = double (0);

    //Origem da camera
    MatrizCam[3][0] = this->position.getX();
    MatrizCam[3][1] = this->position.getY();
    MatrizCam[3][2] = this->position.getZ();
    MatrizCam[3][3] = double (1);
}

Vector Camera::MatrizToConvertPoint(Vector point) {
	double coordinateX = this->MatrizCam[0][0]*point.getX() +
                             this->MatrizCam[1][0]*point.getY() +
                             this->MatrizCam[2][0]*point.getZ() +
                             this->MatrizCam[3][0]*double(1);

	double coordinateY = this->MatrizCam[0][1]*point.getX() +
                             this->MatrizCam[1][1]*point.getY() +
                             this->MatrizCam[2][1]*point.getZ() +
                             this->MatrizCam[3][1]*double(1);

	double coordinateZ = this->MatrizCam[0][2]*point.getX() +
                             this->MatrizCam[1][2]*point.getY() +
                             this->MatrizCam[2][2]*point.getZ() +
                             this->MatrizCam[3][2]*double(1);

	double coordinateE = this->MatrizCam[0][3]*point.getX() +
                             this->MatrizCam[1][3]*point.getY() +
                             this->MatrizCam[2][3]*point.getZ() +
                             this->MatrizCam[3][3]*double(1);

	coordinateX = coordinateX/coordinateE;
    coordinateY = coordinateY/coordinateE;
    coordinateZ = coordinateZ/coordinateE;

	return Vector (coordinateX, coordinateY, coordinateZ);
}

Vector Camera::MatrizToConvertVector (Vector vetor) {
	double coordinateX = this->MatrizCam[0][0]*vetor.getX() +
                             this->MatrizCam[1][0]*vetor.getY() +
                             this->MatrizCam[2][0]*vetor.getZ();

	double coordinateY = this->MatrizCam[0][1]*vetor.getX() +
                             this->MatrizCam[1][1]*vetor.getY() +
                             this->MatrizCam[2][1]*vetor.getZ();


	double coordinateZ = this->MatrizCam[0][2]*vetor.getX() +
                             this->MatrizCam[1][2]*vetor.getY() +
                             this->MatrizCam[2][2]*vetor.getZ();

	return Vector (coordinateX, coordinateY, coordinateZ);
}
