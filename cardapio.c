#include "cardapio.h"
#include "restaurante.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

typedef struct ItemDoCardapio{
    char nomeRestaurante[100];
    char nomeItem[50];
    char descricao[150];
    char preco[20];
} ItemDoCardapio;

void flush_in(){
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}


void cadastrarItemdoCardapio(char* nomeDoRestaurante){

	system("cls");
	printf("\n\n\tCADASTRO DE ITEM NO CARDÁPIO\n\t\n\n");
	printf("\n Informe os dados do Item.\n\n");
	//fflush(stdin);

	FILE* arquivoCardapio;

	if ((verificaNomeExistente(nomeDoRestaurante))!=0){
		ItemDoCardapio meuItem;
		arquivoCardapio = fopen("cardapio.txt","ab+");

		strcpy(meuItem.nomeRestaurante, nomeDoRestaurante);

		printf("- Nome do Item: ");
		scanf("%[^\n]s", meuItem.nomeItem);
        flush_in();

		printf("- Descrição: ");
		scanf("%[^\n]s", meuItem.descricao);
        flush_in();

		printf("- Preço: ");
		scanf("%[^\n]s", meuItem.preco);
        flush_in();

		if (fwrite(&meuItem, sizeof(ItemDoCardapio), 1, arquivoCardapio) !=1){
			printf("\n Não foi possivel cadastrar!\n");
		}else{
			printf("\n Item cadastrado com sucesso!\n ");
			fclose(arquivoCardapio);
		}
	}
	else{
		printf("\n Restaurante já cadastrado!\n ");
	}
	fclose(arquivoCardapio);
	getchar();
	system("cls");
}

void listarCardapio(char* nomeDoRestaurante){
	system("cls");
	ItemDoCardapio itemAuxiliar;
	int cont = 0;

	FILE* arquivoCardapio;
	arquivoCardapio = fopen("cardapio.txt","rb");

	if(arquivoCardapio != NULL){
		printf("\n\n\t\n\t\t\tLISTAGEM DE ITENS\n\t\n\n");

		rewind(arquivoCardapio);

		while(!feof(arquivoCardapio)){
			fread(&itemAuxiliar, sizeof(ItemDoCardapio), 1, arquivoCardapio);

			int isItemDoRestaurante = strcmp(nomeDoRestaurante, itemAuxiliar.nomeRestaurante) == 0 ? 1 : 0;
			if(!feof(arquivoCardapio) && isItemDoRestaurante){

				cont++;
				printf("======================================\n");
				printf("Item %d - %s \n", cont, itemAuxiliar.nomeItem);
				printf("Descrição: %s \n", itemAuxiliar.descricao);
				printf("Preço: %s \n", itemAuxiliar.preco);
			}
		}
	}else{
		printf(" Erro ao tentar abrir arquivo\n");
	}

	if (cont == 0){
		printf("\n\t  Não há itens no cardápio para listar...\n");
	}
	fclose(arquivoCardapio);
	getchar();
	system("cls");
}

//void listarCardapio();
//void alterarItemDoCardapio();
//void excluirItemDoCardapio();
