#include "Material.h"
#include <string>
#include <iostream>
 Material::Material(std :: string Nomen){
     Nome =Nomen;
 }
   double Material::GetR(){
        return this->R;
    }
    double Material::GetG(){
        return this->G;
    }
    double Material::GetB(){
        return this->B;
    }
    double Material::GetKe(){
        return this->Ke;
    }
    double Material::GetKd(){
        return this->Kd;
    }
    double Material::GetKs(){
        return this->Ks;
    }
    double Material::GetAlpha(){
        return this->alpha;
    }
    std :: string Material::GetNome(){
        return this->Nome;
    }
    void Material::SetR(double Rn){
        this->R=Rn;
    }
    void Material::SetG(double Gn){
        this->G=Gn;
    }
    void Material::SetB(double Bn){
        this->B=Bn;
    }
    void Material::SetKe(double Ken){
        this->Ke=Ken;
    }
    void Material::SetKd(double Kdn){
        this->Kd=Kdn;
    }
    void Material::SetKs(double Ksn){
        this->Ks=Ksn;
    }
    void Material::SetAlpha(double alphan){
        this->alpha=alphan;
    }