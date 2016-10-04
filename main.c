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
    int inGame = 1, atualPlay = 1, numPlayers, tam, i = 0, j, action = -1, perigo = 0;
    char namePlayer[15]; int atualPlayer = 0, xPlayer = 0, yPlayer = 0, nx = 0, ny = 0, numPBs = 0; // variaveis usadas para ter as informacoes do jogador atual
    char token[10];
    // le primeiro item do arquivo = tamanho do mapa
    fscanf(entrada, "%d\n", &tam);
    // .
    // cria trainer temporario pra passagem pra lista / cria e aloca lista
    tTrainer tmpTrainer;
    lTrainer *listaTrainer = (lTrainer *) malloc(sizeof(lTrainer));
    criaListaTrainer(listaTrainer);
    // .
    // cria lista de posicoes
    lPos *listaPos = (lPos *) malloc(sizeof(lPos));
    criaListaPosicoes(listaPos);
    // .


    /* textos introdutorios!!!
    system("clear");
    printf("=====* Bem-vindo/a a Pokemon - Matriz Version! *=====\n\n=> Siglas do Jogo:\n* - Posicao do Jogador\nX - Perigo\nP - Pokestop\n1~6 - Pokemons\n- - Espaco ja Passado\n\n");
    sleep(5);
    //TODO: intrucoes/informacoes do jogo, como a sigla por exemplo
    printf("As informacoes serao retiradas do arquivo, aguarde um momento\n");
    while (i<5) {
        sleep(1);
        printf(".\n");
        i++;
    }
    printf("Done!\n\n");
    sleep(2);
    // !!! */
    // Coleta de dados do arquivo : matriz/mapa - variavel, jogadores - lista
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

    // repeticao do jogo
    while (inGame < tam) {
        imprimeInicioJogo(*listaTrainer, atualPlayer); // imprime saudacao inicial ao jogador atual
        infoJogador(*listaTrainer, atualPlayer, &xPlayer, &yPlayer, &numPBs, &namePlayer[15]); // recolhe info do jogador atual que estao na lista dos jogadores
        while (atualPlay) { // joga enquanto nao acaba partida do jogador atual
            // TODO: fazer pegar o primeiro local (inicial)
            explore(tam, *map, xPlayer, yPlayer, &nx, &ny, numPBs, &action, &perigo);
            walk(tam, *map, &xPlayer, &yPlayer, nx, ny, action, &numPBs);
            desenhaMapa(tam, *map, xPlayer, yPlayer);
            printf("\n");
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
        acao (se houver)
        escreve acao na tela
        sleep(1)
        clear
        se fim de mapa, exibe pontuacao do jogador, pokemons, recomeca loop de jogador
        se nao fim de mapa, entao continua loop do jogador
        se fim de jogo, clear, exibe ganhadores, (exibe animacao de vitória?)
        se nao fim de jogo, continua loop de jogo
    */
    return 0;
}
