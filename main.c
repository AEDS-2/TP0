#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Biblioteca.h"

int main () {
    FILE *entrada = fopen("ent.txt", "r");
    int tam, i, j, dLoop, m = 0, n = 0; // variaveis do loop de desenho
    int numPlayers;
    fscanf(entrada, "%d\n", &tam); //le primeiro item do arquivo = tamanho do mapa
    //cria trainer temporário pra passagem pra lista
    tTrainer tmpTrainer;
    lTrainer *listaTrainer;
    criaListaTrainer(listaTrainer);

    // Coleta de dados do arquivo : matriz/mapa, jogadores
    int map[tam][tam];
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            fscanf(entrada, "%d ", &map[i][j]);
        }
    }
    fscanf(entrada, "%d ", &numPlayers);
    for (i = 0; i < numPlayers; i++) {
        tmpTrainer.chave = i;
        tmpTrainer.tPokeballs = 3;
        fscanf(entrada, "%s:", &tmpTrainer.name);
        fscanf(entrada, "%d,", &tmpTrainer.x);
        fscanf(entrada, "%d", &tmpTrainer.y);
        insereTrainer(tmpTrainer, listaTrainer);
    }
    // .
    Imprime(*listaTrainer);
    sleep(5);
    system("clear");


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
                if (map[m][n] < 0) // perigo
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
    sleep(1);
    //system("clear");
//        printf("%s: %d, %d\nPokeballs: %d", tmpTrainer.name, tmpTrainer.x, tmpTrainer.y, tmpTrainer.tPokeballs);

    return 0;
}
