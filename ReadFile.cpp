class File {
public:
    void ConfigurationImagem (std::istringstream &parameters, Imagem &img) {
        int Width = atoi(Reading(parameters).c_str());
        int Height = atoi(Reading(parameters).c_str());

        img.setWidth (Width);
        img.setHeight (Height);
        img.setLength ();
        img.setRGB_Color ();
    }

    void ConfigurationCamera (std::istringstream &parameters, Camera &cam) {
        double px = atof(Reading(parameters).c_str());
        double py = atof(Reading(parameters).c_str());
        double pz = atof(Reading(parameters).c_str());
        double tx = atof(Reading(parameters).c_str());
        double ty = atof(Reading(parameters).c_str());
        double tz = atof(Reading(parameters).c_str());
        double ux = atof(Reading(parameters).c_str());
        double uy = atof(Reading(parameters).c_str());
        double uz = atof(Reading(parameters).c_str());
        double fov = atof(Reading(parameters).c_str());
        double d = atof(Reading(parameters).c_str());

        cam.setPosition (px, py, pz);
        cam.setTarget (tx, ty, tz);
        cam.setUp (ux, uy, uz);
        cam.setFov (fov);
        cam.setD (d);
        cam.setConfig ();
    }

    void ConfigurationMaterial (std::istringstream &parameters, std::vector<Material> &materiais) {
        std::string material = Reading(parameters);

        double r = atof(Reading(parameters).c_str());
        double g = atof(Reading(parameters).c_str());
        double b = atof(Reading(parameters).c_str());
        double kd = atof(Reading(parameters).c_str());
        double ks = atof(Reading(parameters).c_str());
        double ke = atof(Reading(parameters).c_str());
        double alpha = atof(Reading(parameters).c_str());

        materiais.push_back(Material(material, r, g, b, kd, ks, ke, alpha));
    }

    void ConfigurationSphere (std::istringstream &parameters, std::vector<Sphere> &spheres, std::vector<Material> &materiais){
        double cx = atof(Reading(parameters).c_str());
        double cy = atof(Reading(parameters).c_str());
        double cz = atof(Reading(parameters).c_str());
        double r = atof(Reading(parameters).c_str());
        std::string material = Reading(parameters);
        int index = 0;
        bool b = false;

        for (int i = 0 ; i < materiais.size() ; i ++) {
            if (materiais[i].getNome() == material) {
                index = i;
                i = materiais.size();
                b = true;
            }
        }

        if (!b) { std::cout << "Material nao existe" << std::endl; } else {
            spheres.push_back(Sphere(Vector (cx, cy, cz), r, materiais[index]));
        }
    }

    void ConfigurationLight (std::istringstream &parameters, std::vector<Light> &lights){
        double px = atof(Reading(parameters).c_str());
        double py = atof(Reading(parameters).c_str());
        double pz = atof(Reading(parameters).c_str());
        double r = atof(Reading(parameters).c_str());
        double g = atof(Reading(parameters).c_str());
        double b = atof(Reading(parameters).c_str());
        double intensity = atof(Reading(parameters).c_str());

        lights.push_back(Light(Vector (px, py, pz), Vector (r, g, b), intensity));
    }

    void ReadingFile (Imagem &img, Camera &cam, std::vector<Material> &materiais, std::vector<Sphere> &spheres, std::vector<Light> &lights) {
        std::ifstream File ("./Configurations.txt");
        std::string Line;

        while(std::getline(File, Line)){
            if (Line[0] == '#' || Line.empty()) { continue; }
            else {
                std::string command, options;
                std::istringstream parameters (Line);

                options = Reading (parameters);

                if (options == "resolution") {
                    ConfigurationImagem (parameters, img);
                } else if (options == "camera") {
                    ConfigurationCamera (parameters, cam);
                } else if (options == "material") {
                    ConfigurationMaterial (parameters, materiais);
                } else if (options == "sphere") {
                    ConfigurationSphere (parameters, spheres, materiais);
                } else if (options == "light") {
                    ConfigurationLight (parameters, lights);
                }
            }
        }
    }

    std::string Reading (std::istringstream &parameters){
        std::string option;
        getline (parameters, option, ' ');
        return option;
    }
 };
