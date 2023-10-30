#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdbool.h>

typedef struct {
    char nomeDeUsuario[50];
    char senha[50];
    bool isValid;
} Usuario;

#endif // TYPES_H_INCLUDED
