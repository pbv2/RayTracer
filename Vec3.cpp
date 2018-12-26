#include "Vec3.h"

Vector::Vector () {}
Vector::Vector (double n) : x_pos (n), y_pos (n), z_pos (n) {}
Vector::Vector (double x, double y, double z): x_pos (x), y_pos (y), z_pos (z) {}

double Vector::getX () { return this->x_pos; }
double Vector::getY () { return this->y_pos; }
double Vector::getZ () { return this->z_pos; }

Vector Vector::operator + (double &n) { return Vector (this->x_pos+n, this->y_pos+n, this->z_pos+n); }
Vector Vector::operator - (double &n) { return Vector (this->x_pos-n, this->y_pos-n, this->z_pos-n); }
Vector Vector::operator * (double &n) { return Vector (this->x_pos*n, this->y_pos*n, this->z_pos*n); }
Vector Vector::operator / (double &n) { return Vector (this->x_pos/n, this->y_pos/n, this->z_pos/n); }
Vector Vector::operator += (double &n) { return Vector (this->x_pos+=n, this->y_pos+=n, this->z_pos+=n); }

Vector Vector::operator + (Vector &vec) { return Vector (this->x_pos+vec.x_pos, this->y_pos+vec.y_pos, this->z_pos+vec.z_pos); }
Vector Vector::operator - (Vector &vec) { return Vector (this->x_pos-vec.x_pos, this->y_pos-vec.y_pos, this->z_pos-vec.z_pos); }
Vector Vector::operator * (Vector &vec) { return Vector (this->x_pos*vec.x_pos, this->y_pos*vec.y_pos, this->z_pos*vec.z_pos); }
Vector Vector::operator / (Vector &vec) { return Vector (this->x_pos/vec.x_pos, this->y_pos/vec.y_pos, this->z_pos/vec.z_pos); }
Vector Vector::operator += (Vector &vec) { return Vector (this->x_pos+=vec.x_pos, this->y_pos+=vec.y_pos, this->z_pos+=vec.z_pos); }

Vector Vector::negative () { return Vector (-this->x_pos, -this->y_pos, -this->z_pos); }

double Vector::dotProduct (Vector &vec) { return (this->x_pos*vec.x_pos +
                                                  this->y_pos*vec.y_pos +
                                                  this->z_pos*vec.z_pos); }

double Vector::magnitude () { return sqrt (this->x_pos*this->x_pos +
                                           this->y_pos*this->y_pos +
                                           this->z_pos*this->z_pos); }

Vector& Vector::normalize () {
    double mag = magnitude ();
    
    if (mag != 0) {
        double inverse = 1/mag;
        this->x_pos *= inverse;
        this->y_pos *= inverse;
        this->z_pos *= inverse;
    }

    return *this; }

Vector Vector::crossProduct (Vector &vec) { return Vector (this->y_pos*vec.z_pos - this->z_pos*vec.y_pos,
                                                           this->z_pos*vec.x_pos - this->x_pos*vec.z_pos,
                                                           this->x_pos*vec.y_pos - this->y_pos*vec.x_pos); }