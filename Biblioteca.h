/* ---- TADs - Listas */
// Posicao no Mapa - util para sumScore do jogador e para retornar caminho feito pelo jogador
typedef struct pos {
    int x; //linha
    int y; //coluna
} tPos;

typedef struct celulaPos *pPos;
typedef struct celulaPos {
    tPos posicao;
    pPos prox;
} celPos;

typedef struct posicaoLista {
    pPos primeiro, ultimo;
} lPos;
//.

// Jogador (Trainer)
typedef struct trainer {
    int chave;
    char name[10];
    int tPokeballs, x, y, sumScore;
    int tPokedex[6]; // fazer uma lista (pokemon, cp)
    lPos listaCaminho; // lista de posicoes
    int contPassos, contMaior;
} tTrainer;

typedef struct tCelula *pTrainer;
typedef struct tCelula {
    tTrainer treinador;
    pTrainer prox;
} tCelula;

typedef struct trainerlista {
    pTrainer primeiro, ultimo;
} lTrainer;
//.

/* ---- Cabecalho de Funcoes */
// Funcoes de Listas
void criaListaTrainer(lTrainer *lista);
void insereTrainer(tTrainer x, lTrainer *lista);
void criaListaPosicoes(lPos *lista);
void inserePosicao(tPos x, lPos *lista);
// Funcoes de Jogo
void imprimeInicioJogo(lTrainer lista, int numPlayer);
void desenhaMapa (int tam, int *map, int xPlayer, int yPlayer);
void infoJogador(lTrainer lista, int numPlayer, int *x, int *y, int *pbs, lPos listaPos, int Pokedex[6], int *sumScore);
void attJogador(lTrainer lista, int numPlayer, int x, int y, int pbs, lPos listaPos, int Pokedex[6], int sumScore, int contPassos);
void explore(int tam, int* map, int x, int y, int *nx, int *ny, int numPBs, int *action, int *perigo, int firstPos, int Pokedex[6], int *sumScore);
void walk(int tam, int* map, int *x, int *y, int nx, int ny, int action, int *numPBs, int *atualPlay, lPos *listaPos, int *pokeCapturados, int *contPassos);
void imprimePassos(lPos lista, FILE *saida);
void imprimeNome(lTrainer lista, int numPlayer, FILE *saida);
void declaraVencedor(lTrainer lista, int numPlayer, FILE *saida);
