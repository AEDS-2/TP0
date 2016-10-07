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
    // repeticao para avancar ate o jogador atual
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

// Imprime nome do jogador
void imprimeNome(lTrainer lista, int numPlayer, FILE *saida) {
    pTrainer p;
    int rep = 0;
    p = lista.primeiro->prox;
    // repeticao para avancar ate o jogador atual
    while (rep < numPlayer) {
        p = p->prox;
        rep++;
    }
    // .
    if (p != NULL) {
        fprintf(saida, "\n%s ", p->treinador.name);
    }
}
// .

// grava no arquivo o caminho percorrido pelo jogador
void imprimePassos(lPos lista, FILE *saida) {
    pPos p;
    p = lista.primeiro->prox;
    // repeticao para avancar ate o jogador atual
    while (p != NULL) {
        fprintf(saida, " %d,%d ", p->posicao.x, p->posicao.y);
        p = p->prox;
    }
    // .
}
// .

// desenha mapa na tela
void desenhaMapa (int tam, int *map, int xPlayer, int yPlayer) {
    int dLoop = 0, i, j, m = 0, n = 0;
    for(dLoop = 0; dLoop <= tam; dLoop++) { // loop que controla o numero de vezes que as linhas "+===+" e "| elemento |" serao desenhadas
        printf("\n+"); // primeiro simbolo da linha de "+===+"
        i = 0; // zera i para novo loop
        n = 0; // comeca nova numeracao de colunas na exibicao dos numeros no mapa
        while (i < tam) { // desenha a quantidade de necessaria de "+===+" em cada linha (se tam = 3, desenha 3 vezes, uma linha so)
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
                else if (map[m + n*tam] == 8) // caminho passado
                    printf(" - |");
                else if (map[m + n*tam] == 6) // pokestop
                    printf(" P |");
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
void infoJogador(lTrainer lista, int numPlayer, int *x, int *y, int *pbs, lPos listaPos, int Pokedex[6], int *sumScore) {
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
        listaPos = p->treinador.listaCaminho;
        Pokedex = p->treinador.tPokedex;
        *sumScore = p->treinador.sumScore;
    }
    //.
}
//.

// atualiza as informacoes na lista do jogador
void attJogador(lTrainer lista, int numPlayer, int x, int y, int pbs, lPos listaPos, int Pokedex[6], int sumScore, int contPassos) {
    pTrainer p;
    int rep = 0, i = 0;
    p = lista.primeiro->prox;
    //repeticao para chegar ate o jogador atual
    while (rep < numPlayer) {
        p = p->prox;
        rep++;
    }
    // .
    // descobre as info do jogador atual
    if (p != NULL) {
        p->treinador.x = x;
        p->treinador.y = y;
        p->treinador.tPokeballs = pbs;
        p->treinador.listaCaminho = listaPos;
        p->treinador.sumScore = sumScore;
        p->treinador.contPassos = contPassos;
        for (i = 0; i<6; i++) {
            p->treinador.tPokedex[i] = Pokedex[i];
        }
    }
    //.
}
//.


void declaraVencedor(lTrainer lista, int numPlayer, FILE *saida) {
    pTrainer p;
    p = lista.primeiro->prox;
    int maiorScore = 0, maiorCP = 0, menorPassos = 0, rep = 0;

    // declara que todos sao vencedores (que feliz, nao?)
    for (rep = 0; rep < numPlayer; rep++) {
        p->treinador.contMaior = 1;
        p = p->prox;
        printf("%d eh vencedor\n", rep);
    }
    //.
    p = lista.primeiro->prox;
    // descobre maior Score entre os jogadores e deixa somente como vencedor aquele/s que tenha/m o mesmo score
    for (rep = 0; rep < numPlayer; rep++) {
        if (p->treinador.sumScore > maiorScore) {
            maiorScore = p->treinador.sumScore;
        }
        p = p->prox;
    }
    p = lista.primeiro->prox;
    for (rep = 0; rep < numPlayer; rep++) {
        if (p->treinador.sumScore < maiorScore) {
            p->treinador.contMaior = 0;
            printf("rep score: %d\n", rep);
        }
        p = p->prox;
    }
    p = lista.primeiro->prox;
    //.

    // descobre maior num de pokemons com cp alto entre os jogadores e deixa somente como vencedor aquele/s que tenha/m o mesmo numero
    for (rep = 0; rep < numPlayer; rep++) {
        if (p->treinador.tPokedex[5] > maiorCP && p->treinador.contMaior == 1) {
            maiorCP = p->treinador.sumScore;
        }
        p = p->prox;
    }
    p = lista.primeiro->prox;
    for (rep = 0; rep < numPlayer; rep++) {
        if (p->treinador.tPokedex[5] < maiorCP) {
            p->treinador.contMaior = 0;
            printf("%d nao eh mais vencedor\n", rep);
        }
        p = p->prox;
    }
    p = lista.primeiro->prox;
    //.

    // finalmente, descobre menor num de passos entre os jogadores e deixa somente como vencedor aquele/s que tenha/m o mesmo numero
    for (rep = 0; rep < numPlayer; rep++ && p->treinador.contMaior == 1) {
        if (p->treinador.contPassos < menorPassos) {
            menorPassos = p->treinador.sumScore;
        }
        p = p->prox;
    }
    p = lista.primeiro->prox;
    for (rep = 0; rep < numPlayer; rep++) {
        if (p->treinador.contPassos < menorPassos) {
            p->treinador.contMaior = 0;
            printf("%d nao eh mais vencedor\n", rep);
        }
        p = p->prox;
    }
    p = lista.primeiro->prox;
    //.

    // imprime no arquivo o/s vencedor/es
    fprintf(saida, "\nVENCEDOR ");
    for (rep = 0; rep < numPlayer; rep++) {
        printf("%d\n", rep);
        if (p->treinador.contMaior == 1) {
            printf("vencedor: %s\n", p->treinador.name);
            printf(" %s\n", p->treinador.name);
        }
        p = p->prox;
    }
}

// varre a regiao do mapa proxima ao jogador e atribui a melhor posicao para deslocamento futuro
void explore(int tam, int* map, int x, int y, int *nx, int *ny, int numPBs, int *action, int *perigo, int firstPos, int Pokedex[6], int *sumScore) {
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
    maiorCelula = -100;
    do {
        for (i = limEsqx; i <= limDirx; i++) { // varre a matriz de x-1 a x+1 (mini matriz das redondezas do player)
            for (j = limSupy; j <= limInfy; j++) { // varre a matriz de y-1 a y+1 (mini matriz das redondezas do player)
                if ((map[i + j*tam] >= maiorCelula) || numPBs == 3) {
                    // caso em que a celula eh a celula em que o jogador atual estao
                    if ((i == x && j == y) && firstPos != 1) {
                        // nao faz nada
                        // printf("**** nao faz nada (%d)\n", *action); //teste
                    }
                    // .
                    // caso em que a matriz foi varrida por completo e a action continua 0
                    else if (action0 && map[i + j*tam] != 8) {
                        *nx = i;
                        *ny = j;
                        *action = 0;
                        action0 = -1;
                        maiorCelula = map[i + j*tam];
                    }
                    // .
                    // caso em que o espaco ja foi "pisado"
                    else if (map[i + j*tam] == 8) {
                        contEspacos8++;
                    }
                    // .
                    // caso em que o espaco eh um pokestop
                    else if (map[i + j*tam] == 6) {
                        if (numPBs > 0 && firstPos != 1) {
                        } // caso em que esta num pokestop, mas ja tem pokebolas
                        else {
                            *nx = i;
                            *ny = j;
                            *action = 1; // acao de pegar pokebolas
                            maiorCelula = map[i + j*tam];
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
                            maiorCelula = map[i + j*tam];
                        }
                    }
                    // .
                    // caso em que eh uma celula "livre"
                    else if (map[i + j*tam] == 0) {
                        *nx = i;
                        *ny = j;
                        *action = 3; // acao "sem acao"
                        maiorCelula = map[i + j*tam];
                    }
                    // .
                    // caso em que a celula eh um "perigo"
                    else if (map[i + j*tam] < 0) {
                        *nx = i;
                        *ny = j;
                        *action = 4; // acao de tomar dano/diminuir score
                        *perigo = map[i + j*tam];
                        maiorCelula = map[i + j*tam];
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
    // pontuacao e pokedex
    Pokedex[maiorCP]+=1;
    if (*action == 2) *sumScore+=maiorCP;
    else if (*action == 4) *sumScore+=*perigo;
    //.
}
// .

void walk(int tam, int* map, int *x, int *y, int nx, int ny, int action, int *numPBs, int *atualPlay, lPos *listaPos, int *pokeCapturados, int *contPassos) {
    tPos tmpPos;
    switch (action) {
        case -1: // fim da partida do jogador atual
            *atualPlay = 0;
            break;
        case 0: // so de passagem (nao realiza acao da celula)
            printf(">> Passando por celula sem acao: [%d, %d]\n", nx, ny);
            break;
        case 1: // pega pokebolas
            map[nx + (ny * tam)] = 8;
            *numPBs+=1;
            printf(">> Pokestop: +1 pokebola! [%d, %d]\n", nx, ny);
            break;
        case 2: // pega pokemon
            map[nx + (ny * tam)] = 8;
            *numPBs-=1;
            *pokeCapturados+=1;
            printf(">> Pokemon capturado! [%d, %d]\n", nx, ny);
            break;
        case 3: // celula livre
            map[nx + (ny * tam)] = 8;
            printf(">> Celula 0: celula livre, passagem sem danos ou ganhos! [%d, %d]\n", nx, ny);
            break;
        case 4: // perigo
            map[nx + (ny * tam)] = 8;
            printf(">> Perigo! [%d, %d]\n", nx, ny);
            break;
    }
    // lista de posicoes
    tmpPos.x = nx;
    tmpPos.y = ny;
    contPassos+=1;
    inserePosicao(tmpPos, listaPos);
    // .

    *x = nx;
    *y = ny;
}
