#pragma once

struct RGB_Color {
	double red;
	double green;
	double blue;
};

class Imagem {
private:
    int Width;
    int Height;
    RGB_Color *pixels;
public:
    //Construtor
    Imagem (int w, int h);

    //Metodos
    int getWidth ();
    int getHeight ();
    RGB_Color getPixels (int i);

    //Colorindo o Pixel
    void setPixels (double r, double g, double b, int i);

    //Salvando uma Imagem em PPM
    void SaveAsPPM ();
};
