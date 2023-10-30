#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "userRepository.h"

void renderizaMenuEDireciona()
{
    int escolha;

    do
    {
        printf("Menu:\n");
        printf("1. Cadastrar novo usuario\n");
        printf("2. Cadastrar industria\n");
        printf("3. Exibir dados da industria\n");
        printf("4. Exibir relatorios\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch(escolha)
        {
        case 1:
            break;
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

    printf("Digite seu usuario:");
    scanf("%s", nomeDeUsuario);

    printf("Digite sua senha:");
    scanf("%s", senha);

    usuario = buscarUsuario(nomeDeUsuario);

    if(!usuario.isValid) {
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

    printf("Bem vindo ao sistema\n");

    logar(nomeDeUsuario, senha);

    return 0;
}
