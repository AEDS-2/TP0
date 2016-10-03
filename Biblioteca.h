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
    pPos primeiro, uiltimo;
} lPos;
//.

// Jogador (Trainer)
typedef struct trainer {
    int chave;
    char name[10];
    int tPokeballs, x, y, sumScore;
    int tPokedex; // fazer uma lista (pokemon, cp)
    int caminho; // lista de posicoes
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
// Funcoes de Jogo
void imprimeInicioJogo(lTrainer lista, int numPlayer);
void caminhoJogador(lTrainer lista, int numPlayer, int *x, int *y);
void explore(int tam, int* map, int x, int y, int *nx, int *ny);
void walk();
void walkedPath();
