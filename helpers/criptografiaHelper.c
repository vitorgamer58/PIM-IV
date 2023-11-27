#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define CHAVE 2

char* criptografar(const char texto[])
{
    char *textoCriptografado = malloc(strlen(texto) + 1);
    if (textoCriptografado == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    int i = 0;
    while (texto[i] != '\0')
    {
        if (isalpha(texto[i]))
        {
            char base = islower(texto[i]) ? 'a' : 'A';
            textoCriptografado[i] = (texto[i] - base + CHAVE) % 26 + base;
        }
        else
        {
            textoCriptografado[i] = texto[i];
        }
        i++;
    }
    textoCriptografado[i] = '\0';

    return textoCriptografado;
}

char* descriptografar(const char textoCriptografado[])
{
    char *textoDescriptografado = malloc(strlen(textoCriptografado) + 1);
    if (textoDescriptografado == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    int i = 0;
    while (textoCriptografado[i] != '\0')
    {
        if (isalpha(textoCriptografado[i]))
        {
            char base = islower(textoCriptografado[i]) ? 'a' : 'A';
            textoDescriptografado[i] = (textoCriptografado[i] - base - CHAVE + 26) % 26 + base;
        }
        else
        {
            textoDescriptografado[i] = textoCriptografado[i];
        }
        i++;
    }
    textoDescriptografado[i] = '\0';

    return textoDescriptografado;
}
