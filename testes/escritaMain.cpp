#include "imagemPPM.h"
#include "funcoesGerais.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;

int main() {
    ImagemPPM imagem(0, 0);
    ImagemPPM imagem2(500, 500,{255,250,20});
    string caminho = "assets/caracteres/minuscula/a.ppm";
    // string caminho = "assets/imagem.ppm";
    int a = imagem.lerImagem(caminho);
    cout << a << endl;
    cout << caminho << endl;
    imagem2.sobreporImagem(imagem, 50, 50);
    imagem2.salvar("imagem_texto.ppm");
}
