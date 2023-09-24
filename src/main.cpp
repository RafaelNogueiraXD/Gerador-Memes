#include "imagemPPM.h"
#include "funcoesGerais.h"
#include <iostream>
#include <random>
#include <string>
using namespace std;
bool arquivoExiste(const std::string& nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());
    return arquivo.good();
}
int main(int argc, char* argv[]) {
    Dados dados = lerArquivo("data.txt");
    string  te = "assets/imageTest/";
    for (const string& arquivo : dados.arquivos) {
        // Iterando sobre cada frase
        string result =  te + arquivo;
        for (const string& frase : dados.frases) {
            cout << arquivo << " - " << frase << endl;
            if (arquivoExiste(result)) {
                ImagemPPM* image = new ImagemPPM(0,0,{0,0,0});
                image->lerImagem(result);
                image->escreverTexto(frase, 50, 50 , 50);
                result = te + frase + arquivo;
                image->salvar(result);
                delete image;    
            }else {
                random_device rd;  // Dispositivo de geração de números aleatórios
                mt19937 gen(rd());  // Gerador Mersenne Twister
                uniform_int_distribution<> distrib(60, 255);  // Distribuição uniforme entre 0 e 99
                ImagemPPM* image = new ImagemPPM(800,400,{distrib(gen),distrib(gen),distrib(gen)});
                image->setCorDeTexto({0,0,0});
                image->escreverTexto(frase, 50, 50 , 50);
                result = te + frase + arquivo;
                image->salvar(result);
                delete image;    
            }
        }
    }
    
    return 0;
}


