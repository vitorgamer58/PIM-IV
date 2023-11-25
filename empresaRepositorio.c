#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "fileHelper.h"
#include "listas/listas.h"

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
        // Tratamento de erro: arquivo nao pode ser aberto
        return empresa;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), ArquivoEmpresas))
    {
        if(sscanf(buffer, "%100[^;];%100[^;];%100[^;];%100[^;];%100[^;];%100[^;];%200[^;];%15[^\n]",
                  empresa.nomeDoResponsavel,
                  empresa.documentoDoResponsavel,
                  empresa.nomeFantasia,
                  empresa.razaoSocial,
                  empresa.emailDaEmpresa,
                  empresa.telefoneDaEmpresa,
                  empresa.enderecoDaEmpresa,
                  empresa.cnpj
                 ) == 8)
        {
            if(strcmp(cnpj, empresa.cnpj) == 0)
            {
                empresa.isValid = true;
                break;
            }
        }
    }

    fclose(ArquivoEmpresas);

    return empresa;
}

ListaDeEmpresas* buscarTodasEmpresas()
{
    Empresa empresa;
    ListaDeEmpresas *listaDeEmpresas = iniciaListaDeEmpresas();
    empresa.isValid = false;

    FILE *ArquivoEmpresas = abrirOuCriarArquivo("empresas.txt");

    if (ArquivoEmpresas == NULL)
    {
        return listaDeEmpresas;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), ArquivoEmpresas))
    {
        if(sscanf(buffer, "%100[^;];%100[^;];%100[^;];%100[^;];%100[^;];%100[^;];%200[^;];%15[^\n]",
                  empresa.nomeDoResponsavel,
                  empresa.documentoDoResponsavel,
                  empresa.nomeFantasia,
                  empresa.razaoSocial,
                  empresa.emailDaEmpresa,
                  empresa.telefoneDaEmpresa,
                  empresa.enderecoDaEmpresa,
                  empresa.cnpj
                 ) == 8)
        {
            empresa.isValid = true;
            listaDeEmpresas = insereNaListaDeEmpresas(listaDeEmpresas, empresa);
        }
    }

    fclose(ArquivoEmpresas);

    return listaDeEmpresas;
}

