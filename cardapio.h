#ifndef CARDAPIO_H_INCLUDED
#define CARDAPIO_H_INCLUDED

typedef struct lista Lista;
typedef struct listano ListaNo;

Lista* criaLista();
Lista* carregaItensDoCardapio();

Lista* cadastrarItemdoCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante);
void listarCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante);
Lista* excluirItemDoCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante);
Lista* editarItemDoCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante);

void menuItensDoCardapio(Lista* cardapioDeItens, char* nomeDoRestaurante);

void apresentaMenu();
void flush_in();

#endif // CARDAPIO_H_INCLUDED
