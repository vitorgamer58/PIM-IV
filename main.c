#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include "types.h"
#include "userRepository.h"
#include "empresaRepositorio.h"
#include "residuosRepositorio.h"

void relatorioResiduosPorEmpresas()
{
    char cnpj[16];
    ListaDeResiduos *listaDeResiduos;

    printf("Digite o CNPJ (apenas números) da empresa: ");
    getchar();
    fgets(cnpj, sizeof(cnpj), stdin);
    cnpj[strcspn(cnpj, "\n")] = 0; // Remove o caractere de nova linha

    listaDeResiduos = buscarResiduoPorEmpresa(cnpj);

    if(listaDeResiduos->proximo == NULL) {
        printf("UM ELEMENTO!");
    }

    if(listaDeResiduos == NULL)
    {
        printf("\n-------------- Residuos não encontrados para este CNPJ!! --------------\n\n");
        Sleep(2000);
        return;
    }

    while (listaDeResiduos != NULL) {
        printf("CNPJ: %s, Toneladas: %d\n", listaDeResiduos->residuo.cnpj, listaDeResiduos->residuo.toneladas);
        listaDeResiduos = listaDeResiduos->proximo;
    }

    Sleep(2000);
}

void relatorios()
{
    int escolha;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("                      RELATï¿½RIOS\n");
    printf("------------------------------------------------------\n\n");

    printf("Escolha uma das opï¿½ï¿½es abaixo:\n\n");
    printf("[1] relatï¿½rio de resï¿½duos por empresa\n");
    printf("[2] outro tipo de relatï¿½rio\n");
    printf("[3] voltar ao menu principal\n");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        relatorioResiduosPorEmpresas();
    case 2:
        break;
    case 3:
        telaInicial();
        break;
    }
}

void cadastrarResiduos()
{
    Residuo residuo;
    Empresa empresa;
    char cnpj[15];
    int escolha;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("                 CADASTRO DE RESï¿½DUOS\n");
    printf("------------------------------------------------------\n\n");
    printf("Digite o CNPJ (apenas nï¿½meros) da empresa: ");
    getchar();
    fgets(cnpj, sizeof(cnpj), stdin);
    cnpj[strcspn(cnpj, "\n")] = 0; // Remove o caractere de nova linha

    strcpy(residuo.cnpj, cnpj);

    empresa = buscarEmpresa(cnpj);

    if(!empresa.isValid)
    {
        printf("\n-------------- Empresa nï¿½o encontrada!! --------------\n\n");
        printf("Tecle [1] para tentar novamente\n");
        printf("Tecle [2] para voltar ao menu principal\n");
        scanf("%d", &escolha);

        switch(escolha)
        {
        case 1:
            cadastrarResiduos();
            break;
        case 2:
            telaInicial();
            break;
        }
        return;
    }

    printf("Empresa cadastrada: ");
    printf(empresa.nomeFantasia);
    printf("\nDigite a quantidade de resï¿½duos em toneladas (numero inteiro): ");
    scanf("%d", &residuo.toneladas);

    inserirResiduo(residuo);

    printf("\n---------- RESï¿½DUO CADASTRADO COM SUCESSO!! ----------\n\n");
    Sleep(2000);

}

void cadastrarUsuario() // TELA DE CADASTRO DE USUï¿½RIOS
{
    char nomeDeUsuario[50], senha[50];

    system("cls");
    printf("------------------------------------------------------\n");
    printf("              CADASTRO DE NOVOS USUï¿½RIOS\n");
    printf("------------------------------------------------------\n\n");

    printf("Digite o nome do novo usuï¿½rio: ");
    scanf("%s", nomeDeUsuario);
    printf("Agora digite a senha: ");
    scanf("%s", senha);

    bool usuarioFoiCadastrado=inserirUsuario(nomeDeUsuario, senha);

    if (usuarioFoiCadastrado)
    {
        printf("\n-------- NOVO USUï¿½RIO CADASTRADO COM SUCESSO! --------\n");
    }

    Sleep(1500);
    renderizaMenuEDireciona();
}

void cadastrarIndustria() // TELA DE CADASTRO DE INDUSTRIAS
{
    Empresa empresa;

    system("cls");
    printf("------------------------------------------------------\n");
    printf("               CADASTRO DE INDï¿½STRIAS\n");
    printf("------------------------------------------------------\n");
    getchar();

    // FORMULï¿½RIO COM BASE NAS INFORMAï¿½ï¿½ES SUGERIDAS DO PIM

    printf("\n- Qual o nome do responsï¿½vel pela empresa? ");
    fgets(empresa.nomeDoResponsavel, sizeof(empresa.nomeDoResponsavel), stdin);
    empresa.nomeDoResponsavel[strcspn(empresa.nomeDoResponsavel, "\n")] = 0; // Remove o '\n'

    printf("\n- Qual o documento do responsï¿½vel pela empresa? ");
    fgets(empresa.documentoDoResponsavel, sizeof(empresa.documentoDoResponsavel), stdin);
    empresa.documentoDoResponsavel[strcspn(empresa.documentoDoResponsavel, "\n")] = 0;

    printf("\n- Qual a razï¿½o social da empresa? ");
    fgets(empresa.razaoSocial, sizeof(empresa.razaoSocial), stdin);
    empresa.razaoSocial[strcspn(empresa.razaoSocial, "\n")] = 0;

    printf("\n- Qual o nome fantasia da empresa? ");
    fgets(empresa.nomeFantasia, sizeof(empresa.nomeFantasia), stdin);
    empresa.nomeFantasia[strcspn(empresa.nomeFantasia, "\n")] = 0;

    printf("\n- Qual o CNPJ (apenas nï¿½meros) da empresa? ");
    fgets(empresa.cnpj, sizeof(empresa.cnpj), stdin);
    empresa.cnpj[strcspn(empresa.cnpj, "\n")] = 0;

    printf("\n- Qual o nï¿½mero de telefone da empresa? ");
    fgets(empresa.telefoneDaEmpresa, sizeof(empresa.telefoneDaEmpresa), stdin);
    empresa.telefoneDaEmpresa[strcspn(empresa.telefoneDaEmpresa, "\n")] = 0;

    printf("\n- Padrï¿½o para o preenchimento da prï¿½xima pergunta:\n");
    printf("  > RUA, Nï¿½MERO, BAIRRO, CIDADE, ESTADO e CEP <  \n");
    printf("- Qual o endereï¿½o da empresa? ");
    fgets(empresa.enderecoDaEmpresa, sizeof(empresa.enderecoDaEmpresa), stdin);
    empresa.enderecoDaEmpresa[strcspn(empresa.enderecoDaEmpresa, "\n\r")] = 0;

    printf("\n- Qual o e-mail da empresa? ");
    fgets(empresa.emailDaEmpresa, sizeof(empresa.emailDaEmpresa), stdin);
    empresa.emailDaEmpresa[strcspn(empresa.emailDaEmpresa, "\n\r")] = 0;

    // Aqui vocï¿½ deverï¿½ ter a funï¿½ï¿½o inserirEmpresa() definida em outra parte do seu cï¿½digo
    inserirEmpresa(empresa);

    printf("\n------------------------------------------------------\n");
    printf("          INDï¿½STRIA CADASTRADA COM SUCESSO!\n");
    printf("------------------------------------------------------\n");

    Sleep(1500); /* Pausa o programa por 1.5 segundos;
    Aqui vocï¿½ deverï¿½ ter a funï¿½ï¿½o renderizaMenuEDireciona() definida em outra parte do seu cï¿½digo */
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
        printf("------------------------------------------------------\n\n");

        printf("1. Cadastrar novo usuï¿½rio\n");
        printf("2. Cadastrar indï¿½stria\n");
        printf("3. Cadastrar resï¿½duos\n");
        printf("4. Exibir dados da indï¿½stria\n");
        printf("5. Exibir relatï¿½rios\n");
        printf("6. Sair\n");

        printf("\nEscolha uma opï¿½ï¿½o: ");
        scanf("%d", &escolha);

        switch(escolha)
        {
        case 1:
            cadastrarUsuario();
            break;
        case 2:
            cadastrarIndustria();
            break;
        case 3:
            cadastrarResiduos();
            break;
        case 4:
            break;
        case 5:
            relatorios();
            break;
        case 6:
            printf("\n-------------------------------> Saindo do programa...\n");
            printf("Digite qualquer tecla para fechar esta janela <-------\n\n");
            exit(0);
            break;
        default:
            printf("\n---------  Opï¿½ï¿½o invï¿½lida! Tente novamente.  ---------\n\n");
            system("pause");
            break;

        }
    }
    while(escolha != 6);
}

bool checarSenha(const char* senhaDoUsuario, const char* senhaDigitada)
{
    if (strcmp(senhaDoUsuario, senhaDigitada) == 0)
    {
        return true;
    }

    return false;
}

void logar(char* nomeDeUsuario, char* senha) // FUNï¿½ï¿½O E TELAS DE LOGIN
{
    Usuario usuario;

    printf("Digite seu usuï¿½rio: ");
    scanf("%s", nomeDeUsuario);

    printf("Digite sua senha: ");
    scanf("%s", senha);

    usuario = buscarUsuario(nomeDeUsuario);

    if(!usuario.isValid)
    {
        printf("\n-----------  ERRO: usuï¿½rio nï¿½o encontrado  -----------\n\n");
        printf("                   TENTE NOVAMENTE\n\n");

        system("pause");
        system("cls");
        telaInicial();
        logar(nomeDeUsuario, senha);

        return;
    }

    if(checarSenha(usuario.senha, senha))
    {
        printf("\n--------------   LOGADO COM SUCESSO!!   --------------");
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
        printf("Senha invï¿½lida! Tente novamente!\n\n");

        memset(nomeDeUsuario, 0, sizeof(nomeDeUsuario));
        memset(senha, 0, sizeof(senha));
        logar(nomeDeUsuario, senha);
    }
}

int main() // TELA INCIAL E LOGIN
{
    char nomeDeUsuario[50], senha[50];
    telaInicial();
    logar(nomeDeUsuario, senha);

    return 0;
}

void telaInicial()
{
    setlocale(LC_ALL, "Portuguese");
    printf("------------------------------------------------------\n");
    printf("          | STARTUP DE SOLUï¿½ï¿½ES AMBIENTAIS |\n");
    printf("------------------------------------------------------\n");
    printf(" Olï¿½! Efetue login para ter acesso ao nosso sistema.\n\n");
}
