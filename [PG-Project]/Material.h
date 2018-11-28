#pragma once
#include <iostream>
#include <string>

class Material{
    private:
    std :: string Nome;
    double Ke;
    double Kd;
    double Ks;
    double R;
    double G;
    double B;
    double alpha;
    public:
    
    Material(std :: string Nomen);
    double GetR();
    double GetG();
    double GetB();
    double GetKe();
    double GetKd();
    double GetKs();
    double GetAlpha();
    std :: string GetNome();
    void SetR(double Rn);
    void SetG(double Gn);
    void SetB(double Bn);
    void SetKe(double Ken);
    void SetKd(double Kdn);
    void SetKs(double Ksn);
    void SetAlpha(double alphan);
};