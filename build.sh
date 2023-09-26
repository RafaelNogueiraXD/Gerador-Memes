#!/bin/bash

# Diretórios do projeto
SRC_DIR="./src"
INCLUDE_DIR="./include"
BIN_DIR="./bin"
OBJ_DIR="./obj"

# Verifica se os diretórios bin e obj existem, senão, cria-os
mkdir -p $BIN_DIR $OBJ_DIR

# Compila os arquivos fonte para arquivos objeto
for src_file in $SRC_DIR/*.cpp; do
    obj_file="$OBJ_DIR/$(basename $src_file .cpp).o"
    g++ -I$INCLUDE_DIR -c $src_file -o $obj_file
done

# Vincula os arquivos objeto para criar o executável
g++ $OBJ_DIR/*.o -o $BIN_DIR/meu_programa

# Informa se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida!"
    bin/meu_programa "imagem.ppm" "frase 1 texto texto"
    # ./teste.sh
else
    echo "Erro na compilação!"
fi
