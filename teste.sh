#!/bin/bash

# Função para ler o arquivo e armazenar os dados em arrays
lerArquivo() {
    local nomeArquivo="$1"
    local contador=0

    # Verifica se o arquivo existe
    if [[ ! -f "$nomeArquivo" ]]; then
        echo "Não foi possível abrir o arquivo."
        exit 1
    fi

    # Lê o arquivo linha por linha
    while IFS= read -r linha; do
        ((contador++))

        # Se for a segunda linha, armazena as frases
        if [[ $contador -eq 2 ]]; then
            IFS=',' read -ra frases <<< "$linha"  # Note o espaço após a vírgula
            echo "Frases lidas: ${frases[@]}"
        fi

        # Se for a quarta linha, armazena os nomes dos arquivos
        if [[ $contador -eq 4 ]]; then
            IFS=', ' read -ra arquivos <<< "$linha"  # Note o espaço após a vírgula
            echo "Arquivos lidos: ${arquivos[@]}"
        fi
    done < "$nomeArquivo"
}

# Função para verificar se um arquivo existe
arquivoExiste() {
    local nomeArquivo="$1"
    [[ -f "$nomeArquivo" ]]
}

# Chama a função para ler o arquivo
lerArquivo "data.txt"

path="assets/imageTest/"

# Itera sobre os arquivos e frases
for arquivo in "${arquivos[@]}"; do
    if [[ ! -z "$arquivo" && "$arquivo" != "  " ]]; then
        for frase in "${frases[@]}"; do
            # echo "$arquivo - $frase"
            result="$path$frase$arquivo"
            bin/meu_programa "$arquivo" "$frase"
            if arquivoExiste "$result"; then
                existe=1
            else
                existe=0
            fi
        done
    fi
done
