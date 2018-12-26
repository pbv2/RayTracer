#pragma once

struct RGB {
    double r;
    double g;
    double b;
};

class Material {
private:
    std::string Nome;
    RGB color;
    double Ke;
    double Kd;
    double Ks;
    double alpha;
public:
    //Construtores
    Material ();
    Material (std::string Nome, double red, double green, double blue, double Kd, double Ks, double Ke, double alpha);

    //Metodos
    std::string getNome ();
    double getR ();
    double getG ();
    double getB ();
    double getKe ();
    double getKd ();
    double getKs ();
    double getAlpha ();
};
