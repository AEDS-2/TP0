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
    sleep(2);
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
}
// .

// recolhe as informacoes do jogador atual sempre que solicitado
void infoJogador(lTrainer lista, int numPlayer, int *x, int *y, int *pbs, char *nome[15]) {
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
void explore(int tam, int* map, int x, int y, int *nx, int *ny, int numPBs, int *action, int *perigo, int firstPos) {
    int limEsqx = x-1, limDirx = x+1, limSupy = y-1, limInfy = y+1, maiorCelula, maiorCP = 0, contEspacosVistos = 0, contEspacos8 = 0, action0 = 0;
    //  define os limites da mini matriz se ela extrapolar os limites da matriz do mapa
    if (limEsqx < 0) limEsqx = 0;
    if (limDirx >= tam) limDirx = tam-1;
    if (limSupy < 0) limSupy = 0;
    if (limInfy >= tam) limInfy = tam-1;
    // .
    // atribui valores iniciais
    int i = limEsqx, j = limSupy;
    *nx = i; *ny = j; *action = 0; *perigo = 0;
    // .
    // caso em que eh a primeira posicao do jogador
    if (firstPos == 1) {
        limEsqx = x;
        limDirx = x;
        limSupy = y;
        limInfy = y;
    }
    //.
    maiorCelula = map[limEsqx + limSupy*tam];
    do {
        for (i = limEsqx; i <= limDirx; i++) { // varre a matriz de x-1 a x+1 (mini matriz das redondezas do player)
            for (j = limSupy; j <= limInfy; j++) { // varre a matriz de y-1 a y+1 (mini matriz das redondezas do player)
                if ((map[i + j*tam] >= maiorCelula) || numPBs == 3) {
                    // caso em que a celula eh a celula em que o jogador atual estao
                    if ((i == x && j == y) && firstPos != 1) {
                        // nao faz nada
                        //printf("**** nao faz nada (%d)\n", *action); //teste
                    }
                    // .
                    // caso em que a matriz foi varrida por completo e a action continua 0
                    else if (action0 && map[i + j*tam] != 8) {
                        *nx = i;
                        *ny = j;
                        *action = 0;
                        action0 = -1;
                    }
                    // .
                    // caso em que o espaco ja foi "pisado"
                    else if (map[i + j*tam] == 8) {
                        contEspacos8++;
                    }
                    // .
                    // caso em que o espaco eh um pokestop
                    else if (map[i + j*tam] == 6) {
                        if (numPBs > 0) {
                        } // caso em que esta num pokestop, mas ja tem pokebolas
                        else {
                            *nx = i;
                            *ny = j;
                            *action = 1; // acao de pegar pokebolas
                        }
                    }
                    // .
                    // caso em que eh encontrado um pokemon
                    else if (map[i + j*tam] > 0 && map[i + j*tam] < 6) { // eh um pokemon
                        if (numPBs == 0) { } // caso em que encontra um pokemon mas nao tem pokebolas
                        else if (map[i + j*tam] > maiorCP) {
                            *nx = i;
                            *ny = j;
                            *action = 2; // acao de captura de pokemon
                            maiorCP = map[i + j*tam];
                        }
                    }
                    // .
                    // caso em que eh uma celula "livre"
                    else if (map[i + j*tam] == 0) {
                        *nx = i;
                        *ny = j;
                        *action = 3; // acao "sem acao"
                    }
                    // .
                    // caso em que a celula eh um "perigo"
                    else if (map[i + j*tam] < 0) {
                        *nx = i;
                        *ny = j;
                        *action = 4; // acao de tomar dano/diminuir score
                        *perigo = map[i + j*tam];
                    }
                    // .
                }
                contEspacosVistos++; // conta quantos espacos foram varridos na matriz
            }
        }
        // confere se action permaneceu 0 mesmo apos varrer toda matriz
        if (*action == 0 && action0 != -1) {
            // caso em que todos os espacos sao 8 (ja pisados) : fim de partida
            if (contEspacos8 == (contEspacosVistos-1)) {
                *action = -1;
            }
            // .
            // caso em que todos os espacos foram vistos mas nao houve acao (nao pode pegar pokemon nem pokebolas)
            else {
                action0 = 1;
            }
        }
    } while (action0 == 1);
}
// .

void walk(int tam, int* map, int *x, int *y, int nx, int ny, int action, int *numPBs, int *atualPlay) {
    switch (action) {
        case -1: // fim da partida do jogador atual
            *atualPlay = 0;
            break;
        case 0: // so de passagem (nao realiza acao da celula)
            printf(">> Passando por celula sem acao: [%d, %d]\n", nx, ny);
            break;
        case 1: // pega pokebolas
            map[*x + (*y * tam)] = 8;
            *numPBs+=1;
            printf(">> Pokestop: +1 pokebola! [%d, %d]\n", nx, ny);
            break;
        case 2: // pega pokemon
            map[*x + (*y * tam)] = 8;
            *numPBs-=1;
            printf(">> Pokemon capturado! [%d, %d]\n", nx, ny);
            break;
        case 3: // celula livre
            map[*x + (*y * tam)] = 8;
            printf(">> Celula 0: celula livre, passagem sem danos ou ganhos! [%d, %d]\n", nx, ny);
            break;
        case 4: // perigo
            map[*x + (*y * tam)] = 8;
            printf(">> Perigo! [%d, %d]\n", nx, ny);
            break;
    }
    // TODO: acrescenta nova posicao na lista de posicoes passadas
    *x = nx;
    *y = ny;
}
void walkedPath();
