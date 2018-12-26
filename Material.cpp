#include "Material.h"

Material::Material () {}
Material::Material (std::string Nome, double red, double green, double blue, double Kd, double Ks, double Ke, double alpha) : Nome(Nome), Kd(Kd), Ks(Ks), Ke(Ke), alpha(alpha) {
    this->color.r = red;
    this->color.g = green;
    this->color.b = blue;
}

std::string Material::getNome () { return this->Nome; }

double Material::getR () { return this->color.r; }
double Material::getG () { return this->color.g; }
double Material::getB () { return this->color.b; }

double Material::getKe () { return this->Ke; }
double Material::getKd () { return this->Kd; }
double Material::getKs () { return this->Ks; }
double Material::getAlpha () { return this->alpha; }
