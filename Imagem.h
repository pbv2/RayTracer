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
    int length;
    RGB_Color *pixels;
public:
    //Construtor
    Imagem ();
    Imagem (int Width, int Height);

    //Metodos
    int getWidth ();
    int getHeight ();

    void setWidth (int width);
    void setHeight (int height);
    void setLength ();
    void setRGB_Color ();

    RGB_Color getPixels (int index);

    //Colorindo o Pixel
    void setPixels (double red, double green, double blue, int index);

    //Salvando uma Imagem em PPM
    void SaveAsPPM ();
};