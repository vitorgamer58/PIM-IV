#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#include "types.h"
#include "fileHelper.h"
#include "listas/listas.h"

bool inserirResiduo(Residuo residuo)
{
    FILE *ArquivoResiduos = abrirArquivoParaGravacao("residuos.txt");

    if(ArquivoResiduos == NULL)
    {
        return false;
    }

    char residuosLinha[1000];

    char toneladasStr[50];

    sprintf(toneladasStr, "%d", residuo.toneladas); // CONVERTE INT EM STRING

    strcpy(residuosLinha, residuo.cnpj);
    strcat(residuosLinha, ";");
    strcat(residuosLinha, toneladasStr);

    fprintf(ArquivoResiduos, "%s\n", residuosLinha);

    fclose(ArquivoResiduos);

    return true;
}

ListaDeResiduos* buscarResiduoPorEmpresa(const char* cnpj)
{
    FILE *ArquivoResiduos = abrirOuCriarArquivo("Residuos.txt");
    Residuo residuo;
    ListaDeResiduos *listaDeResiduos = iniciaListaDeResiduos();
    char linha[1000];

    if(ArquivoResiduos == NULL)
    {
        return NULL;
    }

    while(fgets(linha, sizeof(linha), ArquivoResiduos) != NULL)
    {
        sscanf(linha, "%15[^;];%d", residuo.cnpj, &residuo.toneladas);
        residuo.cnpj[15] = '\0';

        if(strcmp(cnpj, residuo.cnpj) == 0)
        {
            listaDeResiduos = insereNaListaDeResiduos(listaDeResiduos, residuo);
        }
    }

    fclose(ArquivoResiduos);

    return listaDeResiduos;
}

