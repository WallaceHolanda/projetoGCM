#include "restaurante.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

typedef struct Restaurante{
	char nome[100];
	char rua[100];
	char bairro[100];
	char cidade[100];
	char numero[10];
	char cep[100];
	char horaAbertura[10];
	char horaFechamento[10];
	char tipoCulinaria[100];
}Restaurante;

FILE *pRestaurante;

void cadastrar(){
	char nome[100];
	int op;

	system("cls");
	printf("\n\n\tCADASTRO DE RTESTAURANTES\n\t\n\n");
	printf("\n Informe os dados do Restaurante.\n\n Nome: ");
	fflush(stdin);
	gets(nome);
	if ((verificaNomeExistente(nome))==0){
		Restaurante func;
		pRestaurante = fopen("Restaurantes.txt","ab+");
		strcpy(func.nome,strupr(nome));
		printf("Insira o Endereço\n\n");
		printf("Rua: ");
		scanf("%s", &func.rua);
		printf("Número: ");
		scanf("%s", &func.numero);
		printf("Bairro: ");
		scanf("%s", &func.bairro);
		printf("Cidade: ");
		scanf("%s", &func.cidade);
		printf("Cep: ");
		scanf("%s", &func.cep);
		printf("Horario de Abertura: ");
		scanf("%s", &func.horaAbertura);
		printf("Horario de Fechamento: ");
		scanf("%s", &func.horaFechamento);
		printf("Tipo de Culinária: ");
		scanf("%s", &func.tipoCulinaria);

		if (fwrite(&func,sizeof(Restaurante),1,pRestaurante) !=1){
			printf("\n Não foi possivel realizar ocadastrar!\n");
		}else{
			printf("\n Novo Restaurante cadastrado com sucesso!\n ");
			fclose(pRestaurante);
		}
	}
	else{
		printf("\n Restaurante já cadastrado!\n ");
	}
	fclose(pRestaurante);
	getch();
	system("cls");
}

void listar(){
	system("cls");
	Restaurante auxfunc;
	int cont = 0;
	pRestaurante = fopen("Restaurantes.txt","rb");
	if(pRestaurante!=NULL){
		printf("\n\n\t\n\t\t\tLISTAGEM DE RESTAURANTES\n\t\n\n");

		rewind(pRestaurante);
		while(!feof(pRestaurante)){
			fread(&auxfunc,sizeof(Restaurante),1,pRestaurante);
			if(!feof(pRestaurante)){
				cont++;
				printf(" [%i]\n Nome: %s\n Rua: %s\n Numero: %s\n Bairro: %s\n Cidade: %s\n Cep: %s\n Abertura: %s\n Fechamento: %s\n Culinaria: %s\n\n",cont,auxfunc.nome,auxfunc.rua,auxfunc.numero,auxfunc.bairro,auxfunc.cidade,auxfunc.cep,auxfunc.horaAbertura,auxfunc.horaFechamento,auxfunc.tipoCulinaria);
			}
		}
	}else{
		printf(" Erro ao tentar abrir arquivo\n");
	}

	if (cont == 0){
		printf("\n\t  Não há restaurantes cadastrados para listar...\n");
	}
	fclose(pRestaurante);
	getch();
	system("cls");
}


void alterar(){

	Restaurante auxfunc, funcAlterado;
	int cont=-1;
	char nomePesquisa[100];
	system("cls");

	printf("\n\n\t\n\t\t\tALTERAR RESTAURANTE\n\t\n\n");
	printf("\n Dados da Pesquisa...\n Informe o NOME do Restaurante que deseja alterar:\n ");
	fflush(stdin);
	gets(nomePesquisa);
	if(verificaNomeExistente(strupr(nomePesquisa)) == 1){
		pRestaurante = fopen("Restaurantes.txt","rb+");
		rewind(pRestaurante);
		while(!feof(pRestaurante)){
			fread(&auxfunc,sizeof(Restaurante),1,pRestaurante);
			if(!feof(pRestaurante)){
				cont++;
				if(strcmp(nomePesquisa,auxfunc.nome)==0){
					printf("\n Dados do Restaurantes localizado:\n");
					printf("Nome: %s\n Rua: %s\n Numero: %s\n Bairro: %s\n Cidade: %s\n Cep: %s\n Abertura: %s\n Fechamento: %s\n Culinaria: %s\n\n",auxfunc.nome,auxfunc.rua,auxfunc.numero,auxfunc.bairro,auxfunc.cidade,auxfunc.cep,auxfunc.horaAbertura,auxfunc.horaFechamento,auxfunc.tipoCulinaria);
					printf("\n Informe os dados para alteracao do Restaurante.\n");
					printf(" Nome: ");
					fflush(stdin);
					gets(nomePesquisa);
					fclose(pRestaurante);
					if((verificaNomeExistente(strupr(nomePesquisa))== 0) || ((verificaNomeExistente(strupr(nomePesquisa)) == 1) && (strcmp(auxfunc.nome,strupr(nomePesquisa)) == 0))){
						pRestaurante = fopen("Restaurantes.txt","rb+");
						strcpy(funcAlterado.nome,strupr(strupr(nomePesquisa)));
						printf("Insira o Endereço\n\n");
                        printf("Rua: ");
                        scanf("%s", &funcAlterado.rua);
                        printf("Número: ");
                        scanf("%s", &funcAlterado.numero);
                        printf("Bairro: ");
                        scanf("%s", &funcAlterado.bairro);
                        printf("Cidade: ");
                        scanf("%s", &funcAlterado.cidade);
                        printf("Cep: ");
                        scanf("%s", &funcAlterado.cep);
                        printf("Horario de Abertura: ");
                        scanf("%s", &funcAlterado.horaAbertura);
                        printf("Horario de Fechamento: ");
                        scanf("%s", &funcAlterado.horaFechamento);
                        printf("Tipo de Culinária: ");
                        scanf("%s", &funcAlterado.tipoCulinaria);
						fseek(pRestaurante,cont*sizeof(Restaurante),SEEK_SET);
						fwrite(&funcAlterado,sizeof(Restaurante),1,pRestaurante);
						printf("\n Dados do Rstaurante alterado com sucesso!\n");
						fclose(pRestaurante);
						break;
					}

					if ((verificaNomeExistente(nomePesquisa) == 1) && (strcmp(auxfunc.nome,nomePesquisa) != 0)){
						printf("\n Não foi possivel alterar os dados do Restaurante.\n Você está tentando inserir um nome que já existente.\n ");
						fclose(pRestaurante);
						break;
					}
				}
			}
		}
	}else{
		printf("\n Restaurante não encontrado!\n ");
	}

	fclose(pRestaurante);
	getch();
	system("cls");
}

void excluir(){
	char nomePesquisa[100];
	Restaurante funcExcluir;
	FILE *pExcluir;
	system("cls");
	printf("\n\n\t\n\t\t\tEXCLUIR RESTAURANTE\n\t\n\n");
	printf("\n Dados da Pesquisa...\n Informe o NOME do Restaurante que deseja excluir:\n ");
	fflush(stdin);
	gets(nomePesquisa);
	if(verificaNomeExistente(strupr(nomePesquisa))== 1){
		fclose(pRestaurante);
		pRestaurante = fopen("Restaurantes.txt","rb+");
		pExcluir = fopen("pExcluir.txt","wb+");
		rewind(pRestaurante);
		while(!feof(pRestaurante)){
			fread(&funcExcluir,sizeof(Restaurante),1,pRestaurante);

			if(!feof(pRestaurante)){
				if(strcmp(funcExcluir.nome,strupr(nomePesquisa))==0){
					printf("\n Restaurante Localizado!\n Registro excluido com sucesso!\n ");
				}else{
					fwrite(&funcExcluir,sizeof(Restaurante),1,pExcluir);
				}
			}
		}
		fclose(pRestaurante);
		fclose(pExcluir);
		remove("Restaurantes.txt");
		rename("pExcluir.txt","Restaurantes.txt");
	}else{
		printf("\n Restaurante não localizado!\n ");
	}
	getch();
	system("cls");
}

int verificaNomeExistente(char nome[20]){
	Restaurante aux;

	int verificador = 0; // 1 - Ja existe cadastrado / 0 - Nao cadastrado

	pRestaurante = fopen("Restaurantes.txt","rb");
	if(pRestaurante!=NULL){
		rewind(pRestaurante);
		while(!feof(pRestaurante)){

			fread(&aux,sizeof(Restaurante),1,pRestaurante);
			if(!feof(pRestaurante)){
				if(strcmp(aux.nome,nome)==0){
					verificador = 1;
				}
			}
		}
	}else{
		printf("\n Erro ao abrir arquivo.\n");
	}
	fclose(pRestaurante);
	//getch();

	return verificador;
}

void menuCrud(){
	int op;

	do{
		system("cls");
		printf("\t\t\t\t\tSelecione uma das Opções abaixo...\n\n\t\t\t\t\t\t[1] CADASTRAR\n\t\t\t\t\t\t[2] LISTAR \n\t\t\t\t\t\t[3] ALTERAR \n\t\t\t\t\t\t[4] EXCLUIR\n\t\t\t\t\t\t[0] SAIR\n\n\t\t\t\t\t\tOPÇÃO: ");

		scanf("%d",&op);
		switch(op){
			case 1:
				cadastrar();
				menuCrud();
				break;
			case 2:
				listar();
				menuCrud();
				break;
			case 3:
				alterar();
				menuCrud();
				break;
			case 4:
				excluir();
				menuCrud();
				break;
			case 0:
				exit(0);
				break;

		}
		if ((op < 0) || (op > 4)){
	        printf("\n\n\t\t\t\t\t\tOpção Inválida!\n ");
	        getch();
		}
	}while(op !=0);
	system("cls");
	getch();
}
