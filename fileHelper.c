#include <stdio.h>

FILE* criarArquivo(const char* nomeDoArquivo)
{
    FILE* Ponteiro;

    Ponteiro = fopen(nomeDoArquivo, "w");

    if(!Ponteiro)
    {
        printf("Erro ao criar o arquivo.\n");
        return NULL;
    }

    return Ponteiro;
}

FILE* abrirOuCriarArquivo(const char* nomeDoArquivo)
{
    FILE *Ponteiro;

    Ponteiro = fopen(nomeDoArquivo, "r+");

    if(!Ponteiro)
    {
        return criarArquivo(nomeDoArquivo);
    }

    return Ponteiro;
}

FILE* abrirArquivoParaGravacao(const char* nomeDoArquivo, const char* linha)
{
    FILE *Ponteiro = fopen(nomeDoArquivo, "a"); // Abre o arquivo para anexar

    if (Ponteiro == NULL)
    {
        perror("Erro ao abrir o arquivo");
    }
    return Ponteiro;
}
