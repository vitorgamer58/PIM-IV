#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"

bool inserirEmpresa(Empresa empresa)
{
    FILE *ArquivoEmpresas=abrirArquivoParaGravacao("empresas.txt");

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
    strcat(empresaLinha, empresa.documentoDoResponsavel);
    strcat(empresaLinha, ";");
    strcat(empresaLinha, empresa.cnpj);

    fprintf(ArquivoEmpresas, "%s\n", empresaLinha);

    fclose(ArquivoEmpresas);

    return true;
}

int exibirDadosIndustria() // Esboço da função de exibição de dados
{
    // Nome do arquivo a ser lido.
    char nomeArquivo[] = "usuarios.txt";

    // Abre o arquivo para leitura.
    FILE *arquivo = fopen(nomeArquivo, "r");

    // Verifica se o arquivo foi aberto com sucesso.
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê e exibe os dados do arquivo linha por linha.
    char linha[100]; // Uma linha pode ter até 100 caracteres, ajuste conforme suas necessidades.

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        printf("%s", linha);
    }

        system("pause");
    // Fecha o arquivo.
    fclose(arquivo);

    return 0;
}
