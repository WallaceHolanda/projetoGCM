#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>
#include "restaurante.h"
#include "cardapio.h"

int main(){
    setlocale(LC_ALL,"Portuguese");

    char nomeDoRestaurante[50] = "AGUA NA BOCA";

	Lista* cardapio = criaLista();
	cardapio = carregaItensDoCardapio();

    menuItensDoCardapio(cardapio, nomeDoRestaurante);

	return 0;
}
