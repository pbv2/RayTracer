#include "Imagem.h"

Imagem::Imagem (int width, int height) : Width(width), Height(height), pixels(new RGB_Color[width*height]) {}

int Imagem::getWidth () { return this->Width; }
int Imagem::getHeight () { return this->Height; }

RGB_Color Imagem::getPixels (int i) { return this->pixels[i]; }

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

    for (int i = 0 ; i < this->Height ; i ++) {
        for (int j = 0 ; j < this->Width ; j ++) {
            int x = this->Width*i + j;
            RGB_Color rgb = getPixels(x);

            double red = (rgb.red)*255;
            double green = (rgb.green)*255;
            double blue = (rgb.blue)*255;

            fprintf(f, "%d %d %d ", (int)red, (int)green, (int)blue);
        }
    }

    fclose(f); }