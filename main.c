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
    printf("    TOTAL DE RESIDUOS CADASTRADADOS E FATURAMENTO\n");
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
        printf("CNPJ: %s\nResiduos: %d toneladas\nFaturamento: R$%.2f\n\n",
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
            printf("---- Deseja salvar este relatorio em um arquivo? -----\n\n");
            printf("[1] Sim\n");
            printf("[2] Nao\n");
            if (scanf("%d", &escolha) != 1)
            {
                while(getchar() != '\n');
            }

            switch (escolha)
            {
            case 1:
                printf("\n------------------------------------------------------\n");
                printf("           SALVANDO RELATORIO EM UM ARQUIVO\n");
                printf("------------------------------------------------------\n\n");
                printf("Digite o nome desejado para o arquivo do relatorio: ");
                scanf("%s", nomeDoArquivoDeRelatorio);
                strcat(nomeDoArquivoDeRelatorio, ".txt");
                gravarStringNoArquivo(nomeDoArquivoDeRelatorio, relatorio);
                printf("\n------------ RELATORIO SALVO COM SUCESSO!! ------------\n");
                Sleep(2000);
                relatorios();
            case 2:
                relatorios();
                break;
            default:
                printf("\n---------  Opcao invalida! Tente novamente.  ---------\n\n");
                system("pause");
                break;
            }
        }
        while(escolha != 2);

    printf("\n-----------------------> SAINDO");
    relatorios();
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
    printf("          RELATORIO DE RESIDUOS POR EMPRESA\n");
    printf("------------------------------------------------------\n\n");

    printf("Digite o CNPJ (apenas numeros) da empresa:\n");
    getchar();
    fgets(cnpj, sizeof(cnpj), stdin);
    cnpj[strcspn(cnpj, "\n")] = 0; // Remove o caractere de nova linha

    listaDeResiduos = buscarResiduoPorEmpresa(cnpj);

    if(listaDeResiduos == NULL)
    {
        do
        {
            printf("\n------ RESIDUOS NAO ENCONTRADOS PARA ESTE CNPJ! ------\n\n");
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
                printf("\n---------  Opcao invalida! Tente novamente.  ---------\n\n");
                system("pause");
                break;
            }
        }
        while(escolha != 2);
    }
    printf("\n");

    while (listaDeResiduos != NULL)
    {
        printf("\Residuos cadastrados: %d toneladas.\n", listaDeResiduos->residuo.toneladas);

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
            printf("\n---- Deseja salvar este relatorio em um arquivo? -----\n\n");
            printf("[1] Sim\n");
            printf("[2] Nao\n");
            if (scanf("%d", &escolhaDois) != 1)
            {
                while(getchar() != '\n');
            }

            switch (escolhaDois)
            {
            case 1:
                printf("\n------------------------------------------------------\n");
                printf("           SALVANDO RELATORIO EM UM ARQUIVO\n");
                printf("------------------------------------------------------\n\n");
                printf("Digite o nome desejado para o arquivo do relatorio:\n");
                scanf("%s", nomeDoArquivoDeRelatorio);
                strcat(nomeDoArquivoDeRelatorio, ".txt");
                gravarStringNoArquivo(nomeDoArquivoDeRelatorio, relatorio);
                printf("\n------------ RELATORIO SALVO COM SUCESSO!! ------------\n");
                Sleep(2000);
                relatorios();
            case 2:
                relatorios();
                break;
            default:
                printf("\n---------  Opcao invalida! Tente novamente.  ---------\n\n");
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
    printf("                      RELATORIOS\n");
    printf("------------------------------------------------------\n");

    do
    {
        printf("\nEscolha uma das opcoes abaixo:\n\n");
        printf("1. Relatorio de residuos por empresa\n");
        printf("2. Total de residuos cadastrados e faturamento\n");
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
            printf("\n---------  Opcao invalida! Tente novamente.  ---------\n\n");
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
    printf("                 CADASTRO DE RESIDUOS\n");
    printf("------------------------------------------------------\n\n");
    printf("Digite o CNPJ (apenas numeros) da empresa:\n");
    getchar();
    fgets(cnpj, sizeof(cnpj), stdin);
    cnpj[strcspn(cnpj, "\n")] = 0; // Remove o caractere de nova linha

    strcpy(residuo.cnpj, cnpj);
    empresa = buscarEmpresa(cnpj);

    if(!empresa.isValid)
    {
        do
        {
            printf("\n-------------- Empresa nao encontrada!! --------------\n\n");
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
                printf("\n---------  Opcao invalida! Tente novamente.  ---------\n\n");
                system("pause");
                break;
            }
        }
        while(escolha != 2);
    }

    printf("\nEmpresa cadastrada: ");
    printf(empresa.nomeFantasia);
    printf("\nDigite a quantidade de residuos em toneladas (numero inteiro): ");
    scanf("%d", &residuo.toneladas);

    inserirResiduo(residuo);

    printf("\n---------- RESIDUO CADASTRADO COM SUCESSO!! ----------\n");
    Sleep(2000);

}

void cadastrarUsuario() // TELA DE CADASTRO DE USU�RIOS
{
    char nomeDeUsuario[50], senha[50];

    system("cls");
    printf("------------------------------------------------------\n");
    printf("              CADASTRO DE NOVOS USUARIOS\n");
    printf("------------------------------------------------------\n\n");

    printf("Digite o nome do novo usuario: ");
    scanf("%s", nomeDeUsuario);
    printf("Agora digite a senha: ");
    scanf("%s", senha);

    char* senhaCriptografada = criptografar(senha);

    bool usuarioFoiCadastrado=inserirUsuario(nomeDeUsuario, senhaCriptografada);

    if (usuarioFoiCadastrado)
    {
        printf("\n-------- NOVO USUARIO CADASTRADO COM SUCESSO! --------\n");
    }

    Sleep(1500);
    renderizaMenuEDireciona();
}

void cadastrarIndustria() // TELA DE CADASTRO DE INDUSTRIAS
{
    Empresa empresa;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("               CADASTRO DE INDUSTRIAS\n");
    printf("------------------------------------------------------\n");

    // FORMUL�RIO COM BASE NAS INFORMA��ES SUGERIDAS DO PIM

    printf("\n- Qual o nome do responsavel pela empresa? ");
    fflush(stdin);
    fgets(empresa.nomeDoResponsavel, sizeof(empresa.nomeDoResponsavel), stdin);
    empresa.nomeDoResponsavel[strcspn(empresa.nomeDoResponsavel, "\n")] = 0; // Remove o '\n'

    printf("\n- Qual o documento (RG ou CPF) do responsavel pela empresa? ");
    fflush(stdin);
    fgets(empresa.documentoDoResponsavel, sizeof(empresa.documentoDoResponsavel), stdin);
    empresa.documentoDoResponsavel[strcspn(empresa.documentoDoResponsavel, "\n")] = 0;

    printf("\n- Qual a razao social da empresa? ");
    fflush(stdin);
    fgets(empresa.razaoSocial, sizeof(empresa.razaoSocial), stdin);
    empresa.razaoSocial[strcspn(empresa.razaoSocial, "\n")] = 0;

    printf("\n- Qual o nome fantasia da empresa? ");
    fflush(stdin);
    fgets(empresa.nomeFantasia, sizeof(empresa.nomeFantasia), stdin);
    empresa.nomeFantasia[strcspn(empresa.nomeFantasia, "\n")] = 0;

    printf("\n- Qual o CNPJ (apenas numeros) da empresa? ");
    fflush(stdin);
    fgets(empresa.cnpj, sizeof(empresa.cnpj), stdin);
    empresa.cnpj[strcspn(empresa.cnpj, "\n")] = 0;

    printf("\n- Qual o numero de telefone da empresa? ");
    fflush(stdin);
    fgets(empresa.telefoneDaEmpresa, sizeof(empresa.telefoneDaEmpresa), stdin);
    empresa.telefoneDaEmpresa[strcspn(empresa.telefoneDaEmpresa, "\n")] = 0;

    printf("\n- Padrao para o preenchimento da proxima pergunta:\n");
    printf("   > RUA, NUMERO, BAIRRO, CIDADE, ESTADO, CEP <  \n");
    printf("- Qual o endereco da empresa? ");
    fflush(stdin);
    fgets(empresa.enderecoDaEmpresa, sizeof(empresa.enderecoDaEmpresa), stdin);
    empresa.enderecoDaEmpresa[strcspn(empresa.enderecoDaEmpresa, "\n\r")] = 0;

    printf("\n- Qual o e-mail da empresa? ");
    fflush(stdin);
    fgets(empresa.emailDaEmpresa, sizeof(empresa.emailDaEmpresa), stdin);
    empresa.emailDaEmpresa[strcspn(empresa.emailDaEmpresa, "\n\r")] = 0;

    inserirEmpresa(empresa);

    printf("\n------------------------------------------------------\n");
    printf("          INDUSTRIA CADASTRADA COM SUCESSO!\n");
    printf("------------------------------------------------------\n");

    Sleep(1500);
    renderizaMenuEDireciona();
}

void renderizaMenuEDireciona() // TELA DE MENU E DIRECIONAMENTO
{
    int escolha;

    do
    {
        system("cls");
        printf("------------------------------------------------------\n");
        printf("                    MENU PRINCIPAL:\n");
        printf("------------------------------------------------------\n\n");

        printf("1. Cadastrar novo usuario\n");
        printf("2. Cadastrar industria\n");
        printf("3. Cadastrar residuos\n");
        printf("4. Exibir relatorios\n");
        printf("5. Sair\n");

        printf("\nEscolha uma opcao: ");
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
            printf("\n---------  Opcao invalida! Tente novamente.  ---------\n\n");
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

void logar(char* nomeDeUsuario, char* senha) // FUN��O E TELAS DE LOGIN
{
    Usuario usuario;

    printf("Digite seu usuario: ");
    scanf("%s", nomeDeUsuario);

    printf("Digite sua senha: ");
    scanf("%s", senha);

    usuario = buscarUsuario(nomeDeUsuario);

    char* senhaDescriptografada = descriptografar(usuario.senha);

    if(!usuario.isValid)
    {
        printf("\n-----------  ERRO: usuario nao encontrado  -----------\n\n");
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
        printf("\n---------------  ERRO: senha invalida  ---------------\n\n");
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

int main() // TELA INCIAL E LOGIN
{
    char nomeDeUsuario[50], senha[50];
    telaInicial();
    logar(nomeDeUsuario, senha);

    return 0;
}

void telaInicial()
{
    system("cls");
    //setlocale(LC_ALL, "Portuguese");
    printf("------------------------------------------------------\n");
    printf("          | STARTUP DE SOLUCOES AMBIENTAIS |\n");
    printf("------------------------------------------------------\n");
    printf(" Ola! Efetue login para ter acesso ao nosso sistema.\n\n");
}
