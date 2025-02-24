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

typedef struct Fila {
    No* no;
    struct Fila* prox;
} Fila;

/**
 * Inicializa um novo tabuleiro com as dimensões e quantidade de bombas especificadas.
 * @param largura Largura do tabuleiro.
 * @param altura Altura do tabuleiro.
 * @param quantidadeBombas Número de bombas a serem distribuídas.
 * @return Ponteiro para o tabuleiro inicializado.
 */
Tabuleiro* iniciar_tabuleiro(int largura, int altura, int quantidadeBombas);

/**
 * Obtém um nó do tabuleiro a partir das coordenadas fornecidas.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 * @param linha A linha da jogada.
 * @param coluna A coluna da jogada.
 * @return Ponteiro para o nó correspondente.
 */
No* obter_no(Tabuleiro* tabuleiro, char linha, int coluna);

/**
 * Calcula a quantidade de minas adjacentes a uma determinada posição.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 * @param linha A linha da jogada.
 * @param coluna A coluna da jogada.
 * @return Número de minas adjacentes à posição especificada.
 */
int calcular_minas_adjacentes(Tabuleiro* tabuleiro, char linha, int coluna);

/**
 * Revela uma posição do tabuleiro e verifica se a jogada resulta em uma explosão.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 * @param jogadasTotais Número total de jogadas feitas até o momento.
 * @param linha A linha da jogada.
 * @param coluna A coluna da jogada.
 * @param chamada_recursiva Indica se a chamada foi feita recursivamente.
 * @return 1 se a jogada resultou em explosão, 0 caso contrário.
 */
int revelar_campo(Tabuleiro* tabuleiro, int jogadasTotais, char linha, int coluna, int chamada_recursiva);

/**
 * Define uma bandeira em uma posição do tabuleiro.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 * @param linha A linha da posição.
 * @param coluna A coluna da posição.
 * @return 1 se a bandeira foi definida com sucesso, 0 caso contrário.
 */
int definir_bandeira(Tabuleiro* tabuleiro, char linha, int coluna);

/**
 * Remove uma bandeira de uma posição do tabuleiro.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 * @param linha A linha da posição.
 * @param coluna A coluna da posição.
 * @return 1 se a bandeira foi removida com sucesso, 0 caso contrário.
 */
int remover_bandeira(Tabuleiro* tabuleiro, char linha, int coluna);

/**
 * Distribui as bombas aleatoriamente pelo tabuleiro.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 */
void distribuir_bombas(Tabuleiro* tabuleiro);

/**
 * Realoca uma bomba em caso de primeira jogada ou condição especial.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 * @param linha A linha onde a realocação deve ocorrer.
 * @param coluna A coluna onde a realocação deve ocorrer.
 * @return 1 se a realocação foi bem-sucedida, 0 caso contrário.
 */
int realoca_bomba(Tabuleiro* tabuleiro, char linha, int coluna);

/**
 * Exibe a localização de todas as bombas no tabuleiro.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 */
void exibir_bombas(Tabuleiro* tabuleiro);

/**
 * Verifica se o jogador venceu a partida, ou seja, todas as células seguras foram reveladas.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 * @return 1 se o jogador venceu, 0 caso contrário.
 */
int vitoria(Tabuleiro* tabuleiro);

/**
 * Obtém uma dica usando um algoritmo baseado em busca BFS.
 * O algoritmo verifica se a quantidade de bombas adjacentes é igual ao número de posições
 * não reveladas adjacentes. Se for, todas as posições ocultas são bombas. Caso contrário,
 * uma posição aleatória é sugerida.
 * @param tabuleiro Ponteiro para o tabuleiro do jogo.
 * @return String representando a dica de onde pode haver uma bomba.
 */
char* obter_dica(Tabuleiro* tabuleiro);

#endif