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

/* ---- Funcoes de Jogo */
// Imprime nome e informacoes do jogador ao inicio da partida dele
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

// recolhe as informacoes do jogador atual sempre que solicitado
void infoJogador(lTrainer lista, int numPlayer, int *x, int *y, int *pbs) {
    pTrainer p;
    int rep = 0;
    p = lista.primeiro->prox;
    //repeticao para chegar ate o jogador atual
    while (rep < numPlayer) {
        p = p->prox;
        rep++;
    }
    // .
    // descobre as info do jogador atual
    if (p != NULL) {
        *x = p->treinador.x;
        *y = p->treinador.y;
        *pbs = p->treinador.tPokeballs;
    }
    //.
}
//.

// varre a regiao do mapa proxima ao jogador e atribui a melhor posicao para deslocamento futuro
void explore(int tam, int* map, int x, int y, int *nx, int *ny, int numPBs, int *action) {
    int i, j, maior, newX = 0, newY = 0, lxe = x-1, lxd = x+1, lye = y-1, lyd = y+1;
    // confere se as variaveis que delimitam a regiao de exploracao saem da matriz
    if (lxe < 0) lxe = 0;
    if (lxd >= tam) lxd = tam-1;
    if (lye < 0) lxe = 0;
    if (lyd >= tam) lyd = tam-1;
    // .
    // varre a mini matriz que delimita a regiao de exploracao e encontra o maior elemento
    for (i = lxe; i <= lxd; i++) {
        // declaracao de valores iniciais
        if (i == lxe) {
            maior = map[i + j*tam];
            newX = i;
            newY = j;
        }
        // .
        for (j = lye; j <= lyd; j++) {
            if (map[i + j*tam] > maior) {
                if (map[i + j*tam] > 0 && map[i + j*tam] < 6) { // eh um pokemon
                    if (numPBs == 0) {} // tem pokemon e nao tem pokebolas
                    else {
                        maior = map[i + j*tam];
                        newX = i;
                        newY = j;
                        *action = 1;
                    }
                }
                else if (map[i + j*tam] == 6) { // eh um pokestop
                    if (numPBs == 3) {} // tem pokestop mas tem pokebolas
                    else {
                        maior = map[i + j*tam];
                        newX = i;
                        newY = j;
                        *action = 2;
                    }
                }
                else if (map[i + j*tam] == 8) {} // caminho ja passado
                else {
                    maior = map[i + j*tam];
                    newX = i;
                    newY = j;
                    // TODO: diferenciacao de 0 (nada) e < 0 (perigo)
                }
            }
        }
    }
    //.
    *nx = newX;
    *ny = newY;
}
// .

void walk() {
    // mudar posicao
    // acrescentar posicao a lista de posicoes
    // mudar o valor
}
void walkedPath();
