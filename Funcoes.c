#include <stdio.h>
#include <stdlib.h>
#include "Biblioteca.h"

/* ---- Funcoes de Listas */
// cria uma lista de jogadores
void criaListaTrainer(lTrainer *lista) {
 lista->primeiro = (tCelula *)malloc(sizeof(tCelula));
 lista->ultimo = lista->primeiro;
 lista->primeiro->prox = NULL;
}

// insere novo jogador em uma lista
void insereTrainer(tTrainer x, lTrainer *lista) {
 lista->ultimo->prox  = (tCelula *)malloc(sizeof(tCelula));
 lista->ultimo = lista->ultimo->prox;
 lista->ultimo->treinador = x;
 lista->ultimo->prox = NULL;
}
//.

void Imprime(lTrainer lista) {
 pTrainer p;
 p = lista.primeiro->prox;
 while (p != NULL) {
 printf("%d\n", p->treinador.chave);
 p = p->prox;
 }
}

void explore();
void walk();
void walkedPath();
