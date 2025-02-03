#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct No {
    int relevado;
    int bomba;
    int possui_bandeira;
    int total_minas_adjacentes;
    struct No* cima;
    struct No* baixo;
    struct No* esquerda;
    struct No* direita;
} No;

typedef struct {
    int largura;
    int altura;
    int **matriz;  //int No** matriz
} Tabuleiro;

Tabuleiro* iniciar_tabuleiro(
    int largura, 
    int altura
);

/**
 * Calcula a quantidade de minas adjacentes de uma determinada posição.
 * @param tabuleiro O tabuleiro do jogo. 
 * @param char A linha da jogada. 
 * @param coluna A coluna da jogada.
 */
int calcular_minas_adjacentes(
    Tabuleiro* tabuleiro, 
    char linha, 
    int coluna
);

/**
 * Revela uma posição do tabuleiro. 
 * @param tabuleiro Ponteiro para o tabuleiro do jogo. 
 */
void reveler_campo(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
);

/**
 * Defina uma bandeira em uma posição. 
 * @param tabuleiro Ponteiro para o tabuleiro do jogo. 
 */
void definir_bandeira(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
);

#endif