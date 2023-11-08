#include <stdio.h>
#include <string.h>
#include <locale.h>

void verificadorTelefone()
 {
    setlocale(LC_ALL, "Portuguese");
    char telefone[16]; // Buffer para armazenar o número de telefone (incluindo hífens)

    printf("---> Qual o número do celular do responsável pela empresa?\n");
    printf("Responda no formato XX-XX-9XXXXXXXX\n");
    printf("Os quatro primeiros dígitos referenciam o código do país e DDD.\n");
    printf("Digite aqui: ");
    scanf("%15s", telefone); // Ler até 15 caracteres (13 dígitos + 2 hífens)

    // Verificar se a entrada tem o tamanho correto e possui um hífen na posição correta
    if (strlen(telefone) == 15 && telefone[2] == '-' && telefone[5] == '-' && telefone[6] == '9') {
        printf("Número de telefone válido: %s\n", telefone);
        // Agora você pode prosseguir com o armazenamento ou processamento do número de telefone.
    }
	else {
        printf("\nNúmero de telefone inválido. Deve estar no formato XX-XX-9XXXXXXXX.\n");
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
    char cpf[15]; // Buffer para armazenar o cpf (incluindo pontos e hífen)

    printf("---> Qual o CPF do responsável pela empresa?\n");
    printf("Preencha com pontos e hífen. Deve estar no formato XXX.XXX.XXX-XX\n");
    printf("Digite aqui: ");
    scanf("%14s", cpf); // Ler até 14 caracteres (11 números + 2 pontos + 1 hífen)

    // Verificar se a entrada tem o tamanho correto e possui pontos e hífens nas posições corretas
    if (strlen(cpf) == 14 && cpf[3] == '.' && cpf[7] == '.' && cpf[11] == '-') {
        printf("Número de CPF válido: %s\n", cpf);
        // Agora você pode prosseguir com o armazenamento ou processamento do número de telefone.
    }
	else {
        printf("\nNúmero de CPF inválido. Deve estar no formato XXX.XXX.XXX-XX.\n");
        printf("Tente novamente.\n");
        printf("\n");
        system("pause");
        verificadorCPF();
    }

    return;
}

