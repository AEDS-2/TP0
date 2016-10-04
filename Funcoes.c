#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

// cria nova lista de posicoes
void criaListaPosicoes(lPos *lista){
    lista->primeiro = (celPos *)malloc(sizeof(celPos));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}
//.
// insere nova posicao a lista de posicoes
void inserePosicao(tPos x, lPos *lista) {
 lista->ultimo->prox  = (celPos *)malloc(sizeof(celPos));
 lista->ultimo = lista->ultimo->prox;
 lista->ultimo->posicao = x;
 lista->ultimo->prox = NULL;
}
//.

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
    sleep(5);
    system("clear");
}
// .

// desenha mapa na tela
void desenhaMapa (int tam, int *map, int xPlayer, int yPlayer) {
    int dLoop = 0, i, j, m = 0, n = 0;
    for(dLoop = 0; dLoop <= tam; dLoop++) { // loop que controla o numero de vezes que as linhas "+===+" e "| elemento |" ser?o desenhadas
        printf("\n+"); // primeiro simbolo da linha de "+===+"
        i = 0; // zera i para novo loop
        n = 0; // come?a nova numera??o de colunas na exibicao dos numeros no mapa
        while (i < tam) { // desenha a quantidade de necessaria de "+===+" em cada linha (se tam = 3, desenha 3 vezes, uma linha s?)
            printf("===+");
            i++;
        }
        j = 0; // zera j para novo loop
        if (dLoop < tam) { // confere numero de exibicoes, pois o while acima deve exibir uma vez a mais
            printf("\n|"); // primeiro simobolo da linha de "| elemento |"
            while (j < tam) { //desenha a quantidade de "| elemento |" em cada linha
            if (m == xPlayer && n == yPlayer) //jogador
                printf(" * |");
                else if (map[m + n*tam] < 0) // perigo
                    printf(" X |");
                else if (map[m + n*tam] == 6) // pokestop
                    printf(" P |");
                else if (map[m + n*tam] == 8) // caminho passado
                    printf(" - |");
                else //pokemons
                    printf(" %d |", map[m + n*tam]);
                n++;
                j++;
            }
        }
        m++; // vai pra proxima linha da matriz do mapa
    }
    printf("\n");
    sleep(2); //TODO: regular esse tempo
    system("clear");
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
    int i, j, maior = map[0 + 0*tam], limEsqx = x-1, limDirx = x+1, limSupy = y-1, limInfy = y+1;
    //  define os limites da mini matriz se ela extrapolar os limites da matriz do mapa
    if (limEsqx < 0) limEsqx = 0;
    if (limDirx > tam-1) limDirx = tam-1;
    if (limSupy < 0) limSupy = 0;
    if (limInfy > tam-1) limInfy = tam-1;
    // .
    for (i = limEsqx; i < limDirx; i++) {
        for (j = limSupy; j < limInfy; j++) {
            if (map[i + j*tam] > maior) {
                maior = map[i + j*tam];
                *nx = i;
                *ny = j;
            }
        }
    }
    /*
    int maior, newX = 0, newY = 0, lxe = x-1, lxd = x+1, lye = y-1, lyd = y+1;
    // confere se as variaveis que delimitam a regiao de exploracao saem da matriz
    if (lxe < 0) lxe = 0;
    if (lxd >= tam) lxd = tam-1;
    if (lye < 0) lye = 0;
    if (lyd >= tam) lyd = tam-1;
    // .
    int i = lxe, j = lye;
    // varre a mini matriz que delimita a regiao de exploracao e encontra o maior elemento
    //TODO: fazer caso em que nao ha mais para onde andar
    for (i = lxe; i <= lxd; i++) {
        printf("em i: posicao atual: [%d, %d] . lxe: %d, lxd: %d\n", i, j, lxe, lxd);
        // declaracao de valores iniciais
        if (i == lxe) {
            maior = map[i + j*tam];
            newX = i;
            newY = j;
        }
        // .
        for (j = lye; j <= lyd; j++) {
            printf("em j: posicao atual: [%d, %d] . lye: %d, lyd: %d\n", i, j, lye, lyd);
            if (map[i + j*tam] > maior) {
                if (map[i + j*tam] > 0 && map[i + j*tam] < 6) { // eh um pokemon
                    printf("map atual: %d\n", map[i + j*tam]);
                    if (numPBs == 0) {} // tem pokemon e nao tem pokebolas
                    else {
                        printf("map if pokemon: %d\n", map[i + j*tam]);
                        maior = map[i + j*tam];
                        newX = i;
                        newY = j;
                        printf("if pokemon: [%d, %d]\n", newX, newY);
                        *action = 1;
                    }
                }
                else if (map[i + j*tam] == 6) { // eh um pokestop
                    if (numPBs == 3) {} // tem pokestop mas tem pokebolas
                    else {
                        printf("map if pokestop: %d\n", map[i + j*tam]);
                        maior = map[i + j*tam];
                        newX = i;
                        newY = j;
                        printf("if pokestop: [%d, %d]\n", newX, newY);
                        *action = 2;
                    }
                }
                else if (map[i + j*tam] == 8) {} // caminho ja passado
                else {
                    printf("map else: %d\n", map[i + j*tam]);
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
    printf("em explore: [%d, %d]\n", newX, newY);
    */
}
// .

void walk(int tam, int* map, int *x, int *y, int nx, int ny, int action) {
    map[*x + (*y * tam)] = 8;
    switch (action) {
        case 1: //pega pokemao
                break;
        case 2: //pokestop
                break;
    }
    // TODO: acrescenta nova posicao na lista
    *x = nx;
    *y = ny;
}
void walkedPath();
