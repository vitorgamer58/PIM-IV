#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool checarUsuario(const char* usuario, const char* senha) {
    if (strcmp(usuario, "teste") == 0 && strcmp(senha, "teste") == 0) {
        return true;
    }

    return false;
}

void logar(char* usuario, char* senha) {
    printf("Digite seu usuario:");
    scanf("%s", usuario);

    printf("Digite sua senha:");
    scanf("%s", senha);

    if(checarUsuario(usuario, senha)) {
        printf("Logado com sucesso!!");
    } else {
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
