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
    Imagem (int w, int h) {
        this->Width = w;
        this->Height = h;
        this->pixels = new RGB_Color [w*h];
    }

    int getWidth () {
        return this->Width;
    }

    int getHeight () {
        return this->Height;
    }

    RGB_Color getPixels (int i) {
        return this->pixels[i];
    }

    void setPixels (double r, double g, double b, int i) {
        this->pixels [i].red = r;
        this->pixels [i].green = g;
        this->pixels [i].blue = b;
    }

    void SaveAsPPM () {
        FILE *f;
        f = fopen("IMAGEM.ppm", "w");

        fprintf(f, "%s\n", "P3");
        fprintf(f, "%d %d\n", this->Width, this->Height);
        fprintf(f,"%d\n", 255);

        for (int i = this->Height - 1 ; i >= 0 ; i --) {
            for (int j = 0 ; j < this->Width ; j ++) {
                int x = this->Width*i + j;
                RGB_Color rgb = getPixels(x);

                double red = (rgb.red)*255;
                double green = (rgb.green)*255;
                double blue = (rgb.blue)*255;

                fprintf(f, "%d %d %d ", (int)red, (int)green, (int)blue);
            }
        }

        fclose(f);
    }
};
