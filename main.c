#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include "types.h"
#include "userRepository.h"
#include "empresaRepositorio.h"
#include "residuosRepositorio.h"
#include "helpers/helpers.h"
#include "helpers/fileHelper.h"

void relatorioSomaDeResiduos()
{
    ListaDeEmpresas *listaDeEmpresas;
    ListaDeResiduos *listaDeResiduos;
    ListaDeResiduos *listaSomaDeResiduosPorEmpresa = iniciaListaDeResiduos();
    char relatorio[10000] = "CNPJ;Pesagem;Faturamento\n";
    int escolha;
    char nomeDoArquivoDeRelatorio[50];

    system("cls");
    printf("------------------------------------------------------\n");
    printf("    TOTAL DE RES�DUOS CADASTRADADOS E FATURAMENTO\n");
    printf("------------------------------------------------------\n\n");

    listaDeEmpresas = buscarTodasEmpresas();

    while (listaDeEmpresas != NULL)
    {
        listaDeResiduos = buscarResiduoPorEmpresa(listaDeEmpresas->empresa.cnpj);

        int somaDeResiduosEmpresaAtual = 0;

        while(listaDeResiduos != NULL)
        {
            somaDeResiduosEmpresaAtual += listaDeResiduos->residuo.toneladas;
            listaDeResiduos = listaDeResiduos->proximo;
        }

        Residuo residuo;
        strcpy(residuo.cnpj, listaDeEmpresas->empresa.cnpj);
        residuo.toneladas = somaDeResiduosEmpresaAtual;
        residuo.faturamento = calcularFaturamento(somaDeResiduosEmpresaAtual);

        listaSomaDeResiduosPorEmpresa = insereNaListaDeResiduos(listaSomaDeResiduosPorEmpresa, residuo);

        listaDeEmpresas = listaDeEmpresas->proximo;
    }

    while (listaSomaDeResiduosPorEmpresa != NULL)
    {
        printf("CNPJ: %s\nRes�duos: %d toneladas\nFaturamento: R$%.2f\n\n",
               listaSomaDeResiduosPorEmpresa->residuo.cnpj,
               listaSomaDeResiduosPorEmpresa->residuo.toneladas,
               listaSomaDeResiduosPorEmpresa->residuo.faturamento
              );

        char somaResiduosEmpresa[100];

        snprintf(somaResiduosEmpresa, sizeof(somaResiduosEmpresa),"%s;%d;%.2f\n",
                 listaSomaDeResiduosPorEmpresa->residuo.cnpj,
                 listaSomaDeResiduosPorEmpresa->residuo.toneladas,
                 listaSomaDeResiduosPorEmpresa->residuo.faturamento
                );
        strcat(relatorio, somaResiduosEmpresa);

        listaSomaDeResiduosPorEmpresa = listaSomaDeResiduosPorEmpresa->proximo;
    }

    Sleep(500);

    do
    {
        printf("---- Deseja salvar este relat�rio em um arquivo? -----\n\n");
        printf("[1] Sim\n");
        printf("[2] N�o\n");
        if (scanf("%d", &escolha) != 1)
        {
            while(getchar() != '\n');
        }

        switch (escolha)
        {
        case 1:
            printf("\n------------------------------------------------------\n");
            printf("           SALVANDO RELAT�RIO EM UM ARQUIVO\n");
            printf("------------------------------------------------------\n\n");
            printf("Digite o nome desejado para o arquivo do relat�rio:\n");
            scanf("%s", nomeDoArquivoDeRelatorio);
            strcat(nomeDoArquivoDeRelatorio, ".txt");
            gravarStringNoArquivo(nomeDoArquivoDeRelatorio, relatorio);
            printf("\n------------ RELAT�RIO SALVO COM SUCESSO!! ------------\n");
            Sleep(2000);
            relatorios();
        case 2:
            relatorios();
            break;
        default:
            printf("\n---------  Op��o inv�lida! Tente novamente.  ---------\n\n");
            system("pause");
            break;
        }
    }
    while(escolha != 2);

}


void relatorioResiduosPorEmpresas()
{
    char cnpj[16];
    int escolha;
    ListaDeResiduos *listaDeResiduos;

    char relatorio[10000] = "CNPJ;Pesagem;\n";
    int escolhaDois;
    char nomeDoArquivoDeRelatorio[50];

    system("cls");
    printf("------------------------------------------------------\n");
    printf("          RELAT�RIO DE RES�DUOS POR EMPRESA\n");
    printf("------------------------------------------------------\n\n");

    printf("Digite o CNPJ (apenas n�meros) da empresa:\n");
    getchar();
    fgets(cnpj, sizeof(cnpj), stdin);
    cnpj[strcspn(cnpj, "\n")] = 0;

    listaDeResiduos = buscarResiduoPorEmpresa(cnpj);

    if(listaDeResiduos == NULL)
    {
        do
        {
            printf("\n------ RES�DUOS N�O ENCONTRADOS PARA ESTE CNPJ! ------\n\n");
            printf("[1] Para tentar novamente\n");
            printf("[2] Para voltar ao menu principal\n");
            if (scanf("%d", &escolha) != 1)
            {
                while(getchar() != '\n');
            }

            switch (escolha)
            {
            case 1:
                relatorioResiduosPorEmpresas();
            case 2:
                renderizaMenuEDireciona();
                break;
            default:
                printf("\n---------  Op��o inv�lida! Tente novamente.  ---------\n\n");
                system("pause");
                break;
            }
        }
        while(escolha != 2);
    }
    printf("\n");

    while (listaDeResiduos != NULL)
    {
        printf("\Res�duos cadastrados: %d toneladas\n", listaDeResiduos->residuo.toneladas);

        char somaResiduosEmpresa[100];

        snprintf(somaResiduosEmpresa, sizeof(somaResiduosEmpresa),"%s;%d\n",
                 listaDeResiduos->residuo.cnpj,
                 listaDeResiduos->residuo.toneladas
                );

        strcat(relatorio, somaResiduosEmpresa);

        listaDeResiduos = listaDeResiduos->proximo;
    }

    do
    {
        printf("\n---- Deseja salvar este relat�rio em um arquivo? -----\n\n");
        printf("[1] Sim\n");
        printf("[2] N�o\n");
        if (scanf("%d", &escolhaDois) != 1)
        {
            while(getchar() != '\n');
        }

        switch (escolhaDois)
        {
        case 1:
            printf("\n------------------------------------------------------\n");
            printf("           SALVANDO RELAT�RIO EM UM ARQUIVO\n");
            printf("------------------------------------------------------\n\n");
            printf("Digite o nome desejado para o arquivo do relat�rio:\n");
            scanf("%s", nomeDoArquivoDeRelatorio);
            strcat(nomeDoArquivoDeRelatorio, ".txt");
            gravarStringNoArquivo(nomeDoArquivoDeRelatorio, relatorio);
            printf("\n------------ RELAT�RIO SALVO COM SUCESSO!! ------------\n");
            Sleep(2000);
            relatorios();
        case 2:
            relatorios();
            break;
        default:
            printf("\n---------  Op��o inv�lida! Tente novamente.  ---------\n\n");
            system("pause");
            break;
        }
    }
    while(escolhaDois != 2);
}

void relatorios()
{
    int escolha;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("                      RELAT�RIOS\n");
    printf("------------------------------------------------------\n");

    do
    {
        printf("\nEscolha uma das op��es abaixo:\n\n");
        printf("1. Relat�rio de res�duos por empresa\n");
        printf("2. Total de res�duos cadastrados e faturamento\n");
        printf("3. Voltar ao menu principal\n");
        if (scanf("%d", &escolha) != 1)
        {
            while(getchar() != '\n');
        }

        switch (escolha)
        {
        case 1:
            relatorioResiduosPorEmpresas();
            break;
        case 2:
            relatorioSomaDeResiduos();
            break;
        case 3:
            renderizaMenuEDireciona();
            break;
        default:
            printf("\n---------  Op��o inv�lida! Tente novamente.  ---------\n\n");
            system("pause");
            break;
        }
    }
    while(escolha != 3);
}

void cadastrarResiduos()
{
    Residuo residuo;
    Empresa empresa;
    char cnpj[16];
    int escolha;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("                 CADASTRO DE RES�DUOS\n");
    printf("------------------------------------------------------\n\n");
    printf("Digite o CNPJ (apenas n�meros) da empresa:\n");
    getchar();
    fgets(cnpj, sizeof(cnpj), stdin);
    cnpj[strcspn(cnpj, "\n")] = 0;

    strcpy(residuo.cnpj, cnpj);
    empresa = buscarEmpresa(cnpj);

    if(!empresa.isValid)
    {
        do
        {
            printf("\n-------------- Empresa n�o encontrada!! --------------\n\n");
            printf("[1] Para tentar novamente\n");
            printf("[2] Para voltar ao menu principal\n");
            if (scanf("%d", &escolha) != 1)
            {
                while(getchar() != '\n');
            }

            switch(escolha)
            {
            case 1:
                cadastrarResiduos();
                break;
            case 2:
                renderizaMenuEDireciona();
                break;
            default:
                printf("\n---------  Op��o inv�lida! Tente novamente.  ---------\n\n");
                system("pause");
                break;
            }
        }
        while(escolha != 2);
    }

    printf("\nEmpresa cadastrada: ");
    printf(empresa.nomeFantasia);
    printf("\nDigite a quantidade de res�duos em toneladas (n�mero inteiro): ");
    scanf("%d", &residuo.toneladas);

    inserirResiduo(residuo);

    printf("\n---------- RES�DUO CADASTRADO COM SUCESSO!! ----------\n");
    Sleep(2000);

}

void cadastrarUsuario()
{
    char nomeDeUsuario[50], senha[50];

    system("cls");
    printf("------------------------------------------------------\n");
    printf("              CADASTRO DE NOVOS USU�RIOS\n");
    printf("------------------------------------------------------\n\n");

    printf("Digite o nome do novo usu�rio: ");
    scanf("%s", nomeDeUsuario);
    printf("Agora digite a senha: ");
    scanf("%s", senha);

    char* senhaCriptografada = criptografar(senha);

    bool usuarioFoiCadastrado=inserirUsuario(nomeDeUsuario, senhaCriptografada);

    if (usuarioFoiCadastrado)
    {
        printf("\n-------- NOVO USU�RIO CADASTRADO COM SUCESSO! --------\n");
    }

    Sleep(1500);
    renderizaMenuEDireciona();
}

void cadastrarIndustria()
{
    Empresa empresa;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("               CADASTRO DE IND�STRIAS\n");
    printf("------------------------------------------------------\n");

    printf("\n- Qual o nome do respons�vel pela empresa?\n");
    fflush(stdin);
    fgets(empresa.nomeDoResponsavel, sizeof(empresa.nomeDoResponsavel), stdin);
    empresa.nomeDoResponsavel[strcspn(empresa.nomeDoResponsavel, "\n")] = 0;

    printf("\n- Qual o RG ou CPF do respons�vel pela empresa?\n");
    fflush(stdin);
    fgets(empresa.documentoDoResponsavel, sizeof(empresa.documentoDoResponsavel), stdin);
    empresa.documentoDoResponsavel[strcspn(empresa.documentoDoResponsavel, "\n")] = 0;

    printf("\n- Qual a raz�o social da empresa?\n");
    fflush(stdin);
    fgets(empresa.razaoSocial, sizeof(empresa.razaoSocial), stdin);
    empresa.razaoSocial[strcspn(empresa.razaoSocial, "\n")] = 0;

    printf("\n- Qual o nome fantasia da empresa?\n");
    fflush(stdin);
    fgets(empresa.nomeFantasia, sizeof(empresa.nomeFantasia), stdin);
    empresa.nomeFantasia[strcspn(empresa.nomeFantasia, "\n")] = 0;

    printf("\n- Qual o CNPJ (apenas n�meros) da empresa?\n");
    fflush(stdin);
    fgets(empresa.cnpj, sizeof(empresa.cnpj), stdin);
    empresa.cnpj[strcspn(empresa.cnpj, "\n")] = 0;

    printf("\n- Qual o n�mero de telefone da empresa?\n");
    fflush(stdin);
    fgets(empresa.telefoneDaEmpresa, sizeof(empresa.telefoneDaEmpresa), stdin);
    empresa.telefoneDaEmpresa[strcspn(empresa.telefoneDaEmpresa, "\n")] = 0;

    printf("\n- Padr�o para o preenchimento da pr�xima pergunta:\n");
    printf("   > RUA, N�MERO, BAIRRO, CIDADE, ESTADO, CEP <  \n");
    printf("- Qual o endere�o da empresa?\n");
    fflush(stdin);
    fgets(empresa.enderecoDaEmpresa, sizeof(empresa.enderecoDaEmpresa), stdin);
    empresa.enderecoDaEmpresa[strcspn(empresa.enderecoDaEmpresa, "\n\r")] = 0;

    printf("\n- Qual o e-mail da empresa?\n");
    fflush(stdin);
    fgets(empresa.emailDaEmpresa, sizeof(empresa.emailDaEmpresa), stdin);
    empresa.emailDaEmpresa[strcspn(empresa.emailDaEmpresa, "\n\r")] = 0;

    inserirEmpresa(empresa);

    printf("\n------------------------------------------------------\n");
    printf("          IND�STRIA CADASTRADA COM SUCESSO!\n");
    printf("------------------------------------------------------\n");

    Sleep(1500);
    renderizaMenuEDireciona();
}

void renderizaMenuEDireciona()
{
    int escolha;

    do
    {
        system("cls");
        printf("------------------------------------------------------\n");
        printf("                    MENU PRINCIPAL:\n");
        printf("------------------------------------------------------\n\n");

        printf("1. Cadastrar novo usu�rio\n");
        printf("2. Cadastrar ind�stria\n");
        printf("3. Cadastrar res�duos\n");
        printf("4. Exibir relat�rios\n");
        printf("5. Sair\n");

        printf("\nEscolha uma op��o: ");
        if (scanf("%d", &escolha) != 1)
        {
            while(getchar() != '\n');
        }

        switch(escolha)
        {
        case 1:
            cadastrarUsuario();
            break;
        case 2:
            cadastrarIndustria();
            break;
        case 3:
            cadastrarResiduos();
            break;
        case 4:
            relatorios();
            break;
        case 5:
            printf("\n-------------------------------> Saindo do programa...\n");
            printf("Digite qualquer tecla para fechar esta janela <-------\n\n");
            exit(0);
            break;
        default:
            printf("\n---------  Op��o inv�lida! Tente novamente.  ---------\n\n");
            system("pause");
            break;

        }
    }
    while(escolha != 5);
}

bool checarSenha(const char* senhaDoUsuario, const char* senhaDigitada)
{
    if (strcmp(senhaDoUsuario, senhaDigitada) == 0)
    {
        return true;
    }

    return false;
}

void logar(char* nomeDeUsuario, char* senha)
{
    Usuario usuario;

    printf("Digite seu usu�rio: ");
    scanf("%s", nomeDeUsuario);

    printf("Digite sua senha: ");
    scanf("%s", senha);

    usuario = buscarUsuario(nomeDeUsuario);

    char* senhaDescriptografada = descriptografar(usuario.senha);

    if(!usuario.isValid)
    {
        printf("\n-----------  ERRO: usu�rio n�o encontrado  -----------\n\n");
        printf("                  TENTE NOVAMENTE!\n\n");

        system("pause");
        system("cls");
        telaInicial();
        logar(nomeDeUsuario, senha);

        return;
    }

    if(checarSenha(senhaDescriptografada, senha))
    {
        printf("\n--------------   LOGADO COM SUCESSO!!   --------------");
        Sleep(1200);
        system ("cls");

        // TELA DE BOAS VINDAS

        printf("------------------------------------------------------\n");
        printf("           BEM-VINDOS AO SISTEMA DA STARTUP!\n");
        printf("------------------------------------------------------\n");
        Sleep(2200);
        renderizaMenuEDireciona();
    }

    else
    {
        printf("\n---------------  ERRO: senha inv�lida  ---------------\n\n");
        printf("                   TENTE NOVAMENTE!\n\n");

        system("pause");
        system("cls");
        telaInicial();
        logar(nomeDeUsuario, senha);

        memset(nomeDeUsuario, 0, sizeof(nomeDeUsuario));
        memset(senha, 0, sizeof(senha));
        logar(nomeDeUsuario, senha);
    }
}

int main()
{
    char nomeDeUsuario[50], senha[50];
    telaInicial();
    logar(nomeDeUsuario, senha);

    return 0;
}

void telaInicial()
{
    system("cls");
    setlocale(LC_ALL, "Portuguese_Brazil");
    printf("------------------------------------------------------\n");
    printf("          | STARTUP DE SOLUCOES AMBIENTAIS |\n");
    printf("------------------------------------------------------\n");
    printf("Ol�! Efetue login para ter acesso ao nosso sistema.\n\n");
}
