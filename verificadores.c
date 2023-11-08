#include <stdio.h>
#include <string.h>
#include <locale.h>

void verificadorTelefone()
 {
    setlocale(LC_ALL, "Portuguese");
    char telefone[16]; // Buffer para armazenar o n�mero de telefone (incluindo h�fens)

    printf("---> Qual o n�mero do celular do respons�vel pela empresa?\n");
    printf("Responda no formato XX-XX-9XXXXXXXX\n");
    printf("Os quatro primeiros d�gitos referenciam o c�digo do pa�s e DDD.\n");
    printf("Digite aqui: ");
    scanf("%15s", telefone); // Ler at� 15 caracteres (13 d�gitos + 2 h�fens)

    // Verificar se a entrada tem o tamanho correto e possui um h�fen na posi��o correta
    if (strlen(telefone) == 15 && telefone[2] == '-' && telefone[5] == '-' && telefone[6] == '9') {
        printf("N�mero de telefone v�lido: %s\n", telefone);
        // Agora voc� pode prosseguir com o armazenamento ou processamento do n�mero de telefone.
    }
	else {
        printf("\nN�mero de telefone inv�lido. Deve estar no formato XX-XX-9XXXXXXXX.\n");
        printf("Tente novamente.\n");
        printf("\n");
        system("pause");
        verificadorTelefone();
    }

    return 0;
}

void verificadorCPF()
 {

    setlocale(LC_ALL, "Portuguese");
    char cpf[15]; // Buffer para armazenar o cpf (incluindo pontos e h�fen)

    printf("---> Qual o CPF do respons�vel pela empresa?\n");
    printf("Preencha com pontos e h�fen. Deve estar no formato XXX.XXX.XXX-XX\n");
    printf("Digite aqui: ");
    scanf("%14s", cpf); // Ler at� 14 caracteres (11 n�meros + 2 pontos + 1 h�fen)

    // Verificar se a entrada tem o tamanho correto e possui pontos e h�fens nas posi��es corretas
    if (strlen(cpf) == 14 && cpf[3] == '.' && cpf[7] == '.' && cpf[11] == '-') {
        printf("N�mero de CPF v�lido: %s\n", cpf);
        // Agora voc� pode prosseguir com o armazenamento ou processamento do n�mero de telefone.
    }
	else {
        printf("\nN�mero de CPF inv�lido. Deve estar no formato XXX.XXX.XXX-XX.\n");
        printf("Tente novamente.\n");
        printf("\n");
        system("pause");
        verificadorCPF();
    }

    return;
}

