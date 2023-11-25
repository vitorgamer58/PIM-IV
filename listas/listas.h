#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include "../types.h"

typedef struct
{
    Residuo residuo;
    struct ListaDeResiduos * proximo;
} ListaDeResiduos;

typedef struct
{
    Empresa empresa;
    struct ListaDeEmpresas * proximo;
} ListaDeEmpresas;

typedef struct
{
    Empresa empresa;
    struct ListaDeEmpresas * proximo;
} ListaRelatorioSomaResiduos;

ListaDeResiduos* iniciaListaDeResiduos();
ListaDeResiduos* insereNaListaDeResiduos(ListaDeResiduos* lista, Residuo novoResiduo);
ListaDeEmpresas* iniciaListaDeEmpresas();
ListaDeEmpresas* insereNaListaDeEmpresas(ListaDeEmpresas* lista, Empresa novaEmpresa);



#endif // LISTAS_H_INCLUDED
