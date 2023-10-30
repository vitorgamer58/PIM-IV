#include <stdio.h>

FILE* criarArquivo(const char* nomeDoArquivo) {
    FILE* Ponteiro;

    Ponteiro = fopen(nomeDoArquivo, "w");

    if(!Ponteiro) {
        printf("Erro ao criar o arquivo.\n");
        return NULL;
    }

    return Ponteiro;
}

FILE* abrirOuCriarArquivo(const char* nomeDoArquivo) {
    FILE *Ponteiro;

    Ponteiro = fopen(nomeDoArquivo, "r");

    if(!Ponteiro) {
        return criarArquivo(nomeDoArquivo);
    }

    return Ponteiro;
}
