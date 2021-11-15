#include "usuario.h"
#include "restaurante.h"
#include "cardapio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define LOGIN_MAX	10
#define SENHA_MAX	10

struct usuario_t {
	char login[10];
	char senha[10];
};


void cadastrarUser()
{
	FILE *fp;
	struct usuario_t usuario;
	memset(&usuario, 0, sizeof(struct usuario_t));

	printf("Cadastro de Usuários\n");
	printf("Login: ");
	scanf("%s", usuario.login);
	printf("Senha: ");
	scanf("%s", usuario.senha);

	fp = fopen("login", "wb");
	if (!fp) {
		printf("Erro ao criar o arquivo!");
		return;
	}else {
	    printf("Usuário cadastrado com sucesso!");
	    fwrite(&usuario, sizeof(struct usuario_t), 1, fp);
        fclose(fp);
        Sleep(2000);
	}

}

int login()
{
    FILE *fp;
	struct usuario_t usuario;
	fp = fopen("login", "rb");
	if (!fp) {
        printf("Nenhum usuário encontrado, abrindo cadastro!\n");
		Sleep(2000);
		cadastrarUser();
		fp = fopen("login", "rb");
		if (!fp) {
		    printf("Erro! Arquivo não encontrado\n");
		    return 0;
		}
	}
	memset(&usuario, 0, sizeof(struct usuario_t));

	fread(&usuario, sizeof(struct usuario_t), 1, fp);
	fclose(fp);
	if (!strcmp("", usuario.login)) {
		cadastrarUser();
	} else {
			char login[LOGIN_MAX];
			char senha[SENHA_MAX];
			system("cls");
			printf("\t\t\t\t\tREALIZE LOGIN\n\n");
			printf("Login: ");
			scanf("%s", login);
			printf("Senha: ");
			scanf("%s", senha);
			if (!strcmp(login, usuario.login) && !strcmp(senha, usuario.senha)) {
				printf("\t\t\t\t\tBem vindo %s\n", usuario.login);
				Sleep(2000);
				menuSecundario();
			} else {
				printf("Usuário ou senha invalidos!\n");
			}
	}
	return 0;
}
void menuLogin(){
	int op;
	do{
		system("cls");
		printf("\t\t\t\t\t\tSEJAM BEM VINDOS\n\n\t\t\t\t\t\t[1] CADASTRAR\n\t\t\t\t\t\t[2] LOGIN \n\t\t\t\t\t\t[0] SAIR\n\n\t\t\t\t\t\tOPÇÃO: ");

		scanf("%d",&op);
		switch(op){
			case 1:
				cadastrarUser();
				break;
			case 2:
				login();
				break;

			case 0:
				exit(0);
				break;

		}
		if ((op < 0) || (op > 2)){
	        printf("\n\n\t\t\t\t\t\tOpção Inválida!\n ");
	        getch();
		}
	}while(op !=0);
	system("cls");
	getch();
}

void menuSecundario(){


    int op;
    char nomeRest[100];
	do{
		system("cls");
		printf("\t\t\t\t\t\tSEJAM BEM VINDOS\n\n\t\t\t\t\t\t[1] MENU DE RESTAURANTES\n\t\t\t\t\t\t[2] MENU DE CARDÁPIOS \n\t\t\t\t\t\t[0] SAIR\n\n\t\t\t\t\t\tOPÇÃO: ");

		scanf("%d",&op);
		switch(op){
			case 1:
				menuCrud();
				break;
			case 2:

			    printf("Insira o nome do restaurante: ");
			    flush_in();
			    scanf("%[^\n]s", nomeRest);
			    if (verificaNomeExistente(strupr(nomeRest))==1){
                    Lista* cardapio = criaLista();
                    cardapio = carregaItensDoCardapio();
                    menuItensDoCardapio(cardapio, nomeRest);

			    }else {

                    printf("Nome de Restaurante não encontrado! Por favor insira outro nome.");
                    Sleep(2000);

			    }

				break;

			case 0:
				exit(0);
				break;

		}
		if ((op < 0) || (op > 2)){
	        printf("\n\n\t\t\t\t\t\tOpção Inválida!\n ");
	        getchar();
		}
	}while(op !=0);
	system("cls");
	getch();
}

