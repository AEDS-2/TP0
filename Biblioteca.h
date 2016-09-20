/* ---- Tipos : Jogador (trainer) e Pokémon */
typedef struct trainer {
    int tPokeballs;
    int tPokedex; // fazer uma lista (pokémon, cp)
    int sumScore;
} tTrainer;

//fazer lista de jogadores

/* ---- Listas : Posições (mapa) */
typedef struct pos {
    int x;
    int y;
} lPos;

/* ---- Cabeçalho de Funções */
void explore();
void walk();
void walkedPath();
