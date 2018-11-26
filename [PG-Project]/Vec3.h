#pragma once

class Vector {
private:
    double x_pos;
    double y_pos;
    double z_pos;
public:
    //Construtores
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

    /*friend std::ostream & operator << (std::ostream &print, const Vector <T> &vec) {
        print << vec.x_pos << " " << vec.y_pos << " " << vec.z_pos;
        return print;
    }*/
};
