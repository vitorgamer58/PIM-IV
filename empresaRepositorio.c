#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "fileHelper.h"

bool inserirEmpresa(Empresa empresa)
{
    FILE *ArquivoEmpresas = abrirArquivoParaGravacao("empresas.txt");

    if(ArquivoEmpresas == NULL)
    {
        return false;
    }

    char empresaLinha[1000];

    strcpy(empresaLinha, empresa.nomeDoResponsavel);
    strcat(empresaLinha, ";");
    strcat(empresaLinha, empresa.documentoDoResponsavel);
    strcat(empresaLinha, ";");
    strcat(empresaLinha, empresa.nomeFantasia);
    strcat(empresaLinha, ";");
    strcat(empresaLinha, empresa.razaoSocial);
    strcat(empresaLinha, ";");
    strcat(empresaLinha, empresa.emailDaEmpresa);
    strcat(empresaLinha, ";");
    strcat(empresaLinha, empresa.telefoneDaEmpresa);
    strcat(empresaLinha, ";");
    strcat(empresaLinha, empresa.enderecoDaEmpresa);
    strcat(empresaLinha, ";");
    strcat(empresaLinha, empresa.cnpj);

    fprintf(ArquivoEmpresas, "%s\n", empresaLinha);

    fclose(ArquivoEmpresas);

    return true;
}

Empresa buscarEmpresa(const char *cnpj)
{
    Empresa empresa;
    empresa.isValid = false;

    FILE *ArquivoEmpresas = abrirOuCriarArquivo("empresas.txt");

    if (ArquivoEmpresas == NULL)
    {
        // Tratamento de erro: arquivo n�o p�de ser aberto
        return empresa;
    }

    while(fscanf(ArquivoEmpresas, "%100[^;];%100[^;];%100[^;];%100[^;];%100[^;];%100[^;];%200[^;];%15[^\n]\n",
                 empresa.nomeDoResponsavel,
                 empresa.documentoDoResponsavel,
                 empresa.nomeFantasia,
                 empresa.razaoSocial,
                 empresa.emailDaEmpresa,
                 empresa.telefoneDaEmpresa,
                 empresa.enderecoDaEmpresa,
                 empresa.cnpj
                ) != EOF)
    {
        if(strcmp(cnpj, empresa.cnpj) == 0)
        {
            empresa.isValid = true;
            fclose(ArquivoEmpresas);
            return empresa;
        }
    }

    fclose(ArquivoEmpresas);

    return empresa;
}
