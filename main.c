#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include "types.h"
#include "userRepository.h"
#include "verificadores.c"

void cadastrarUsuario() // TELA DE CADASTRO DE USU�RIOS
{
    char nomeDeUsuario[50], senha[50];

    system("cls");
    printf("------------------------------------------------------\n");
    printf("              CADASTRO DE NOVOS USU�RIOS\n");
    printf("------------------------------------------------------\n");
    printf("\n");
    printf("Digite o nome do novo usu�rio: ");
    scanf("%s", nomeDeUsuario);
    printf("Agora digite a senha: ");
    scanf("%s", senha);
    printf("\n");
    bool usuarioFoiCadastrado=inserirUsuario(nomeDeUsuario, senha);

    if (usuarioFoiCadastrado)
    {
        printf("-------- NOVO USU�RIO CADASTRADO COM SUCESSO! --------\n");
    }

    printf("\n");
    system ("pause");
    renderizaMenuEDireciona();

}

void cadastrarIndustria() // TELA DE CADASTRO DE INDUSTRIAS
{
    char nomeDoResp[50], enderecoDoResp[100], nomeDaEmpresa[50], razaoSocial[50], nomeFantasia[50];
    char enderecoDaEmpresa[100], emailEmpresa[30];
    int cpf[12], cnpj[15], telDoResp[15], telDaEmpresa[15], aberturaEmpresa[11];

    system("cls");
    printf("------------------------------------------------------\n");
    printf("               CADASTRO DE IND�STRIAS\n");
    printf("------------------------------------------------------\n");
    printf("  Iniciando com os dados do respons�vel pela empresa.\n");
    printf("\n");

    // FORMUL�RIO COM BASE NAS INFORMA��ES SUGERIDAS DO PIM

    printf("- Qual o nome do respons�vel pela empresa? ");
    scanf("%s", nomeDoResp);
    printf("\n");

    verificadorCPF(); // Apenas testando (c�digo em verificadores.c)
    printf("\n");

    printf("---> Qual o endere�o do respons�vel pela empresa?\n");
    printf("SIGA O PADR�O: RUA, N�MERO, BAIRRO, CIDADE, ESTADO e CEP\n");
    printf("\n");
    printf("- Digite aqui: ");
    scanf("%s", enderecoDoResp);
    printf("\n");

    verificadorTelefone(); // Apenas testando (c�digo em verificadores.c)
    printf(" \n");


    printf("------------------------------------------------------\n");
    printf("                DADOS CADASTRADOS!\n");
    printf("------------------------------------------------------\n");
    printf("       Agora vamos cadastrar os dados da empresa.\n");
    printf("\n");

    printf("- Qual o nome empresa? ");
    scanf("%s", nomeDaEmpresa);
    printf(" \n");

    printf("- Qual o CNPJ (apenas n�meros) da empresa? ");
    scanf("%d", &cnpj);
    printf(" \n");

    printf("- Qual a raz�o social da empresa? ");
    scanf("%s", razaoSocial);
    printf(" \n");

    printf("- Qual o nome fantasia da empresa? ");
    scanf("%s", nomeFantasia);
    printf(" \n");

    printf("- Qual o n�mero de telefone da empresa? ");
    scanf("%d", &telDaEmpresa);
    printf(" \n");

    printf("---> Qual o endere�o da empresa?\n");
    printf("SIGA O PADR�O: RUA, N�MERO, BAIRRO, CIDADE, ESTADO e CEP\n");
    printf("\n");
    printf("- Digite aqui: ");
    scanf("%s", enderecoDaEmpresa);
    printf(" \n");

    printf("- Qual o e-mail da empresa? ");
    scanf("%s", emailEmpresa);
    printf(" \n");

    printf("- Qual a data de abertura da empresa? ");
    scanf("%d", &aberturaEmpresa);
    printf("\n");

    printf("------------------------------------------------------\n");
    printf("          IND�STRIA CADASTRADA COM SUCESSO!\n");
    printf("------------------------------------------------------\n");

    printf("\n");
    system("pause");


}

void renderizaMenuEDireciona() // TELA DE MENU E DIRECIONAMENTO
{
    int escolha;

    do
    {
        system("cls");
        printf("------------------------------------------------------\n");
        printf("                    MENU PRINCIPAL:\n");
        printf("------------------------------------------------------\n");
        printf("\n");
        printf("1. Cadastrar novo usu�rio\n");
        printf("2. Cadastrar ind�stria\n");
        printf("3. Exibir dados da ind�stria\n");
        printf("4. Exibir relat�rios\n");
        printf("5. Sair\n");
        printf("\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        switch(escolha)
        {
        case 1:
            cadastrarUsuario();
        case 2:
            cadastrarIndustria();
        case 3:
            break;
        case 4:
            break;
        case 5:
            return;
        default:
            printf("\n");
            printf("---------  Op��o inv�lida! Tente novamente.  ---------\n");
            printf("\n");
            system("pause");
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
        printf("\n");
        printf("-----------  ERRO: usu�rio n�o encontrado  -----------\n");
        printf("\n");
        printf("                   TENTE NOVAMENTE\n");
        printf("\n");
        system("pause");
        system("cls");
        main();
        logar(nomeDeUsuario, senha);

        return;
    }

    if(checarSenha(usuario.senha, senha))
    {
        printf("\n");
        printf("--------------   LOGADO COM SUCESSO!!   --------------");
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
        printf("Senha inv�lida! Tente novamente!\n");
        printf("\n");
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
    printf(" Ol�! Efetue login para ter acesso ao nosso sistema.\n");
    printf("\n");
    logar(nomeDeUsuario, senha);

    return 0;
}
