#include "imagemPPM.h"
#include "funcoesGerais.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;
//primeiro printa a imagem
int main(int argc, char* argv[]) {
    string palavra = "nova";
     if (palavra.compare(argv[1]) == 0){
        ImagemPPM image(800,600,{199,50,99});
        image.setCorDeTexto({0,0,0});
        image.escreverTexto("texto aleatorio", 50, 50, 50);
        image.salvar("assets/teste.ppm");
     }else  cout << "isso nao eh um " << argv[1] << endl;
   
    // ImagemPPM image(0,0);
    // image.lerImagem("assets/alek.ppm");
    // for(int i = 0; i < 21; i++)
    //     image.aplicarFiltroGaussiano();
    // image.salvar("assets/gaussiano.ppm");
    // return 0;
}

