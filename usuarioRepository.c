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


int exibirDadosIndustria() // Esboço da função de exibição de dados
{
    // Nome do arquivo a ser lido.
    char nomeArquivo[] = "usuarios.txt";

    // Abre o arquivo para leitura.
    FILE *arquivo = fopen(nomeArquivo, "r");

    // Verifica se o arquivo foi aberto com sucesso.
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê e exibe os dados do arquivo linha por linha.
    char linha[100]; // Uma linha pode ter até 100 caracteres, ajuste conforme suas necessidades.

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        printf("%s", linha);
    }

        system("pause");
    // Fecha o arquivo.
    fclose(arquivo);

    return 0;
}

