/*~
> TODO
: pontos soltos de ToDo pelo projeto
: walkedPath
: reler pdf
: arrumar tempo de todos os sleeps
: nome nas info do jogador
: listagem de pokemons (vetor)
: listagem de posicoes (lista)
: score total
~*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Biblioteca.h"

int main () {
    FILE *entrada = fopen("ent.txt", "r");
    int inGame = 1, atualPlay, numPlayers, tam, i = 0, j, action = -1, perigo = 0, firstPos;
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
    int map[tam][tam], mapSave[tam][tam];
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            fscanf(entrada, "%d ", &map[i][j]);
            mapSave[i][j] = map[i][j];
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
    while (inGame <= numPlayers) {
        // imprime saudacao inicial ao jogador atual e armazena informacoes dele
        imprimeInicioJogo(*listaTrainer, atualPlayer);
        infoJogador(*listaTrainer, atualPlayer, &xPlayer, &yPlayer, &numPBs, NULL); // TODO: fazer exibicao do nome
        // .
        // limpa variaveis para nova partida
        firstPos = 1; atualPlay = 1;
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                map[i][j] = mapSave[i][j];
            }
        }
        //.

        // joga enquanto nao acaba partida do jogador atual : explora, anda, desenha mapa e exibe informacoes
        while (atualPlay) {
            explore(tam, *map, xPlayer, yPlayer, &nx, &ny, numPBs, &action, &perigo, firstPos);
            walk(tam, *map, &xPlayer, &yPlayer, nx, ny, action, &numPBs, &atualPlay);
            // confere se partida ja acabou
            if (atualPlay != 0) {
                desenhaMapa(tam, *map, xPlayer, yPlayer);
                printf("Player: [nome] | Pontuacao: [num]\nNumero de Pokebolas: %d | Numero de Pokemons Capturados: [num]\n", numPBs);
                sleep(2);
                system("clear");
            }
            // .
            firstPos++;
        }
        // .

        printf("Fim da Partida do Jogador [nome]!\nPontuacao Final: [score]\n\n");
        sleep(3);
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
