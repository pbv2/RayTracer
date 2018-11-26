#pragma once
#include "Vec3.h"

class Material{
    private:
    double Nome;
    double Ke;
    double Kd;
    double Ks;
    double R;
    double G;
    double B;
    double alpha;
    public:
    
    Material(double Nomen);
    double GetR();
    double GetG();
    double GetB();
    double GetKe();
    double GetKd();
    double GetKs();
    double GetAlpha();
    double GetNome();
    void SetR(double Rn);
    void SetG(double Gn);
    void SetB(double Bn);
    void SetKe(double Ken);
    void SetKd(double Kdn);
    void SetKs(double Ksn);
    void SetAlpha(double alphan);
};