#include "cardapio.h"
#include "restaurante.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

#define ITEM_NAO_ENCONTRADO 0
#define ITEM_ENCONTRADO 1

typedef struct ItemDoCardapio{
    char nomeRestaurante[100];
    char nomeItem[50];
    char descricao[150];
    char preco[20];
} ItemDoCardapio;

struct listano{
    ItemDoCardapio itemCardapio;
    ListaNo* prox;
};

struct lista{
    ListaNo* prim;
};

void flush_in(){
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

Lista* criaLista(){
    Lista* aux = (Lista*) malloc(sizeof(Lista));
    aux->prim = NULL;
    return aux;
}

void insereLista(Lista* l, ItemDoCardapio novoItem){
    ListaNo* novoNo = (ListaNo*) malloc(sizeof(ListaNo));
    novoNo->itemCardapio = novoItem;
    novoNo->prox = l->prim;
    l->prim = novoNo;
}

Lista* carregaItensDoCardapio(){
    ItemDoCardapio novoItem;
    FILE* arquivoCardapio;
    arquivoCardapio = fopen("cardapio.txt","ab+");

    Lista* listaDeItens = criaLista();

    if(arquivoCardapio == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }

    while(!feof(arquivoCardapio)){
        fread(&novoItem, sizeof(ItemDoCardapio), 1, arquivoCardapio);

        //int isItemDoRestaurante = strcmp(nomeDoRestaurante, novoItem.nomeRestaurante) == 0 ? 1 : 0;
        if(!feof(arquivoCardapio))
            insereLista(listaDeItens, novoItem);
    }
    fclose(arquivoCardapio);
    return listaDeItens;
}

int verificaItemPeloRestaurante(Lista* l, char* nomeDoItem, char* nomeDoRestaurante){
    ListaNo* auxiliar;
    for(auxiliar = l->prim; auxiliar != NULL; auxiliar = auxiliar->prox){
        int restauranteExiste = strcmp(auxiliar->itemCardapio.nomeRestaurante, nomeDoRestaurante) == 0 ? 1 : 0;
        int itemExiste = strcmp(auxiliar->itemCardapio.nomeItem, nomeDoItem) == 0 ? 1 : 0;
        if(restauranteExiste && itemExiste)
            return ITEM_ENCONTRADO;
    }
    return ITEM_NAO_ENCONTRADO;
}

Lista* substituirItem(Lista* l, char* nomeDoItem, char* nomeDoRestaurante, ItemDoCardapio novoItem){
    ListaNo* auxiliar;

    for(auxiliar = l->prim; auxiliar != NULL; auxiliar = auxiliar->prox){
        int restauranteExiste = strcmp(auxiliar->itemCardapio.nomeRestaurante, nomeDoRestaurante) == 0 ? 1 : 0;
        int itemExiste = strcmp(auxiliar->itemCardapio.nomeItem, nomeDoItem) == 0 ? 1 : 0;

        if(restauranteExiste && itemExiste){
            auxiliar->itemCardapio = novoItem;
            return l;
        }
    }
    return NULL;
}

void salvarListaNoArquivo(Lista* l){
    FILE* arquivoCardapio;
    arquivoCardapio = fopen("cardapio.txt","wb");

    if(arquivoCardapio == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }

    ListaNo* aux;
    for(aux = l->prim; aux != NULL; aux = aux->prox)
        fwrite(&(aux->itemCardapio), sizeof(ItemDoCardapio), 1, arquivoCardapio);

    fclose(arquivoCardapio);
}

int excluirItemDaLista(Lista* l, char* nomeDoItemExcluido){
    ListaNo* ant = NULL;
    ListaNo* prox = l->prim;
    if(prox == NULL){
        printf("Nao há itens cadastrados!\n");
    } else {
        while( prox != NULL && strcmp(prox->itemCardapio.nomeItem, nomeDoItemExcluido) != 0){
            ant = prox;
            prox = prox->prox;
        }
        if(prox == NULL){
            printf("Item não encontrado!\n");
            return ITEM_NAO_ENCONTRADO;
        }else{
            if(ant == NULL){
                printf("Item removido com sucesso!\n");
                l->prim = prox->prox;
            }else{
                printf("Item removido com sucesso!\n");
                ant->prox = prox->prox;
            }
            free(prox);
        }
    }
    return ITEM_ENCONTRADO;
}

int isListaVazia(Lista* l){
    if(l->prim == NULL)
        return 1;
    else
        return 0;
}

Lista* cadastrarItemdoCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante){
    char nomeDoItemCadastrado[50];
    //Lista* cardapioDeItens = carregaItensDoCardapio(nomeDoRestaurante);

	system("cls");
	printf("\n\n\tCADASTRO DE ITEM NO CARDÁPIO\n\t\n\n");
	printf("\n Informe os dados do Item.\n\n");

	printf("- Nome do Item: ");
    scanf("%[^\n]s", nomeDoItemCadastrado);
    flush_in();

    int itemNaoExiste = verificaItemPeloRestaurante(cardapioDeItens, nomeDoItemCadastrado, nomeDoRestaurante) == ITEM_NAO_ENCONTRADO;
    int restauranteExiste = verificaNomeExistente(nomeDoRestaurante);

	if (restauranteExiste && itemNaoExiste){
		ItemDoCardapio meuItem;

		strcpy(meuItem.nomeRestaurante, nomeDoRestaurante);
		strcpy(meuItem.nomeItem, nomeDoItemCadastrado);

		printf("- Descrição: ");
		scanf("%[^\n]s", meuItem.descricao);
        flush_in();

		printf("- Preço: ");
		scanf("%[^\n]s", meuItem.preco);
        flush_in();

        insereLista(cardapioDeItens, meuItem);
        salvarListaNoArquivo(cardapioDeItens);
	} else{
		printf("\n Item já cadastrado!\n ");
	}
	getchar();
	system("cls");
	return cardapioDeItens;
}

void listarCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante){
    //Lista* cardapioDeItens = carregaItensDoCardapio(nomeDoRestaurante);
    ListaNo* auxiliar;
    int cont = 1;

    system("cls");
    for(auxiliar = cardapioDeItens->prim; auxiliar != NULL; auxiliar = auxiliar->prox){
        if(strcmp(auxiliar->itemCardapio.nomeRestaurante, nomeDoRestaurante) == 0){
           printf("\n=======================================================\n");
            printf("Item %d - %s \n", cont, auxiliar->itemCardapio.nomeItem);
            printf("Descrição: %s \n", auxiliar->itemCardapio.descricao);
            printf("Preço: %s \n", auxiliar->itemCardapio.preco);
            cont++;
        }
    }
    printf("\n=======================================================\n");
    getchar();
	system("cls");
}

Lista* editarItemDoCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante){
    ItemDoCardapio itemEditado;
    char nomeDoItemEditado[50];

	system("cls");
	printf("\n\n\tEDITAR ITEM DO CARDÁPIO\n\t\n\n");
	printf("- Nome do Item: ");
    scanf("%[^\n]s", nomeDoItemEditado);
    flush_in();

    if(verificaItemPeloRestaurante(cardapioDeItens, nomeDoItemEditado, nomeDoRestaurante) == ITEM_ENCONTRADO){

        printf("\n\n\tEDITAR ITEM DO CARDÁPIO\n\t\n\n");
        printf("\n\n\tINFORME OS NOVOS DADOS DO ITEM \n\t\n\n");

        strcpy(itemEditado.nomeRestaurante, nomeDoRestaurante);

        printf("- Nome do Item: ");
        scanf("%[^\n]s", itemEditado.nomeItem);
        flush_in();

        printf("- Descrição: ");
		scanf("%[^\n]s", itemEditado.descricao);
        flush_in();

		printf("- Preço: ");
		scanf("%[^\n]s", itemEditado.preco);
        flush_in();

        Lista* listaAuxiliar = criaLista();
        listaAuxiliar = substituirItem(cardapioDeItens, nomeDoItemEditado, nomeDoRestaurante, itemEditado);


        if(isListaVazia(listaAuxiliar) == 0){
            salvarListaNoArquivo(listaAuxiliar);
            return listaAuxiliar;
        }

    } else {
        printf("Item não encontrado!");
    }

    getchar();
	system("cls");
	return cardapioDeItens;
}

Lista* excluirItemDoCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante){
    char nomeDoItemExcluido[50];
    //Lista* cardapioDeItens = carregaItensDoCardapio(nomeDoRestaurante);

	system("cls");
	printf("\n\n\tREMOVER ITEM DO CARDÁPIO\n\t\n\n");

	printf("- Nome do Item: ");
    scanf("%[^\n]s", nomeDoItemExcluido);
    flush_in();

    if(excluirItemDaLista(cardapioDeItens, nomeDoItemExcluido) == ITEM_ENCONTRADO)
        salvarListaNoArquivo(cardapioDeItens);
    getchar();
	system("cls");
	return cardapioDeItens;
}


//void alterarItemDoCardapio();


