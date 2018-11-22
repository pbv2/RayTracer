#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

#include "Vec3.h"
#include "imagem.h"


using namespace std;


//vector<Sphere> &spheres


void render(Imagem *img, float fov) {
    Vec3F pixel (0);
    int Width = img->getWidth();
    int Height = img->getHeight();

    float invWidth = 1/(float)Width;
    float invHeight = 1/(float)Height;

    float Aspectratio = Width/(float)Height;
    float Angle = tan(M_PI*0.5*fov/(float)180);

    for (int y = 0; y < Height; ++y) {
        for (int x = 0; x < Width; ++x) {
            float xx = (2*((x+0.5)*invWidth)-1)*Angle*Aspectratio;
            float yy = (1-2*((y+0.5)*invHeight))*Angle;

            Vec3F raydir(xx, yy, -1);
            raydir.normalize();
            img->setPixels((double)pixel.getX(),(double)pixel.getY(),(double)pixel.getZ(), y*Height + x);
        }
    }

    img->SaveAsPPM();
}

int main (int argc, char *argv[]) {
    int Width = 640;
	int Height = 480;
	Imagem *img = new Imagem(Width, Height);

    for (int i = 0 ; i < Width*Height; i++) {
        img->setPixels(0,0,0,i);
    }
    render(img,30);
    //img->SaveAsPPM();

    int x = 2;
    int y = 5;
    x *= y;
    cout << x << endl;
    x -= 1;
    cout << x << endl;
    x += 1;
    cout << x << endl;
    x /= y;
    cout << x << endl;


    Vec3F v1 (0.25);
    Vec3F v2 (0.25, 0.5, 0.25);
    float scalar = 2;

    Vec3F r = v1.cross_product(v2);

    cout << v1.getX() << " " << v1.getY() << " " << v1.getZ() << endl;

    cout << r << endl;

    r.normalize();

    cout << r << endl;

    cout << sqrt(r.dot_product(r)) << endl;

    cout << r.magnitude() << endl;

    cout << r*scalar << endl;

    cout << "aaa" << endl;

    cout << v2.negative() << endl;

    return 0;
}
