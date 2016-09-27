/* ---- TADs - Listas */
// Jogador (Trainer)
typedef struct trainer {
    int chave;
    int tPokeballs;
    int tPokedex; // fazer uma lista (pokemon, cp)
    char name[10];
    int x;
    int y;
    int sumScore;
    int caminho; // lista de posicoes
} tTrainer;

typedef struct celula *pTrainer;
typedef struct celula {
    tTrainer treinador;
    pTrainer prox;
} tCelula;

typedef struct trainerlista {
    pTrainer primeiro, ultimo;
} lTrainer;
//.

// Posicao no Mapa - util para sumScore do jogador e para retornar caminho feito pelo jogador
typedef struct pos {
    int x; //linha
    int y; //coluna
} lPos;
//.

/* ---- Cabecalho de Funcoes */
// Funcoes de Listas
void criaListaTrainer(lTrainer *lista);
void insereTrainer(tTrainer x, lTrainer *lista);
void Imprime(lTrainer lista);
// Funcoes de Jogo
void explore();
void walk();
void walkedPath();
