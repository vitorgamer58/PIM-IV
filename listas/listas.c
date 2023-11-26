#include <stddef.h>
#include "listas.h"
#include "../types.h"

ListaDeResiduos* iniciaListaDeResiduos()
{
    return NULL;
}

ListaDeResiduos* insereNaListaDeResiduos(ListaDeResiduos* lista, Residuo novoResiduo)
{
    ListaDeResiduos* nova_lista = (ListaDeResiduos*)malloc(sizeof(ListaDeResiduos));
    nova_lista->residuo = novoResiduo;
    nova_lista->proximo = lista;
    return nova_lista;
}

ListaDeEmpresas* iniciaListaDeEmpresas()
{
    return NULL;
}

ListaDeEmpresas* insereNaListaDeEmpresas(ListaDeEmpresas* lista, Empresa novaEmpresa)
{
    ListaDeEmpresas* nova_lista = (ListaDeEmpresas*)malloc(sizeof(ListaDeEmpresas));
    nova_lista->empresa = novaEmpresa;
    nova_lista->proximo = lista;
    return nova_lista;
}
