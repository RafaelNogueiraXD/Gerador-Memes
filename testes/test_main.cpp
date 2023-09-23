#include "imagemPPM.h"
#include "funcoesGerais.h"
#include <iostream>
#include <random>
using namespace std;

int main() {
    // ImagemPPM imagemColorida(800 , 200, {255, 255, 255});
    // imagemColorida.mostraValoresBasicos();
    // // imagemColorida.colorirRandomVertical(5);
    // imagemColorida.colorirRandomVertical(10);
    // imagemColorida.salvar("assets/imagemColorida.ppm");
    // teste funcional 1
    
   
    // int op = 0;
    // int xInit, yInit, xF, yF;
    // int xI, xf;
    // string caminho;
    // // 69 caaracters
    // //48 pra todos os numeros, começando em 10
    // ImagemPPM imagemUsuario(0 , 0);
    // imagemUsuario.lerImagem("assets/impactfont.ppm");
    // imagemUsuario.recortarImagemVerticalmente(46*9,48*10);

    // imagemUsuario.salvar("assets/1.ppm");


/*
    do{
        menu();
        cin >> op;
        switch(op){
        case 1:
        cout << "ok" << endl;
            break;
        case 2: 
            cin >> xI;
            cin >> xF;
            imagemUsuario.recortarImagemVerticalmente(xI, xF);
        break;
        case 3:
            cin >> caminho;
            imagemUsuario.salvar(caminho);
        break;
        case 4:
            imagemUsuario.lerImagem("assets/impactfont.ppm");        break;
        default:
            cout << "opcao invalida" << endl;
            break;
        }
    }while( op == 0);    
*/
    //cortando verticalmente
    // imagemColorida.recortarImagem(0,0,imagemColorida.calculoPorcetagem(10,0) - 1,imagemColorida.getAltura()-1);
    //cortando horizontamente
    // imagemColorida.recortarImagem(0,0,imagemColorida.getLargura() - 1,imagemColorida.calculoPorcetagem(20,1) - 1);
    // imagemColorida.salvar("assets/imagemColoridaRecortada.ppm");

    // ImagemPPM imagemVerde(100 , 100, {0 , 0 , 0});
    // imagemVerde.mostraValoresBasicos();

    // imagemVermelha.sobreporImagem(imagemVerde, imagemVermelha.calculoPorcetagem(10, "Horizontal"), imagemVermelha.calculoPorcetagem(10, "vertical"));
    // imagemVermelha.salvar("assets/resultado.ppm");
    // // criando verde
    // ImagemPPM imagem(400, 200);
    // cout << "Pintando Imagem" << endl;
    // imagem.pintarImagem({0, 0, 255}); // Pinta toda a imagem de verde
    // cout << "definindo pixel central" << endl;
    // imagem.definirPixel(400, 300, {255, 0, 0}); // Define um pixel no centro como vermelho
    // cout << "salvando . . . " << endl;
    // imagem.salvar("assets/imagemAzul.ppm");

    return 0;
}