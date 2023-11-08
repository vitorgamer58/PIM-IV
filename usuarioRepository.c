#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "userRepository.h"

Usuario buscarUsuario(const char *nomeDeUsuario)
{
    Usuario usuario;
    usuario.isValid = false;
    FILE *Ponteiro = abrirOuCriarArquivo("usuarios.txt");

    if(Ponteiro == NULL)
    {
        return usuario;
    }

    while(fscanf(Ponteiro, "%49[^,],%49[^\n]\n", &usuario.nomeDeUsuario, usuario.senha) != EOF)
    {
        if(strcmp(nomeDeUsuario, usuario.nomeDeUsuario) == 0)
        {
            usuario.isValid = true;
            fclose(Ponteiro);
            return usuario;
        }
    }

    fclose(Ponteiro);
    return usuario;
}

bool inserirUsuario(const char* nomeDeUsuario, const char* senha)
{
    FILE *ArquivoUsuarios=abrirArquivoParaGravacao("usuarios.txt");

    if(ArquivoUsuarios==NULL)
    {
        return false;
    }

    char usuarioSenha[101];

    strcpy(usuarioSenha, nomeDeUsuario);
    strcat(usuarioSenha, ",");
    strcat(usuarioSenha, senha);

    fprintf(ArquivoUsuarios, "%s\n", usuarioSenha);

    fclose(ArquivoUsuarios);

    return true;
}

