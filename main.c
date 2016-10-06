/*~
> TODO
: pontos soltos de ToDo pelo projeto
: nome nas info do jogador
: venceor
Problemas :
- C1 no final
~*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Biblioteca.h"

int main () {
    FILE *entrada = fopen("ent.txt", "r"), *saida = fopen("sai.txt", "w");
    int inGame = 1, atualPlay, numPlayers, tam, i = 0, j, action = -1, perigo = 0, firstPos, sumScore = 0, pokeCapturados = 0;
    int Pokedex[6];
    char namePlayer; int atualPlayer = 0, xPlayer = 0, yPlayer = 0, nx = 0, ny = 0, numPBs = 0; // variaveis usadas para ter as informacoes do jogador atual
    char token[10];
    tPos tmpPos;
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

    /*/ texto introdutorio
    system("clear");
    printf("=====* Bem-vindo/a a Pokemon - Matriz Version! *=====\n\n=> Simbolos do Jogo:\n* - Posicao do Jogador\nX - Perigo\nP - Pokestop\n1~6 - Pokemons\n- - Espaco ja Passado\n\n");
    sleep(5);
    printf("As informacoes serao retiradas do arquivo, aguarde um momento\n");
    while (i<5) {
        sleep(1);
        printf(".\n");
        i++;
    }
    printf("Done!\n\n");
    sleep(2);
    // .*/

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
        infoJogador(*listaTrainer, atualPlayer, &xPlayer, &yPlayer, &numPBs, &namePlayer, *listaPos, Pokedex, &sumScore); // TODO: fazer exibicao do nome
        // .
        // limpa variaveis para nova partida
        firstPos = 1; atualPlay = 1; pokeCapturados = 0;
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                map[i][j] = mapSave[i][j];
            }
        }
        for (i = 0; i < 6; i++) {
            Pokedex[i] = 0;
        }
        //.
        // insere primeira posicao na lista
        tmpPos.x = xPlayer;
        tmpPos.y = yPlayer;
        inserePosicao(tmpPos, listaPos);
        // .

        // joga enquanto nao acaba partida do jogador atual : explora, anda, desenha mapa e exibe informacoes
        while (atualPlay) {
            explore(tam, *map, xPlayer, yPlayer, &nx, &ny, numPBs, &action, &perigo, firstPos, Pokedex, &sumScore);
            walk(tam, *map, &xPlayer, &yPlayer, nx, ny, action, &numPBs, &atualPlay, listaPos, &pokeCapturados);
            // confere se partida ja acabou
            if (atualPlay != 0) {
                desenhaMapa(tam, *map, xPlayer, yPlayer);
                printf("Player: %s | Pontuacao: %d\nNumero de Pokebolas: %d | Numero de Pokemons Capturados: %d\n", &namePlayer, sumScore, numPBs, pokeCapturados);
                sleep(2);
                system("clear");
            }
            // .
            firstPos++;
        }
        // .
        printf("Fim da Partida do Jogador [nome]!\nPontuacao Final: %d\n\n", sumScore);
        sleep(3);

        // retorno de todas as informacoes para o arquivo
        //fprintf(saida, "\n %s ", namePlayer);
        fprintf(saida, "%d \n", sumScore);
        imprimePassos(*listaPos, saida);
        // .

        inGame++;
        atualPlayer++;
    }
    // .
    fclose(saida);
    return 0;
}
