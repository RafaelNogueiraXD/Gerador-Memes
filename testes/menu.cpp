#include "imagemPPM.h"
#include "funcoesGerais.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;
//primeiro printa a imagem
int main() {
    ImagemPPM image(0,0,{0,0,0});
   int op = 0;
    string inputUsuario,caminho;
    do{
        menu();
        printf("Escolha: ");
        cin >> op;
        switch (op)
        {
        case 1:
            printf("Digite o caminho: ");
            cin >> caminho;
            image.lerImagem(caminho);
        break;
        case 2:
            cout << "Escreva a frase" << endl;
            cin >> inputUsuario;
            
            image.escreverTexto(inputUsuario,50,50,50);
        break;
        case 3:
            cout << "Escreva a frase" << endl;
            cin >> inputUsuario;
            image.escreverTexto(inputUsuario,50,50,50);
            image.escreverTexto(inputUsuario, 50, image.getAltura() - 100 , 50); // Escreve o texto na imagem
        break;
        case 4:
            menuEdicao();
            break;
        case 5:
            cin >> inputUsuario;
            if(inputUsuario == caminho)cout << "nao pode salvar na imagem original" << endl;
            else image.salvar(inputUsuario);
        break;
        case 6:
            image.lerImagem(caminho);
        break;
        case 7:
            for(int i = 0; i < 21; i++)
                image.aplicarFiltroGaussiano();
        break;
        default:
            cout << "Opcao invalida" << endl;
            break;
        }
    }while( op != 0);    
  
  
/*
    ImagemPPM imagem(0,0);
    imagem.lerImagem("assets/alek.ppm");
    imagem.setCorDeTexto({255,0,90});
    imagem.escreverTexto("kkkkkkkkkkk", 50, 50, 50); // Escreve o texto na imagem
    imagem.expandirImagem(imagem.getAltura()+150, imagem.getLargura());
    imagem.escreverTexto("O baguio eh doido msm", 50, imagem.getAltura() - 100 , 50); // Escreve o texto na imagem
    imagem.salvar("imagem_texto.ppm");
*/
    return 0;
}


/*
isso eh uma gauciana em matriz função f
1 2 1
2 4 2 
1 2 1

função g 
m[i-1][j-1]m[i-1][j]m[i][j+1] 
m[i][j-1]  m[i][j]  m[i][j+1]
m[i+1][j-1]m[i+1][j]m[i+1][j+1]

n[i][j] = (1/16) *[( m[i-1][j-1] + m[i+1][j-1] + m[i-1][j-1] + m[i-1][j+1]) +
              2 * (m[i][j-1] + m[i][j+1] + m[i-1][j] + m[i+1][j]) +
              4 * m[i][j]]
detecção de borda , matriz
-1 0 1
-1 0 1
-1 0 1

detecção borda
-1 -1 -1
0 0 0
1 1 1

conseguimos aplicar uma função que realiza a convolução de uma imagem com os filtros mencionados: Gaussiano para suavização 

e os dois filtros de detecção de borda.

*/