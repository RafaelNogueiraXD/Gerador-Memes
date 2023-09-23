// #include <imagemPPM.h>
#include <iostream>
using namespace std;


void menu(){
    cout << "Bem-vindo ao gerador de memes!" << endl;
    cout << "\t 0 - encerrar o app" << endl;
    cout << "\t 1- Informe o caminho da imagem!" << endl;
    cout << "\t 2- Informe o texto no topo da imagem." << endl;
    cout << "\t 3 - Informe o texto no fundo da imagem." << endl;
    cout << "\t 4 - Aumentar opções de edição de imagem." << endl;
    cout << "\t 5 - salve a imagem" << endl;
    cout << "\t 6 - reset as alteracoes(volte ao estado inicial da imagem)" << endl;
    cout << "\t 7 - aplica blurr" << endl;
    
}
void menuEdicao(){
    cout << "\t 1 - recorte a imagem" << endl;
    cout << "\t 2 - gere uma imagem Verticalmente Colorida" << endl;
    cout << "\t 3 - gere uma imagem Horizontamente Colorida" << endl;
    cout << "\t 4 - negativar imagem a imagem" << endl;
    cout << "\t 5 - pinte a imagem" << endl;
}
int calculoLetras(int numAscii){
    int resultado = 0;
    if(numAscii > 47 && numAscii < 58){
        resultado = numAscii - 48;
    }else if(numAscii > 64 && numAscii < 91){
        resultado = numAscii - 64;
        resultado += 10;
    }else if(numAscii > 96 && numAscii < 123){
        resultado = numAscii - 97;
        resultado += 36;
    }
    return resultado;
}