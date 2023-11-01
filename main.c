#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "userRepository.h"

void cadastrarUsuario()
{
    char nomeDeUsuario[50], senha[50];

    system("cls");
    printf("------------------------------------------------\n");
    printf("          CADASTRO DE NOVOS USUARIOS\n");
    printf("------------------------------------------------\n");
    printf("\n");
    printf("Digite o nome do novo usuario: ");
    scanf("%s", nomeDeUsuario);
    printf("Agora digite a senha: ");
    scanf("%s", senha);
    printf("\n");
    printf("----- NOVO USUARIO CADASTRADO COM SUCESSO! -----\n");
    printf("\n");
    system ("pause");


}
void renderizaMenuEDireciona()
{
    int escolha;

    do
    {
        system("cls");
        printf("------------------------------------------------\n");
        printf("                MENU PRINCIPAL:\n");
        printf("------------------------------------------------\n");
        printf("\n");
        printf("1. Cadastrar novo usuario\n");
        printf("2. Cadastrar industria\n");
        printf("3. Exibir dados da industria\n");
        printf("4. Exibir relatorios\n");
        printf("5. Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch(escolha)
        {
        case 1:
            cadastrarUsuario();
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            return;
        default:
            printf("Opcao invalida! Tente novamente.\n");
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

    printf("Digite seu usuario: ");
    scanf("%s", nomeDeUsuario);

    printf("Digite sua senha: ");
    scanf("%s", senha);

    usuario = buscarUsuario(nomeDeUsuario);

    if(!usuario.isValid)
    {
        printf("Usuario nao encontrado\n");
        return;
    }

    if(checarSenha(usuario.senha, senha))
    {
        printf("Logado com sucesso!!");
        renderizaMenuEDireciona();
    }

    else
    {
        printf("Senha invalida!\n");
        memset(nomeDeUsuario, 0, sizeof(nomeDeUsuario));
        memset(senha, 0, sizeof(senha));
        logar(nomeDeUsuario, senha);
    }
}

int main()
{
    char nomeDeUsuario[50], senha[50];

    printf("------------------------------------------------\n");
    printf("              BEM-VINDO AO SISTEMA!\n");
    printf("------------------------------------------------\n");
    printf("\n");
    logar(nomeDeUsuario, senha);

    return 0;
}
