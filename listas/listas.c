#include "listas.h"
#include "../types.h"

listaDeResiduos* iniciaListaDeResiduos() {
    return NULL;
}

listaDeResiduos* insereNaListaDeResiduos(listaDeResiduos* lista, Residuo novoResiduo)
{
    listaDeResiduos* nova_lista = (listaDeResiduos*)malloc(sizeof lista);
    nova_lista->residuo = novoResiduo;
    nova_lista->proximo = lista;
    return nova_lista;
}
