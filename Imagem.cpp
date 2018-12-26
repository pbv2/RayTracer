#include "Imagem.h"

Imagem::Imagem () {};
Imagem::Imagem (int Width, int Height) : Width(Width), Height(Height), length(Width*Height), pixels(new RGB_Color [Width*Height]) {}

int Imagem::getWidth () { return this->Width; }
int Imagem::getHeight () { return this->Height; }

void Imagem::setWidth (int width) { this->Width = width; }
void Imagem::setHeight (int height) { this->Height = height; }
void Imagem::setLength () { this->length = this->Width*this->Height; }
void Imagem::setRGB_Color () { this->pixels = new RGB_Color[this->Width*this->Height]; }

RGB_Color Imagem::getPixels (int i) { return this->pixels [i]; }

void Imagem::setPixels (double r, double g, double b, int i) {
    this->pixels [i].red = r;
    this->pixels [i].green = g;
    this->pixels [i].blue = b; }

void Imagem::SaveAsPPM () {
    FILE *f;
    f = fopen("IMAGEM.ppm", "w");

    fprintf(f, "%s\n", "P3");
    fprintf(f, "%d %d\n", this->Width, this->Height);
    fprintf(f,"%d\n", 255);

    for (int i = 0 ; i < this->length ; i ++) {
        RGB_Color rgb = getPixels(i);

        double red = std::min(double (1), (rgb.red))*255;
        double green = std::min(double (1), (rgb.green))*255;
        double blue = std::min(double (1), (rgb.blue))*255;

        fprintf(f, "%d %d %d ", (int)red, (int)green, (int)blue);
    }

    fclose(f);
}