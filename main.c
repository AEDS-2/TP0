#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Biblioteca.h"

int main () {
    FILE *entrada = fopen("ent.txt", "r");
    int tam, i, j, numPlayers, tmp;
    fscanf(entrada, "%d\n", &tam); //le primeiro item do arquivo = tamanho do mapa

    // Coleta de dados do arquivo : matriz/mapa, jogadores
    int map[tam][tam];
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            fscanf(entrada, "%d ", &map[i][j]);
        }
    }
    fscanf(entrada, "%d ", &numPlayers);
    for (i = 0; i < numPlayers; i++) {
        //Fazer lista de trainers
    }
    // .






    //do {
        for(i=0;i<=tam;i++) {
            printf("\n+");
            j=0;
            while (j<tam) {
                printf("===+");
                j++;
            }
            if (i<tam) {
                printf("\n|");
                j=0;
                while (j<tam) {
                    fscanf(entrada, "%d ", &tmp);
                    if (tmp < 0) printf(" x |");
                    else if (tmp == 6) printf(" P |");
                    else printf(" %d |", tmp);
                    j++;
                }
            }
        }
        printf("\n");
        sleep(1);
        system("clear");
    //} while (1 != 0);

    return 0;
}
