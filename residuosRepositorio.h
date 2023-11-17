#ifndef RESIDUOSREPOSITORIO_H_INCLUDED
#define RESIDUOSREPOSITORIO_H_INCLUDED

#include "types.h"
#include "listas/listas.h"

bool inserirResiduo(Residuo residuo);
ListaDeResiduos* buscarResiduoPorEmpresa(const char* cnpj);

#endif // RESIDUOSREPOSITORIO_H_INCLUDED
