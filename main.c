// TODO next: configurar a lista de posicoes na funcao walk
/*~
> TODO
: pontos soltos de ToDo pelo projeto
: walkedPath
: reler pdf
: arrumar tempo de todos os sleeps
: conferir porque o mapa desenhado nao ta atualizando!! > algum problema na varredura da matriz
~*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Biblioteca.h"

int main () {
    FILE *entrada = fopen("ent.txt", "r");
    int inGame = 1, atualPlay = 1, numPlayers, action = -1, tam, i = 0, j;
    int atualPlayer = 0, xPlayer = 0, yPlayer = 0, nx = 0, ny = 0, numPBs = 0; // variaveis usadas para ter as informações do jogador atual
    char token[10];
    // le primeiro item do arquivo = tamanho do mapa
    fscanf(entrada, "%d\n", &tam);
    // .
    // cria trainer temporário pra passagem pra lista / cria e aloca lista
    tTrainer tmpTrainer;
    lTrainer *listaTrainer = (lTrainer *) malloc(sizeof(lTrainer));
    criaListaTrainer(listaTrainer);
    // .
    // cria lista de posicoes
    lPos *listaPos = (lPos *) malloc(sizeof(lPos));
    criaListaPosicoes(listaPos);
    // .


    /* textos introdutórios!!!
    system("clear");
    printf("=====* Bem-vindo/a a Pokemon - Matriz Version! *=====\n\n=> Siglas do Jogo:\n* - Posicao do Jogador\nX - Perigo\nP - Pokestop\n1~6 - Pokemons\n\n");
    sleep(5);
    //TODO: intruções/informações do jogo, como a sigla por exemplo
    printf("As informacoes serao retiradas do arquivo, aguarde um momento\n");
    while (i<5) {
        sleep(1);
        printf(".\n");
        i++;
    }
    printf("Done!\n\n");
    sleep(2);
    // !!! */
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
    int vamo =0;
    // repeticao do jogo
    while (inGame < tam) {
        imprimeInicioJogo(*listaTrainer, atualPlayer); // imprime saudação inicial ao jogador atual
        while (atualPlay) { // joga enquanto não muda jogador/nao acaba partida
            printf("%d\n", vamo);
            infoJogador(*listaTrainer, atualPlayer, &xPlayer, &yPlayer, &numPBs);
            desenhaMapa(tam, *map, xPlayer, yPlayer);
            explore(tam, *map, xPlayer, yPlayer, &nx, &ny, numPBs, &action);
            walk(tam, *map, &xPlayer, &yPlayer, nx, ny, action);
            vamo++;
        }
        inGame++;
        atualPlayer++;
    }
    // .

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
    return 0;
}
