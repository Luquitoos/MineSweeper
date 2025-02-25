#ifndef JOGO_H
#define JOGO_H

#include "tabuleiro.h"

typedef struct {
    int largura;
    int altura;
    int maximoDeMinas;
    int minasRestantes;
    int quantidadeJogadas; // Conta ações do jogador, pode ser relevante em algum momento.
    int jogo_ativo;
    Tabuleiro* tabuleiro; // Ponteiro para o tabuleiro
} Jogo;

/**
 * Inicializa o jogo. 
 * @return Ponteiro para a struct Jogo inicializada.
 */
Jogo* iniciar_jogo(
    int largura,
    int altura,
    int quantidadeMinas
);

/**
 * Processa uma ação do jogo.
 */
int processar_acao(Jogo* jogo);
int calcular_maximo_minas(int largura, int altura);

/**
 * Abandona um jogo, libera a memória e redireciona o 
 * jogador para a interface inicial. 
 * 
 * @param causa Se o jogador desistiu, completou ou outra razão.
 * 
 */
void finalizar_jogo(Jogo* jogo);
void exibir_vitoria(Jogo* jogo);

/**
 * Calcula as posições do tabuleiro para uma posição válida.
 */
void exibir_dica(Tabuleiro* tabuleiro);

/**
 * Exibe um erro por alguns segundos.
 */
void exibir_erro(int codigoErro);

void delay_ms(int milisegundos);

#endif