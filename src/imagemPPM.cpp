#include "imagemPPM.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>


ImagemPPM::ImagemPPM(int largura, int altura, const vector<int>& corDeFundo)
    : largura(largura), altura(altura), pixels(altura, vector<vector<int>>(largura, corDeFundo)) {}

void ImagemPPM::definirPixel(int x, int y, const vector<int>& cor) {
    if (x >= 0 && x < largura && y >= 0 && y < altura) {
        pixels[y][x] = cor;
    } else {
        cerr << "Coordenadas do pixel fora dos limites!" << endl;
    }
}

void ImagemPPM::pintarImagem(const vector<int>& cor) {
    for (auto& linha : pixels) {
        for (auto& pixel : linha) {
            pixel = cor;
        }
    }
}

void ImagemPPM::salvar(const string& caminhoArquivo) const {
    cout << "Salvando imagem" << endl;
    ofstream arquivo(caminhoArquivo);

    if (arquivo.is_open()) {
        arquivo << "P3\n";
        arquivo << largura << " " << altura << "\n";
        arquivo << "255\n";

        for (const auto& linha : pixels) {
            for (const auto& pixel : linha) {
                arquivo << pixel[0] << " " << pixel[1] << " " << pixel[2] << " ";
            }
            arquivo << "\n";
        }

        arquivo.close();
    } else {
        cerr << "Não foi possível abrir o arquivo para escrita!" << endl;
    }
}


int ImagemPPM::lerImagem(const string& caminhoArquivo) {
    
    ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        cerr << "Não foi possível abrir o arquivo para leitura!" << endl;
        return 0;
    }

    string linha;
    getline(arquivo, linha);






    getline(arquivo, linha);
    istringstream iss(linha);
    iss >> largura >> altura;

    getline(arquivo, linha);

    pixels.resize(altura, vector<vector<int>>(largura, vector<int>(3)));

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {
            arquivo >> pixels[y][x][0] >> pixels[y][x][1] >> pixels[y][x][2];
        }
    }

    arquivo.close();

    return 1;
}
void ImagemPPM::mostraValoresBasicos(){
    cout << "A largura eh: " << largura << " a altura eh: " << altura << endl;
}

void ImagemPPM::sobreporImagem(const ImagemPPM& imagemMenor, int x, int y) {
    cout << "sobrePondo!" << endl;
    for (int i = 0; i < imagemMenor.altura; ++i) {
        for (int j = 0; j < imagemMenor.largura; ++j) {
            if (i + y < altura && j + x < largura) {
                pixels[i + y][j + x] = imagemMenor.pixels[i][j];
            }
        }
    }
}

int ImagemPPM::getAltura(){
    return altura;
}

int ImagemPPM::getLargura(){
    return largura;
}
int ImagemPPM::calculoPorcetagem(int porcentagem,int direcao) {
    int resultado = 0;
    if (direcao == 0) {
        resultado = (largura * porcentagem) / 100;
    } else {
        resultado = (altura * porcentagem) / 100;   
    }
    return resultado; 
}
void ImagemPPM::colorirRandomVertical(int intervalor){
    random_device rd;

    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);

    int acumulador = intervalor;
    while (acumulador < (100 + intervalor) ){
        pintarRegiao(
            calculoPorcetagem(acumulador - intervalor,0),
            0,
            calculoPorcetagem(acumulador,0),
            getAltura()- 1,
            {dis(gen),dis(gen),dis(gen)});
        acumulador += intervalor;
    }
}
void ImagemPPM::recortarImagemVerticalmente(int x_inicial, int x_final){
    int y_inicial= 0;
    int y_final = getAltura()-1;
    recortarImagem( x_inicial,  y_inicial,  x_final,  y_final);
}
void ImagemPPM::colorirRandomHorizontal(int intervalor){
    random_device rd;

    mt19937 gen(rd());

    uniform_int_distribution<> dis(0, 255);

    int acumulador = intervalor;
    while (acumulador < (100 + intervalor) ){
        pintarRegiao(
            0,
            calculoPorcetagem(acumulador - intervalor,1),
            getLargura(),
            calculoPorcetagem(acumulador,1),
            {dis(gen),dis(gen),dis(gen)}
            );
        acumulador += intervalor;
    }
}

void ImagemPPM::pintarRegiao(int x_inicial, int y_inicial, int x_final, int y_final, const vector<int>& cor) {
    cout << "Pintando imagem !" << endl;
    for (int i = y_inicial; i <= y_final && i < altura; ++i) {
        for (int j = x_inicial; j <= x_final && j < largura; ++j) {
            pixels[i][j] = cor;
        }
    }
}

void ImagemPPM::recortarImagem(int x_inicial, int y_inicial, int x_final, int y_final) {

    if (x_inicial < 0 || y_inicial < 0 || x_final >= largura || y_final >= altura || 
        x_inicial > x_final || y_inicial > y_final) {
        cerr << "Coordenadas de recorte inválidas!" << endl;
        return;
    }

    int novaLargura = x_final - x_inicial + 1;
    int novaAltura = y_final - y_inicial + 1;

    vector<vector<vector<int>>> novosPixels(novaAltura, vector<vector<int>>(novaLargura, vector<int>(3)));

    for (int i = 0; i < novaAltura; ++i) {
        for (int j = 0; j < novaLargura; ++j) {
            novosPixels[i][j] = pixels[y_inicial + i][x_inicial + j];
        }
    }

    largura = novaLargura;
    altura = novaAltura;
    pixels = novosPixels;
}
vector<int> ImagemPPM::getPixel(int y, int x) const {
    return pixels[y][x];
}


void ImagemPPM::aplicarMarcaDagua(const ImagemPPM& logotipo) {

    if (this->largura < logotipo.largura || this->altura < logotipo.altura) {
        cerr << "Erro: O logotipo é maior que a imagem de destino." << endl;
        return;
    }

    for (int y = 0; y < logotipo.altura; ++y) {
        for (int x = 0; x < logotipo.largura; ++x) {
            vector<int> pixelLogotipo = logotipo.pixels[y][x];

        
            if (pixelLogotipo[0] > 200 && pixelLogotipo[1] > 200 && pixelLogotipo[2] > 200) {
                vector<int> pixelDestino = this->pixels[y][x];

            
                vector<int> novoPixel(3);
                for (int i = 0; i < 3; ++i) {
                    novoPixel[i] = 0.5 * pixelDestino[i] + 0.5 * pixelLogotipo[i];
                }

            
                this->pixels[y][x] = novoPixel;
            }
        }
    }
}

vector<int> ImagemPPM::gerarCorSombra() {
    cout << "gerando sombra" << endl;
    vector<int> corSombra(3);
    vector<int> corTexto  = getCorDeTexto();


    if (corTexto[0] > corTexto[1] && corTexto[0] > corTexto[2]) {
        corSombra = {255, 179, 179};
    }

    else if (corTexto[1] > corTexto[0] && corTexto[1] > corTexto[2]) {
        corSombra = {179, 255, 179};
    }

    else if (corTexto[2] > corTexto[0] && corTexto[2] > corTexto[1]) {
        corSombra = {179, 179, 255};
    }

    else {
        corSombra = {179, 179, 179};
    }

    return corSombra;
}
void ImagemPPM::escreverTexto(const string& texto, int x_inicial, int y_inicial, int tamanhoLetra) {
    int sombra = 0;
    vector<int> corOriginal = getCorDeTexto();
    while (sombra < 2){
        if(sombra == 0){
            x_inicial += 5;
            y_inicial += 5;
        }else{
            x_inicial -= 5;
            y_inicial -= 5;
        }
        int x_atual = x_inicial;
        int y_atual = y_inicial;

        int caracteresNaLinhaAtual = 0;
        int maxCaracteresPorLinha = this->getLargura()/60;
        for (char c : texto) {
            string caminho;
            if (isalpha(c)) {
                if (isupper(c)) {
                    caminho = "assets/caracteres/maiuscula/" + string(1, c) + ".ppm";
                } else {
                    caminho = "assets/caracteres/minuscula/" + string(1, c) + ".ppm";
                }
            } else if (ispunct(c)) {
                caminho = "assets/caracteres/pontuacao/" + string(1, c) + ".ppm";
            
            } else if (isdigit(c)) {
                caminho = "assets/caracteres/numeros/" + string(1, c) + ".ppm";
            } else {
            
                    if((caracteresNaLinhaAtual + 1)  < maxCaracteresPorLinha) {
                        x_atual += tamanhoLetra; 
                        caracteresNaLinhaAtual++; 
                    }
                continue;
            }
            if (caracteresNaLinhaAtual >= maxCaracteresPorLinha || c == '\n') {
                y_atual += 100; 
                x_atual = x_inicial; 
                caracteresNaLinhaAtual = 0; 
            }

            ImagemPPM letra(0,0);
            if (letra.lerImagem(caminho)) {
            
            
                if(sombra == 0)
                    letra.setCorDeTexto(this->gerarCorSombra());
                else letra.setCorDeTexto(corOriginal);
                letra.mudarCorDePontoPreto();
                if(sombra == 0){
                    for(int i = 0; i <10 ; i++)
                        letra.aplicarFiltroGaussiano();
                }
            
                for (int y = 0; y < letra.getAltura(); ++y) {
                    for (int x = 0; x < letra.getLargura(); ++x) {
                        vector<int> pixel = letra.getPixel(y, x);
                    
                        if(sombra == 0){
                            if (!(pixel[0] > 179 && pixel[1] > 179 && pixel[2] > 179)) {
                                pixels[y_atual + y][x_atual + x] = pixel;
                            }
                        }else{
                            if (!(pixel[0] > 130 && pixel[1] > 130 && pixel[2] > 130)) {
                                pixels[y_atual + y][x_atual + x] = pixel;
                            }
                        }
                    }
                }
            
            
                x_atual += letra.getLargura() + 5;

            } else {
                cerr << "Não foi possível ler o arquivo: " << caminho << endl;
            }
            caracteresNaLinhaAtual++;
            cout << "escrevendo. . ." << endl;
        }
        sombra++;
    }
}
void ImagemPPM::mudarCorDePontoPreto() {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            if (pixels[i][j][0] == 1 && pixels[i][j][1] == 0 && pixels[i][j][2] == 0) {
                pixels[i][j] = this->getCorDeTexto();
            }
        }
    }
}

void ImagemPPM::apagarPixelsBrancos() {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            if (pixels[i][j][0] == 255 && pixels[i][j][1] == 255 && pixels[i][j][2] == 255) {
                pixels[i][j][0] = 0;
                pixels[i][j][1] = 0;
                pixels[i][j][2] = 0;
            }
        }
    }
}


void ImagemPPM::setCorDeTexto(const vector<int>& novaCor) {
    if (novaCor.size() == 3 && novaCor[0] >= 0 && novaCor[0] <= 255 && 
        novaCor[1] >= 0 && novaCor[1] <= 255 && novaCor[2] >= 0 && novaCor[2] <= 255) {
        corDeTexto = novaCor;
    } else {
        cerr << "Cor inválida!" << endl;
    }
}

vector<int> ImagemPPM::getCorDeTexto() const {
    return corDeTexto;
}

void ImagemPPM::expandirImagem(int novaAltura, int novaLargura) {
    vector<vector<vector<int>>> novosPixels(novaAltura, vector<vector<int>>(novaLargura, vector<int>(3, 0))); 


    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            novosPixels[i][j] = pixels[i][j];
        }
    }

    altura = novaAltura;
    largura = novaLargura;
    pixels = novosPixels;
}

void ImagemPPM::aplicarNegativo() {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            pixels[i][j][0] = 255 - pixels[i][j][0]; 
            pixels[i][j][1] = 255 - pixels[i][j][1]; 
            pixels[i][j][2] = 255 - pixels[i][j][2]; 
        }
    }
}
void ImagemPPM::aplicarFiltroGaussiano() {
    vector<vector<vector<int>>> imagemResultante = pixels;

    int kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    for (int y = 1; y < altura - 1; ++y) {
        for (int x = 1; x < largura - 1; ++x) {
            int red = 0, green = 0, blue = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    red += pixels[y + ky][x + kx][0] * kernel[ky + 1][kx + 1];
                    green += pixels[y + ky][x + kx][1] * kernel[ky + 1][kx + 1];
                    blue += pixels[y + ky][x + kx][2] * kernel[ky + 1][kx + 1];
                }
            }
            imagemResultante[y][x][0] = red / 16;
            imagemResultante[y][x][1] = green / 16;
            imagemResultante[y][x][2] = blue / 16;
        }
    }

    pixels = imagemResultante;
}

