#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct No {
    int revelado;
    int bomba;
    int possui_bandeira;
    int total_minas_adjacentes;
    struct No* cima_esquerda;
    struct No* cima_direita;
    struct No* cima;
    struct No* baixo_esquerda;
    struct No* baixo_direita;
    struct No* baixo;
    struct No* esquerda;
    struct No* direita;
} No;

typedef struct {
    int largura;
    int altura;
    int quantidadeBombas;
    No** matriz;
} Tabuleiro;

Tabuleiro* iniciar_tabuleiro(
    int largura, 
    int altura,
    int quantidadeBombas
);

No* obter_no(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
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
int revelar_campo(
    Tabuleiro* tabuleiro, 
    int* jogadasTotais, 
    char linha, 
    int coluna, 
    int chamada_recursiva
);

/**
 * Executa uma busca usando BFS para encontrar uma posição de uma
 * possível bomba.
 * 
 * O algoritmo considera um tabuleiro como um grafo e verifica se
 * a quantidade de bombas adjacentes é igual ao número de posições
 * não reveladas adjacentes. Se for, é uma bomba. Se não, aleatoriza
 * uma posição aleatória adjacente não revelada.
 */
char* obter_dica(
    Tabuleiro* tabuleiro
);

void distribuir_bombas(Tabuleiro* tabuleiro);
int realoca_bomba(Tabuleiro* tabuleiro, char linha, int coluna);
void exibir_bombas(Tabuleiro* tabuleiro);

/**
 * Defina uma bandeira em uma posição. 
 * @param tabuleiro Ponteiro para o tabuleiro do jogo. 
 */
int definir_bandeira(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
);

int remover_bandeira(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
);


#endif