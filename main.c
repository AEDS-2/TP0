#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Biblioteca.h"

int main () {
    FILE *entrada = fopen("ent.txt", "r");
    int tam, i, j, dLoop, m = 0, n = 0; // variaveis do loop de desenho
    int inGame = 1, numPlayers;
    int atualPlayer = 0, xPlayer = 0, yPlayer = 0, nx = 0, ny = 0, nPBs = 0; // variaveis usadas para ter as informações do jogador atual
    char token[10];
    // le primeiro item do arquivo = tamanho do mapa
    fscanf(entrada, "%d\n", &tam);
    // .
    // cria trainer temporário pra passagem pra lista
    tTrainer tmpTrainer;
    lTrainer *listaTrainer = (lTrainer *) malloc(sizeof(lTrainer));
    criaListaTrainer(listaTrainer);
    // .

    //TODO: intruções/informações do jogo, como a sigla por exemplo

    // Coleta de dados do arquivo : matriz/mapa - variável, jogadores - lista
    int map[tam][tam];
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            fscanf(entrada, "%d ", &map[i][j]);
        }
    }
    fscanf(entrada, "%d ", &numPlayers);
    for (i = 0; i < numPlayers; i++) {
        tmpTrainer.chave = i+1;
        tmpTrainer.tPokeballs = 3;
        fscanf(entrada, "%s: ", token);
        strcpy(tmpTrainer.name, strtok(token, ":"));
        fscanf(entrada, "%d,", &tmpTrainer.x);
        fscanf(entrada, "%d", &tmpTrainer.y);
        insereTrainer(tmpTrainer, listaTrainer);
    }
    // .

    while (inGame < tam) {
        imprimeInicioJogo(*listaTrainer, atualPlayer);
        sleep(2);
        system("clear");
        caminhoJogador(*listaTrainer, atualPlayer, &xPlayer, &yPlayer);
        for(dLoop = 0; dLoop <= tam; dLoop++) { // loop que controla o numero de vezes que as linhas "+===+" e "| elemento |" serão desenhadas
            printf("\n+"); // primeiro simbolo da linha de "+===+"
            i = 0; // zera i para novo loop
            n = 0; // começa nova numeração de colunas na exibicao dos numeros no mapa
            while (i < tam) { // desenha a quantidade de necessaria de "+===+" em cada linha (se tam = 3, desenha 3 vezes, uma linha só)
                printf("===+");
                i++;
            }
            j = 0; // zera j para novo loop
            if (dLoop < tam) { // confere numero de exibicoes, pois o while acima deve exibir uma vez a mais
                printf("\n|"); // primeiro simobolo da linha de "| elemento |"
                while (j < tam) { //desenha a quantidade de "| elemento |" em cada linha
                    if (m == xPlayer && n == yPlayer) //jogador
                        printf(" * |");
                    else if (map[m][n] < 0) // perigo
                        printf(" X |");
                    else if (map[m][n] == 6) // pokestop
                        printf(" P |");
                    else //pokemons
                        printf(" %d |", map[m][n]);
                    n++;
                    j++;
                }
            }
            m++; // vai pra proxima linha da matriz do mapa
        }
        printf("\n"); // coloquei só porque por algum motivo que DEUS sabe, tava desconfigurando o desenho
        sleep(5);
        explore(tam, *map, xPlayer, yPlayer, &nx, &ny);
        inGame++;
        atualPlayer++;
    }

    /*
        entra no loop do jogo
        exibe nome do jogador atual
        entra no loop de um jogador
        olha posicoes por perto
        anda (se posivel)
        desenha na tela
        ação (se houver)
        escreve ação na tela
        sleep(1)
        clear
        se fim de mapa, exibe pontuação do jogador, pokemons, recomeça loop de jogador
        se não fim de mapa, então continua loop do jogador
        se fim de jogo, clear, exibe ganhadores, (exibe animação de vitória?)
        se não fim de jogo, continua loop de jogo
    */



    sleep(1);
    //system("clear");
//        printf("%s: %d, %d\nPokeballs: %d", tmpTrainer.name, tmpTrainer.x, tmpTrainer.y, tmpTrainer.tPokeballs);

    return 0;
}
