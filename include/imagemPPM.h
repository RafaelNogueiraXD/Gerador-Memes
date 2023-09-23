#include <iostream>
#include <vector>
using namespace std;

class ImagemPPM {
public:
    // Construtor que inicializa a imagem com dimensões específicas e uma cor de fundo
    ImagemPPM(int largura, int altura, const vector<int>& corDeFundo = {0, 0, 0});

    // Método para definir um pixel com uma cor específica
    void definirPixel(int x, int y, const vector<int>& cor);
    void pintarRegiao(int x_inicial, int y_inicial, int x_final, int y_final, const vector<int>& cor);
    void colorirRandomVertical(int intervalor);
    void colorirRandomHorizontal(int intervalor);
    
    vector<int> getPixel(int y, int x) const;
    void escreverTexto(const string& texto, int x_inicial, int y_inicial, int tamanhoLetra);
    
    void apagarPixelsBrancos();
    void mudarCorDePontoPreto();
    void aplicarFiltroGaussiano();  
    void aplicarNegativo();     
    int lerImagem(const string& caminhoArquivo);
    void recortarImagem(int x_inicial, int y_inicial, int x_final, int y_final);
    void recortarImagemVerticalmente(int x_inicial, int x_final);
   
    void pintarImagem(const vector<int>& cor);
    void sobreporImagem(const ImagemPPM& imagemMenor, int x, int y);
    void expandirImagem(int novaAltura, int novaLargura);
    // Método para salvar a imagem em um arquivo PPM
    void salvar(const string& caminhoArquivo) const;
    void mostraValoresBasicos();
    int calculoPorcetagem(int porcentagem,int direcao);
    int getAltura();
    int getLargura();
    void setCorDeTexto(const vector<int>& novaCor);
    vector<int> getCorDeTexto() const;
private:
    int largura;
    int altura;
    vector<vector<vector<int>>> pixels;
    vector<int> corDeTexto;

};