#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "fileHelper.h"

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
