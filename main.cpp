#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "Cam.cpp"
#include "Imagem.cpp"
#include "Light.cpp"
#include "Material.cpp"
#include "Ray.cpp"
#include "Sphere.cpp"
#include "Vec3.cpp"
#include "ReadFile.cpp"

#define INFINITY 1000000

double Bias = 0.0001;
Material background;

struct Data {
    int index;
    double distance;
    bool intersection;
};

//Realiza a intersecao com todas as esferas e retorna informacoes sobre a esfera mais proxima (caso exista ao menos uma intersecao
Data TracingSpheres (Vector &Origin, Vector &Direction, std::vector<Sphere> &spheres) {
    Data data;
    data.intersection = false;                                          //"false"    -> caso nao haja intersecao
    data.distance = INFINITY;                                           //"INFINITY" -> caso nao haja intersecao

    double Distance;

    for (int i = 0 ; i < spheres.size() ; i++) {                        //Tracando raios para todas as esferas
        Distance = INFINITY;                                            //Distancia Infinita caso nao haja intersecao

        if (spheres[i].intersection (Origin, Direction, Distance)) {    //Verificando se ha intersecao
            if (Distance < data.distance) {                             //Selecionando a intersecao mais proxima
                data.index = i;                                         //Salvando indice
                data.distance = Distance;                               //Salvando distancia
                data.intersection = true;                               //Indicando que houve ao menos 1 intersecao
            }
        }
    }

    return data;
}

//Verifica se existe alguma esfera entre o ponto de intersecao da esfera com o raio da camera e este ponto e uma das luzes do ambiente
bool TracingShadows (Vector PointOfIntersection, Vector inverseLightDirection, std::vector<Sphere> &spheres, double DistanceLight) {
    Data data;
    data.intersection = false;                                                                  //"false" -> caso nao haja intersecao
    data.distance = DistanceLight;                                                              //Isso evita que esferas atras da luz sejam consideradas no calculo da intersecao
                                                                                                //evitando que uma intersecao atras da luz seja considerada como se ocorrece na frente desta
    double Distance;

    for (int i = 0 ; i < spheres.size() ; i++) {                                                //Tracando raios para todas as esferas
        Distance = INFINITY;                                                                    //Distancia Infinita caso nao haja intersecao

        if (spheres[i].intersection (PointOfIntersection, inverseLightDirection, Distance)) {   //Verificando se ha intersecao
            if (Distance < data.distance) {                                                     //Selecionando a intersecao mais proxima
                data.index = i;                                                                 //Salvando indice
                data.distance = Distance;                                                       //Salvando distancia
                data.intersection = true;                                                       //Indicando que houve ao menos 1 intersecao
            }
        }
    }

    return data.intersection;
}

//Metodo que chama e recebe os resultados sobre as intersecoes com as esferas e realiza o calculo
//do quanto de luz um ponto irá receber e, por fim, retorma a cor daquele ponto
//Considera luz Difusa, especular e ambiente
Vector Tracing (Ray *ray, std::vector<Sphere> &spheres, std::vector<Light> light) {
    Vector rayOrigin = ray->getOrigin ();          //Origem do raio
    Vector rayDirection = ray->getDirection ();    //Direcao do raio

    Data data = TracingSpheres (rayOrigin, rayDirection, spheres);                                      //Calculando intersecoes com as esferas

    if (!data.intersection) {
        return Vector (background.getR(), background.getG(), background.getB());                        //Caso não ocorra intersecao, retorna com de fundo
    } else {
        //Paramentros do material da esfera
        Material materialSphere = spheres[data.index].getMaterial();
        Vector SphereAlbedo (materialSphere.getR(), materialSphere.getG(), materialSphere.getB());
        double Kd = materialSphere.getKd(), Ks = materialSphere.getKs(), Ke = materialSphere.getKe(), Alpha = materialSphere.getAlpha();

        //Paramentros para cor
        Vector ColorPoint (0);
        Vector diffuse (0);
        Vector specular (0);
        Vector environment (0);

        //Pontos e Vetores base -> Sphere
        Vector rayD = rayDirection * data.distance;
        Vector PointOfIntersection = rayOrigin + rayD;
        Vector normalInPointOfIntersection = spheres[data.index].getNormal(PointOfIntersection);

        for (int i = 0 ; i < light.size(); i ++) {
            //Informacoes base -> Light
            Vector correctionPoint = normalInPointOfIntersection*Bias;                                  //O bias serve para evitar problemas de aproximacao, as vezes quando se acha um ponto de intersecao, ao se calcula (apartir desse ponto)
            Vector LightDirection = light[i].getDirection (PointOfIntersection);                            //se existe algum objeto entre ele e a(s) fonte(s) de luz, devido a aproximacao ruim, o ponto e considerado como se estivesse dentro da esfera e,
            Vector inverseLightDirection = LightDirection.negative();                                       //inevitavelmente, acaba intersectando a propria esfera. Assim, ao se deslocar o ponto um pouco para fora da esfera, se tenta evitar
            Vector LightColor = light[i].getColor();                                                        //(nada garante que em 100% dos casos ira funcionar) esse problema causado por falhas de aproximacao
            Vector LightIntesityPoint = light[i].getIntensityPoint (PointOfIntersection);

            bool intersectShadow = !TracingShadows(PointOfIntersection + correctionPoint, inverseLightDirection, spheres, light[i].getDistance(PointOfIntersection));

            if (intersectShadow) {
            // *** Difuse Color *** //
                Vector AlbedoN = SphereAlbedo/Number_PI;                                                                    //Colocar o Albedo no intervalor [0:1]
                //Obs: Albedo = Reflect_light/Incident_light (na pratica é como se fosse a cor do objeto (no projeto),
                //porém o conceito de Albeto é diferente do de cor, pois ele indica o poder de reflexao de uma superficie,
                //ou seja, o quanto cada espectro de cor (red, green, blue) ira refletir)

                Vector IntesityColorLight = LightColor*LightIntesityPoint;
                double CossenoN_ILD = std::max(double (0), normalInPointOfIntersection.dotProduct(inverseLightDirection));  //Ao aumentar o angulo entre os vetores Normal e de Direcap da luz, a intensidade luminosa inevitavelmente diminui,
                Vector diffuseColorInThePoint = AlbedoN*IntesityColorLight*CossenoN_ILD;                                        //ja que os "raios de luz" sao espalhados em uma area maior que a a area que existiria se eles fossem paralelos a normal
                diffuse += diffuseColorInThePoint;

            // *** Specular Color *** //
                //Reflexao em torno da normal do raio de luz
                //RaioFinal = RaioEntrada - 2*(NormalDoPlano*RaioEntrada)*NormalDoPlano
                //2*(NormalDoPlano*RaioEntrada)*NormalDoPlano == nLinha
                double NormalDoPlanoRaioEntrada2 = LightDirection.dotProduct(normalInPointOfIntersection)*2;
                Vector nLinha = normalInPointOfIntersection*NormalDoPlanoRaioEntrada2;
                Vector ReflectedLightDirection = LightDirection - nLinha;

                Vector inverseRayDirection = rayDirection.negative();
                double CossenoRLD_IRD = std::pow(std::max(double (0), ReflectedLightDirection.dotProduct(inverseRayDirection)), double (Alpha));    //Angulo entre o vetor refletido que vem da luz e o vetor de direcao da camera invertido (para evitar que fique negativo)
                Vector specularColorInThePoint = LightIntesityPoint * CossenoRLD_IRD;                                                                   //esse angulo determina o qual desviado o raio de luz esta da camera e ira servir para "degradar" a intensidade do raio
                specular += specularColorInThePoint;                                                                                                    //de luz, causando o efeito de a regiao cujo raio refletido vai diretamente a camera ser mais intensamente iluminada
            }                                                                                                                                           //e a medida que vai se afastando dessa regiao a intensidade vai diminuindo (o alpha torna essa diminuicao mais rapida a medida que ele aumenta)
        }

        diffuse = diffuse * Kd;                         //Parcela da cor por difusao
        specular = specular * Ks;                       //Parcela da cor por especular
        environment = SphereAlbedo * Ke;                //Parcela da cor do ambiente

        ColorPoint = diffuse + specular + environment;  //Cor final
        return ColorPoint;
    }
}

//Lanca raios para cada pixel da imagem e, ao receber a cor do ponto intersectado (ou a do plano de funco, caso nao ocorra intersecao),
//salva no pixel especifico na classe Imagem e, por fim, criar uma Imagem.ppm
void Rendering (Imagem &img, Camera &cam, std::vector<Sphere> sphere, std::vector<Light> light) {
    Vector pixels (0);
    int Width = img.getWidth();                                                                //Largura da Imagem
    int Height = img.getHeight();                                                              //Altura da Imagem

    for (int y = 0; y < Height; y++) {                                                         //Loop por toda a Imagem (Width x Height)
        for (int x = 0; x < Width; x++) {
            Ray *rayLocal = cam.getRay (x, y, img.getWidth(), img.getHeight());                //Criando raio de Ray Tracing (Coordenadas locais)

            Ray *rayWorld = new Ray (cam.MatrizToConvertPoint(rayLocal->getOrigin()),          //Criando raio de Ray Tracing (Coordenadas globais)
                                     cam.MatrizToConvertVector(rayLocal->getDirection()));

            pixels = Tracing (rayWorld, sphere, light);                                        //Retornar cor a ser salva no pixel correspondente
            img.setPixels (pixels.getX(), pixels.getY(), pixels.getZ(), (y*Width) + x);        //Setando cor no pixel
        }
    }

    img.SaveAsPPM ();                                                                          //Gerando imagem
}

int main (int argc, char **argv) {
    //Classe para leitura do arquivo de configuracao
    File f;

    //Classes bases
    Imagem img;
    Camera cam;
    std::vector<Material> material;
    std::vector<Sphere> sphere;
    std::vector<Light> light;

    //Lendo configuracoes
    f.ReadingFile (img, cam, material, sphere, light);

    //Plano de fundo
    if (material.size() != 0) { background = material[0]; }

    //Renderizando
    Rendering (img, cam, sphere, light);

    return 0;
}
