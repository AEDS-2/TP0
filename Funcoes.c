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
// .

// insere novo jogador em uma lista
void insereTrainer(tTrainer x, lTrainer *lista) {
 lista->ultimo->prox  = (tCelula *)malloc(sizeof(tCelula));
 lista->ultimo = lista->ultimo->prox;
 lista->ultimo->treinador = x;
 lista->ultimo->prox = NULL;
}
// .

/* ---- Fun??es de Jogo */
// Imprime nome e informaÃ§Ãµes do jogador ao início da partida dele
void imprimeInicioJogo(lTrainer lista, int numPlayer) {
    pTrainer p;
    int rep = 0;
    p = lista.primeiro->prox;
    // repetição para avançar até o jogador atual
    while (rep < numPlayer) {
        p = p->prox;
        rep++;
    }
    // .
    if (p != NULL) {
        printf("Player %d: %s\nPosicao Inicial: [%d, %d]\nGame Start!\n", p->treinador.chave, p->treinador.name, p->treinador.x, p->treinador.y);
    }
}
// .

void caminhoJogador(lTrainer lista, int numPlayer, int *x, int *y) {
    pTrainer p;
    int rep = 0;
    p = lista.primeiro->prox;
    //repeti??o para chegar at? o jogador atual
    while (rep < numPlayer) {
        p = p->prox;
        rep++;
    }
    // .
    // descobre x e y do jogador atual
    if (p != NULL) {
        *x = p->treinador.x;
        *y = p->treinador.y;
    }
    //.
}

void explore(int tam, int* map, int x, int y, int *nx, int *ny) {
    int i, j, maior = 0, newX = 0, newY = 0, lxe = x-1, lxd = x+1, lye = y-1, lyd = y+1;
    // confere se as vari?veis que delimitam a regi?o de explora??o saem da matriz
    if (lxe < 0) lxe = 0;
    if (lxd >= tam) lxd = tam-1;
    if (lye < 0) lxe = 0;
    if (lyd >= tam) lyd = tam-1;
    // .
    // varre a mini matriz que delimita a regi?o de explora??o e encontra o maior elemento
    for (i = lxe; i <= lxd; i++) {
        for (j = lye; j <= lyd; j++) {
            if (map[i + j*tam] > maior) {
                maior = map[i + j*tam];
                newX = i;
                newY = j;
                //conferir pokebolas pra pokemons e pokestops
            }
        }
    }
    //.
    *nx = newX;
    *ny = newY;
}

void walk() {
    // mudar posicao
    // acrescentar posicao a lista de posicoes
    // mudar o valor
}
void walkedPath();
