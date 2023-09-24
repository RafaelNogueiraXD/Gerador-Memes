// #include <imagemPPM.h>
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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

struct Dados {
    vector<string> frases;
    vector<string> arquivos;
};

Dados lerArquivo(const string& nomeArquivo) {
    Dados dados;
    ifstream arquivo(nomeArquivo);
    string linha;
    int contador = 0;

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            contador++;
            stringstream ss(linha);
            string item;

            // Se for a primeira ou terceira linha, ignora (são as linhas de descrição)
            if (contador == 1 || contador == 3) {
                continue;
            }

            // Se for a segunda linha, armazena as frases
            if (contador == 2) {
                while (getline(ss, item, ',')) {
                    dados.frases.push_back(item);
                }
            }

            // Se for a quarta linha, armazena os nomes dos arquivos
            if (contador == 4) {
                while (getline(ss, item, ',')) {
                    dados.arquivos.push_back(item);
                }
            }
        }
        arquivo.close();
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }

    return dados;
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