#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdbool.h>

typedef struct {
    char nomeDeUsuario[50];
    char senha[50];
    bool isValid;
} Usuario;

typedef struct {
    char nomeDoResponsavel[100];
    char documentoDoResponsavel[50];
    char nomeFantasia[100];
    char razaoSocial[100];
    char emailDaEmpresa[100];
    char telefoneDaEmpresa[50];
    char enderecoDaEmpresa[200];
    char cnpj[16];
    bool isValid;
} Empresa;

typedef struct {
    char cnpj[16];
    int toneladas;
    float faturamento;
} Residuo;


#endif // TYPES_H_INCLUDED
