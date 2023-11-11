#include <stdio.h>
#include <string.h>

typedef struct
{
    char cnpj[15];
    int residuos;
} Empresa;


int cnpjExiste(char* cnpj)
{
    FILE *fp;
    char cnpjArquivo[15];

    fp = fopen("banco_de_dados.txt", "r");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo do banco de dados!\n");
        return 0;
    }
    while (fscanf(fp, "%s\n", cnpjArquivo) != EOF)
    {

        if (strcmp(cnpjArquivo, cnpj) == 0)
        {

            fclose(fp);

            return 1;
        }
    }


    fclose(fp);

    return 0;

}

int main()
{
    FILE *fp;
    Empresa empresa;


    sprintf(empresa.cnpj, "21.488.808/0001-09");
    empresa.residuos = 123;

    if (cnpjExiste(empresa.cnpj))
    {

        fp = fopen("relatorio.txt", "w");

        if (fp == NULL)
        {
            printf("Erro ao abrir arquivo!\n");
            return 1;
        }

        fprintf(fp, "Relatório de Resíduos por CNPJ\n");
        fprintf(fp, "------------------------------\n");
        fprintf(fp, "CNPJ: %s\n", empresa.cnpj);
        fprintf(fp, "Resíduos: %d\n", empresa.residuos);


        fclose(fp);

        printf("Relatório gerado com sucesso!\n");

    }

    return 0;
}
