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
    ImagemPPM logo(0,0);
    logo.lerImagem("assets/logo.ppm");
        if(!arquivo.empty() && arquivo != " " && verificaFinal(arquivo) != 1) {
        cout << argv[1] << endl;
        cout << argv[2] << endl;
        res = pathOriginal + arquivo;
        cout << res << endl;
        if (arquivoExiste(res)) {
            ImagemPPM* image = new ImagemPPM(0,0,{0,0,0});
            image->lerImagem(res);
            image->setCorDeTexto({0,0,0});
            image->escreverTexto(frase, 50, 50 , 50);
            image->sobreporImagem(logo, image->getLargura()-200, image->getAltura()-100);
            res2 = path + frase + arquivo;
            image->salvar(res2);
            delete image;    
        }else {
            cout << "criando Imagem" << endl;
            random_device rd;
            mt19937 gen(rd());  
            uniform_int_distribution<> distrib(60, 255);  
            ImagemPPM* image = new ImagemPPM(1200,600,{distrib(gen),distrib(gen),distrib(gen)});
            image->salvar(res);
            image->setCorDeTexto({0,0,0});
            image->escreverTexto(frase, 50, 50 , 25);
            image->aplicarMarcaDagua(logo);
            image->sobreporImagem(logo, image->getLargura()-200, image->getAltura()-100);
            res2 = path + frase + arquivo;
            image->salvar(res2);
            delete image;    
        }
    }   

    
    
    return 0;
}
