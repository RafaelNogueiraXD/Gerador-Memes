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
    getline(arquivo, linha); // Lê a primeira linha (tipo de PPM)
    // if (linha != linha) {
    //     cout << linha << endl;
    //     cerr << "Formato de arquivo não suportado!" << endl;
    //     return 0;
    // }

    getline(arquivo, linha); // Lê a segunda linha (dimensões)
    istringstream iss(linha);
    iss >> largura >> altura;

    getline(arquivo, linha); // Lê a terceira linha (valor máximo de cor)

    pixels.resize(altura, vector<vector<int>>(largura, vector<int>(3)));

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {
            arquivo >> pixels[y][x][0] >> pixels[y][x][1] >> pixels[y][x][2];
        }
    }

    arquivo.close();
    cout << "Lendo imagem..." << endl;
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
    // Inicializa um gerador de números pseudoaleatórios com uma semente gerada a partir do gerador de números aleatórios
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
    // Inicializa um gerador de números pseudoaleatórios com uma semente gerada a partir do gerador de números aleatórios
    mt19937 gen(rd());
    // Define uma distribuição uniforme que gera números inteiros entre 0 e 100
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
    // Verifica se as coordenadas estão dentro dos limites
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

void ImagemPPM::escreverTexto(const string& texto, int x_inicial, int y_inicial, int tamanhoLetra) {
    int x_atual = x_inicial;
    int y_atual = y_inicial;

    int caracteresNaLinhaAtual = 0;
    int maxCaracteresPorLinha = this->getLargura()/50;
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
        } else {
            // Espaço ou outro caractere não suportado
            x_atual += tamanhoLetra; // Ajusta a posição x para o próximo caractere
            continue;
        }
        if (caracteresNaLinhaAtual >= maxCaracteresPorLinha || c == '\n') {
            y_atual += 100;  // Move para a próxima linha
            x_atual = x_inicial;  // Reinicia a posição x
            caracteresNaLinhaAtual = 0;  // Reinicia a contagem de caracteres

            // Expande a imagem se necessário
            // if (y_atual + 100 > getAltura()) {
            //     expandirImagem(getAltura() + 100, getLargura());
            // }
        }

        ImagemPPM letra(0,0);
        if (letra.lerImagem(caminho)) {
            // Aqui você pode redimensionar a imagem da letra para o tamanho desejado usando um método de redimensionamento que você pode adicionar à classe
            // letra.redimensionar(tamanhoLetra, tamanhoLetra);
            letra.setCorDeTexto(this->getCorDeTexto());
            letra.mudarCorDePontoPreto();
            for (int y = 0; y < letra.getAltura(); ++y) {
                for (int x = 0; x < letra.getLargura(); ++x) {
                    std::vector<int> pixel = letra.getPixel(y, x);
                    // Verifique se o pixel da letra NÃO é branco ou próximo de branco
                    if (!(pixel[0] > 250 && pixel[1] > 250 && pixel[2] > 250)) {
                        pixels[y_atual + y][x_atual + x] = pixel;
                    }
                }
            }
            // this->sobreporImagem(letra, x_atual, y_atual);
            
            
            x_atual += letra.getLargura() + 5; // Ajusta a posição x para o próximo caractere

        } else {
            cerr << "Não foi possível ler o arquivo: " << caminho << endl;
        }
        caracteresNaLinhaAtual++;
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
    vector<vector<vector<int>>> novosPixels(novaAltura, vector<vector<int>>(novaLargura, vector<int>(3, 0)));  // Inicializa com pixels pretos

    // Copia os pixels existentes para a nova matriz
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
            pixels[i][j][0] = 255 - pixels[i][j][0];  // Red
            pixels[i][j][1] = 255 - pixels[i][j][1];  // Green
            pixels[i][j][2] = 255 - pixels[i][j][2];  // Blue
        }
    }
}
//oi rafael tudo bem
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
