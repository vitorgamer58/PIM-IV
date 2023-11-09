#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include "types.h"
#include "userRepository.h"
#include "empresaRepositorio.h"

void cadastrarUsuario() // TELA DE CADASTRO DE USU�RIOS
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

    bool usuarioFoiCadastrado=inserirUsuario(nomeDeUsuario, senha);

    if (usuarioFoiCadastrado)
    {
        printf("\n-------- NOVO USU�RIO CADASTRADO COM SUCESSO! --------\n");
    }

    Sleep(1500);
    renderizaMenuEDireciona();
}

void cadastrarIndustria() // TELA DE CADASTRO DE INDUSTRIAS
{
    Empresa empresa;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("               CADASTRO DE IND�STRIAS\n");
    printf("------------------------------------------------------\n");
    getchar();

    // FORMUL�RIO COM BASE NAS INFORMA��ES SUGERIDAS DO PIM

    printf("\n- Qual o nome do respons�vel pela empresa? ");
    fgets(empresa.nomeDoResponsavel, sizeof(empresa.nomeDoResponsavel), stdin);
    empresa.nomeDoResponsavel[strcspn(empresa.nomeDoResponsavel, "\n")] = 0; // Remove o '\n'

    printf("\n- Qual o documento do respons�vel pela empresa? ");
    fgets(empresa.documentoDoResponsavel, sizeof(empresa.documentoDoResponsavel), stdin);
    empresa.documentoDoResponsavel[strcspn(empresa.documentoDoResponsavel, "\n")] = 0;

    printf("\n- Qual a raz�o social da empresa? ");
    fgets(empresa.razaoSocial, sizeof(empresa.razaoSocial), stdin);
    empresa.razaoSocial[strcspn(empresa.razaoSocial, "\n")] = 0;

    printf("\n- Qual o nome fantasia da empresa? ");
    fgets(empresa.nomeFantasia, sizeof(empresa.nomeFantasia), stdin);
    empresa.nomeFantasia[strcspn(empresa.nomeFantasia, "\n")] = 0;

    printf("\n- Qual o CNPJ (apenas n�meros) da empresa? ");
    fgets(empresa.cnpj, sizeof(empresa.cnpj), stdin);
    empresa.cnpj[strcspn(empresa.cnpj, "\n")] = 0;
    getchar();

    printf("\n- Qual o n�mero de telefone da empresa? ");
    fgets(empresa.telefoneDaEmpresa, sizeof(empresa.telefoneDaEmpresa), stdin);
    empresa.telefoneDaEmpresa[strcspn(empresa.telefoneDaEmpresa, "\n")] = 0;

    printf("\n- Padr�o para o preenchimento da pr�xima pergunta:\n");
    printf("  > RUA, N�MERO, BAIRRO, CIDADE, ESTADO e CEP <  \n");
    printf("- Qual o endere�o da empresa? ");
    fgets(empresa.enderecoDaEmpresa, sizeof(empresa.enderecoDaEmpresa), stdin);
    empresa.enderecoDaEmpresa[strcspn(empresa.enderecoDaEmpresa, "\n\r")] = 0;

    printf("\n- Qual o e-mail da empresa? ");
    fgets(empresa.emailDaEmpresa, sizeof(empresa.emailDaEmpresa), stdin);
    empresa.emailDaEmpresa[strcspn(empresa.emailDaEmpresa, "\n\r")] = 0;

    // Aqui voc� dever� ter a fun��o inserirEmpresa() definida em outra parte do seu c�digo
    inserirEmpresa(empresa);

    printf("\n------------------------------------------------------\n");
    printf("          IND�STRIA CADASTRADA COM SUCESSO!\n");
    printf("------------------------------------------------------\n");

    Sleep(1500); /* Pausa o programa por 1.5 segundos;
    Aqui voc� dever� ter a fun��o renderizaMenuEDireciona() definida em outra parte do seu c�digo */
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

        printf("1. Cadastrar novo usu�rio\n");
        printf("2. Cadastrar ind�stria\n");
        printf("3. Exibir dados da ind�stria\n");
        printf("4. Exibir relat�rios\n");
        printf("5. Sair\n");

        printf("\nEscolha uma op��o: ");
        scanf("%d", &escolha);

        switch(escolha)
        {
        case 1:
            cadastrarUsuario();
            break;
        case 2:
            cadastrarIndustria();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            printf("\n-------------------------------> Saindo do programa...\n");
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

void logar(char* nomeDeUsuario, char* senha) // FUN��O E TELAS DE LOGIN
{
    Usuario usuario;

    printf("Digite seu usu�rio: ");
    scanf("%s", nomeDeUsuario);

    printf("Digite sua senha: ");
    scanf("%s", senha);

    usuario = buscarUsuario(nomeDeUsuario);

    if(!usuario.isValid)
    {
        printf("\n-----------  ERRO: usu�rio n�o encontrado  -----------\n\n");
        printf("                   TENTE NOVAMENTE\n\n");

        system("pause");
        system("cls");
        main();

        return;
    }

    if(checarSenha(usuario.senha, senha))
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
        printf("\n");
        printf("Senha inv�lida! Tente novamente!\n\n");

        memset(nomeDeUsuario, 0, sizeof(nomeDeUsuario));
        memset(senha, 0, sizeof(senha));
        logar(nomeDeUsuario, senha);
    }
}

int main() // TELA INCIAL
{
    char nomeDeUsuario[50], senha[50];

    setlocale(LC_ALL, "Portuguese");
    printf("------------------------------------------------------\n");
    printf("          | STARTUP DE SOLU��ES AMBIENTAIS |\n");
    printf("------------------------------------------------------\n");
    printf(" Ol�! Efetue login para ter acesso ao nosso sistema.\n\n");

    logar(nomeDeUsuario, senha);

    return 0;
}
