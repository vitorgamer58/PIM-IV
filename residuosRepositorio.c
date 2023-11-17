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

    if(ArquivoResiduos == NULL)
    {
        return NULL;
    }

    while(fscanf(ArquivoResiduos, "%14[^;];%d", residuo.cnpj, &residuo.toneladas) != EOF)
    {
        residuo.cnpj[14] = '\0'; // Garantindo que a string seja terminada corretamente
        printf("%s\n", cnpj);
        printf("%s\n", residuo.cnpj);
        printf("%d\n\n", strcmp(cnpj, residuo.cnpj));

        size_t length_cnpj = strlen(cnpj);
        size_t length_residuo_cnpj = strlen(residuo.cnpj);

        printf("Comprimento de cnpj: %zu\n", length_cnpj);
        printf("Comprimento de residuo.cnpj: %zu\n", length_residuo_cnpj);


        if(strcmp(cnpj, residuo.cnpj) == 0)
        {
            listaDeResiduos = insereNaListaDeResiduos(listaDeResiduos, residuo);
        }
    }

    fclose(ArquivoResiduos);

    return listaDeResiduos;
}
