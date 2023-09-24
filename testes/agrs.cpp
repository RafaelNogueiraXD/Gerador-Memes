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
        image.escreverTexto("texto aleatoriopdoksad", 50, 50, 50);
        image.setCorDeTexto({100,90,255});
        image.escreverTexto(argv[2], 50, image.getAltura() - 100 , 50); // Escreve o texto na imagem
        image.salvar("assets/teste.ppm");
     }else  cout << "isso nao eh um " << argv[1] << endl;


}

