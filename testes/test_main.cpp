#include "imagemPPM.h"
#include "funcoesGerais.h"
#include <iostream>
#include <random>
#include <string>
using namespace std;

int verificaFinal(const std::string& str) {
    if (str.size() < 4) {
        return 1;
    }
    std::string final = str.substr(str.size() - 4);
    if (final == ".ppm") {
        return 0;
    } else {
        return 1;
    }
}

bool arquivoExiste(const std::string& nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());
    return arquivo.good();
}

int main(int argc, char* argv[]) {
    string pathOriginal = "assets/original/";
    string path = "assets/imageTest/";
    string res,res2;
    string arquivo = argv[1];
    string  frase = argv[2];
    if(!arquivo.empty() && arquivo != " " && verificaFinal(arquivo) != 1) {
        res = pathOriginal + arquivo;
        if (arquivoExiste(res)) {
            ImagemPPM* image = new ImagemPPM(0,0,{0,0,0});
            image->lerImagem(res);
            image->escreverTexto(frase, 50, 50 , 50);
            res2 = path + frase + arquivo;
            image->salvar(res2);
            delete image;    
            // cout << "ja feito" << endl;
        }else {
            cout << "criando Imagem" << endl;
            random_device rd;  // Dispositivo de geração de números aleatórios
            mt19937 gen(rd());  // Gerador Mersenne Twister
            uniform_int_distribution<> distrib(60, 255);  // Distribuição uniforme entre 0 e 99
            ImagemPPM* image = new ImagemPPM(800,400,{distrib(gen),distrib(gen),distrib(gen)});
            image->salvar(res);
            image->setCorDeTexto({0,0,0});
            image->escreverTexto(frase, 50, 50 , 50);
            res2 = path + frase + arquivo;
            image->salvar(res2);
            delete image;    
        }
    }   
    // cout << "\n\tfim programa " << endl;
    return 0;
}
