/*~
> TODO
: exibir vencedor
:
~*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Biblioteca.h"

int main () {
    FILE *entrada = fopen("ent.txt", "r"), *saida = fopen("sai.txt", "w");
    int inGame = 1, atualPlay, numPlayers, tam, i = 0, j, action = -1, perigo = 0, firstPos, sumScore = 0, pokeCapturados = 0, contPassos = 0;
    int Pokedex[6];
    int atualPlayer = 0, xPlayer = 0, yPlayer = 0, nx = 0, ny = 0, numPBs = 0; // variaveis usadas para ter as informacoes do jogador atual
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
    // .

   // texto introdutorio
    system("clear");
    printf("=====* Bem-vindo/a a Pokemon - Versao Matriz! *=====\n\n=> Simbolos do Jogo:\n* - Posicao do Jogador\nX - Perigo\nP - Pokestop\n1~6 - Pokemons\n- - Espaco ja Passado\n\n");
    sleep(5);
    printf("As informacoes serao retiradas do arquivo, aguarde um momento\n");
    while (i<3) {
        sleep(1);
        printf(".\n");
        i++;
    }
    printf("Done!\n\n");
    sleep(2);
    // .


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
    fclose(entrada);
    // .

    // repeticao do jogo
    while (inGame <= numPlayers) {
        // imprime saudacao inicial ao jogador atual e armazena informacoes dele
        imprimeInicioJogo(*listaTrainer, atualPlayer);
        criaListaPosicoes(listaPos);
        infoJogador(*listaTrainer, atualPlayer, &xPlayer, &yPlayer, &numPBs, *listaPos, Pokedex, &sumScore);
        // .
        // limpa variaveis para nova partida
        firstPos = 1; atualPlay = 1; pokeCapturados = 0; contPassos = 0;
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                map[i][j] = mapSave[i][j];
            }
        }
        for (i = 0; i < 6; i++) {
            Pokedex[i] = 0;
        }
        //.
        // joga enquanto nao acaba partida do jogador atual : explora, anda, desenha mapa e exibe informacoes
        while (atualPlay) {
            explore(tam, *map, xPlayer, yPlayer, &nx, &ny, numPBs, &action, &perigo, firstPos, Pokedex, &sumScore); //explora
            walk(tam, *map, &xPlayer, &yPlayer, nx, ny, action, &numPBs, &atualPlay, listaPos, &pokeCapturados, &contPassos); //anda
            // confere se partida ja acabou. se nao, imprime informacoes
            if (atualPlay != 0) {
                desenhaMapa(tam, *map, xPlayer, yPlayer);
                printf("Pontuacao: %d\nNumero de Pokebolas: %d | Numero de Pokemons Capturados: %d\n", sumScore, numPBs, pokeCapturados);
                sleep(2);
                system("clear");
            }
            // .
            firstPos++;
        }
        // .
        printf("*** Fim da Partida do Jogador %d! ***\nPontuacao Final: %d\n\n", atualPlayer+1, sumScore);
        attJogador(*listaTrainer, atualPlayer, xPlayer, yPlayer, numPBs, *listaPos, Pokedex, sumScore, contPassos); // atualiza lista do jogador atual
        sleep(3);

        // retorno de todas as informacoes para o arquivo
        imprimeNome(*listaTrainer, atualPlayer, saida);
        fprintf(saida, "%d", sumScore);
        imprimePassos(*listaPos, saida);
        // .

        inGame++;
        atualPlayer++;

    }
    // .
    declaraVencedor(*listaTrainer, numPlayers, saida);
    fclose(saida);
    return 0;
}
