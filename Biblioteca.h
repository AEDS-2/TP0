/* ---- TADs - Listas */
// Jogador (Trainer)
typedef struct trainer {
    int chave;
    int tPokeballs;
    int tPokedex; // fazer uma lista (pokémon, cp)
    int sumScore;
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

// Posicao no Mapa
typedef struct pos {
    int x; //linha
    int y; //coluna
} lPos;
//.

/* ---- Cabecalho de Funcoes */
// Funções de Listas
void criaLista(lTrainer *lista);

// Funcoes de Jogo
void explore();
void walk();
void walkedPath();
