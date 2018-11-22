template <typename T>

class Vector {
private:
    T x_pos;
    T y_pos;
    T z_pos;
public:
    Vector (T n): x_pos (n), y_pos (n), z_pos (n) {}
    Vector (T x, T y, T z): x_pos (x), y_pos (y), z_pos (z) {}

    T getX () const {
        return x_pos;
    }

    T getY () const {
        return y_pos;
    }

    T getZ () const {
        return z_pos;
    }

    //Operacoes dos Vetores

    Vector <T> operator + (const T &n) const {
        return Vector <T> (x_pos+n, y_pos+n, z_pos+n);
    }

    Vector <T> operator + (const Vector <T> &vec) const {
        return Vector <T> (x_pos+vec.x_pos, y_pos+vec.y_pos, z_pos+vec.z_pos);
    }

    Vector <T> operator - (const T &n) const {
        return Vector <T> (x_pos-n, y_pos-n, z_pos-n);
    }

    Vector <T> operator - (const Vector <T> &vec) const {
        return Vector <T> (x_pos-vec.x_pos, y_pos-vec.y_pos, z_pos-vec.z_pos);
    }

    Vector <T> operator * (const T &n) const {
       return Vector <T> (x_pos*n, y_pos*n, z_pos*n);
    }

    Vector <T> operator * (const Vector <T> &vec) const {
        return Vector <T> (x_pos*vec.x_pos, y_pos*vec.y_pos, z_pos*vec.z_pos);
    }

    Vector <T> operator / (const T &n) const {
        return Vector <T> (x_pos/n, y_pos/n, z_pos/n);
    }

    Vector <T> operator / (const Vector <T> &vec) const {
        return Vector <T> (x_pos/vec.x_pos, y_pos/vec.y_pos, z_pos/vec.z_pos);
    }

    Vector <T> operator += (const T &n) const {
        return Vector <T> (x_pos+=n, y_pos+=n, z_pos+=n);
    }

    Vector <T> operator += (const Vector <T> &vec) const {
        return Vector <T> (x_pos+=vec.x_pos, y_pos+=vec.y_pos, z_pos+=vec.z_pos);
    }

    Vector <T> negative () const {
        return Vector <T> (-x_pos, -y_pos, -z_pos);
    }

    T dot_product (const Vector <T> &vec) const {
        return (x_pos*vec.x_pos +
                y_pos*vec.y_pos +
                z_pos*vec.z_pos);
    }

    T magnitude () const {
        return sqrt (x_pos*x_pos +
                     y_pos*y_pos +
                     z_pos*z_pos);
    }

    Vector <T> & normalize () {
        T inverse = 1/magnitude ();
        x_pos *= inverse;
        y_pos *= inverse;
        z_pos *= inverse;
        return *this;
    }

    Vector <T> cross_product (const Vector <T> &vec) const {
        return Vector <T> (y_pos*vec.z_pos - z_pos*vec.y_pos,
                           z_pos*vec.x_pos - x_pos*vec.z_pos,
                           x_pos*vec.y_pos - y_pos*vec.x_pos);
    }

    friend std::ostream & operator << (std::ostream &print, const Vector <T> &vec) {
        print << vec.x_pos << " " << vec.y_pos << " " << vec.z_pos;
        return print;
    }
};

typedef Vector<float> Vec3F;
