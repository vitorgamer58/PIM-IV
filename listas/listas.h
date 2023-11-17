#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include "../types.h"

typedef struct
{
    Residuo residuo;
    struct ListaDeResiduos * proximo;
} ListaDeResiduos;

#endif // LISTAS_H_INCLUDED
