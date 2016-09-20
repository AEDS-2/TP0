#include <stdio.h>
#include <stdlib.h>
#include "Biblioteca.h"

/* ---- Funcoes de Listas */
//
void criaLista(lTrainer *lista) {
 lista->primeiro = (tCelula *)malloc(sizeof(tCelula));
 lista->ultimo = lista->primeiro;
 lista->primeiro->prox = NULL;
}
//.

void explore();
void walk();
void walkedPath();
