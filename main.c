#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include "types.h"
#include "userRepository.h"
#include "verificadores.c"
#include "empresaRepositorio.h"

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
    Empresa empresa;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("               CADASTRO DE IND�STRIAS\n");
    printf("------------------------------------------------------\n");
    printf("  Iniciando com os dados do respons�vel pela empresa.\n");
    printf("\n");
    getchar();

    // FORMUL�RIO COM BASE NAS INFORMA��ES SUGERIDAS DO PIM

    printf("- Qual o nome do respons�vel pela empresa? ");
    fgets(empresa.nomeDoResponsavel, sizeof(empresa.nomeDoResponsavel), stdin);
    empresa.nomeDoResponsavel[strcspn(empresa.nomeDoResponsavel, "\n")] = 0; // Remove o '\n'
    printf("\n");

    printf("- Qual o documento do respons�vel pela empresa? ");
    fgets(empresa.documentoDoResponsavel, sizeof(empresa.documentoDoResponsavel), stdin);
    empresa.documentoDoResponsavel[strcspn(empresa.documentoDoResponsavel, "\n")] = 0;
    printf("\n");

    printf("- Qual a raz�o social da empresa? ");
    fgets(empresa.razaoSocial, sizeof(empresa.razaoSocial), stdin);
    empresa.razaoSocial[strcspn(empresa.razaoSocial, "\n")] = 0;
    printf("\n");

    printf("- Qual o nome fantasia da empresa? ");
    fgets(empresa.nomeFantasia, sizeof(empresa.nomeFantasia), stdin);
    empresa.nomeFantasia[strcspn(empresa.nomeFantasia, "\n")] = 0;
    printf("\n");

    printf("- Qual o CNPJ (apenas n�meros) da empresa? ");
    fgets(empresa.cnpj, sizeof(empresa.cnpj), stdin);
    empresa.cnpj[strcspn(empresa.cnpj, "\n")] = 0;
    printf("\n");
    getchar();

    printf("- Qual o n�mero de telefone da empresa? ");
    fgets(empresa.telefoneDaEmpresa, sizeof(empresa.telefoneDaEmpresa), stdin);
    empresa.telefoneDaEmpresa[strcspn(empresa.telefoneDaEmpresa, "\n")] = 0;
    printf("\n");

    printf("---> Qual o endere�o da empresa?\n");
    printf("SIGA O PADR�O: RUA, N�MERO, BAIRRO, CIDADE, ESTADO e CEP\n");
    printf("\n");
    printf("- Digite aqui: ");
    getchar();
    fgets(empresa.enderecoDaEmpresa, sizeof(empresa.enderecoDaEmpresa), stdin);
    empresa.enderecoDaEmpresa[strcspn(empresa.enderecoDaEmpresa, "\n")] = 0;
    printf("\n");

    printf("- Qual o e-mail da empresa? ");
    fgets(empresa.emailDaEmpresa, sizeof(empresa.emailDaEmpresa), stdin);
    empresa.emailDaEmpresa[strcspn(empresa.emailDaEmpresa, "\n")] = 0;
    printf("\n");

    // Aqui voc� dever� ter a fun��o inserirEmpresa() definida em outra parte do seu c�digo
    inserirEmpresa(empresa);

    printf("------------------------------------------------------\n");
    printf("          IND�STRIA CADASTRADA COM SUCESSO!\n");
    printf("------------------------------------------------------\n");

    printf("\n");
    Sleep(1200); // Pausa o programa por 1200 milissegundos
    // Aqui voc� dever� ter a fun��o renderizaMenuEDireciona() definida em outra parte do seu c�digo
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
