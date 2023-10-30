#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    while(escolha != 5);
}

bool checarUsuario(const char* usuario, const char* senha)
{
    if (strcmp(usuario, "teste") == 0 && strcmp(senha, "teste") == 0)
    {
        return true;
    }

    return false;
}

void logar(char* usuario, char* senha)
{
    printf("Digite seu usuario:");
    scanf("%s", usuario);

    printf("Digite sua senha:");
    scanf("%s", senha);

    if(checarUsuario(usuario, senha))
    {
        printf("Logado com sucesso!!");
        renderizaMenuEDireciona();
    }
    else
    {
        printf("Senha invalida!\n");
        memset(usuario, 0, sizeof(usuario));
        memset(senha, 0, sizeof(senha));
        logar(usuario, senha);
    }
}

int main()
{
    char usuario[50], senha[50];

    printf("Bem vindo ao sistema\n");

    logar(usuario, senha);

    return 0;
}
