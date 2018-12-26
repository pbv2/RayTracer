#pragma once
double Number_PI = 3.14159;

class Vector {
private:
    double x_pos;
    double y_pos;
    double z_pos;
public:
    //Construtores
    Vector ();
    Vector (double n);
    Vector (double x, double y, double z);

    //Metodos
    double getX ();
    double getY ();
    double getZ ();

    //Operadores: Constantes
    Vector operator + (double &n);
    Vector operator - (double &n);
    Vector operator * (double &n);
    Vector operator / (double &n);
    Vector operator += (double &n);

    //Operadores: Vetores
    Vector operator + (Vector &vec);
    Vector operator - (Vector &vec);
    Vector operator * (Vector &vec);
    Vector operator / (Vector &vec);
    Vector operator += (Vector &vec);

    //Operacoes Vetoriais
    Vector negative ();
    double magnitude ();
    double dotProduct (Vector &vec);
    Vector& normalize ();
    Vector crossProduct (Vector &vec);
};
