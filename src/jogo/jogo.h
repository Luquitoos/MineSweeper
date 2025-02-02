#ifndef JOGO_H
#define JOGO_H

#include "tabuleiro.h"

typedef struct {
    int largura;
    int altura;
    int maximoDeMinas;
    int minasRestantes;
    int actions; // Conta ações do jogador, pode ser relevante em algum momento.
    int jogo_ativo;
    Tabuleiro* tabuleiro; // Ponteiro para o tabuleiro
} Jogo;

/**
 * Inicializa o jogo. 
 * @return Ponteiro para a struct Jogo inicializada.
 */
Jogo* iniciar_jogo(
    int largura,
    int altura
);

/**
 * Processa uma ação do
 */
void processar_acao(Jogo* jogo, int acao);

/**
 * Abandona um jogo, libera a memória e redireciona o 
 * jogador para a interface inicial. 
 * 
 * @param causa Se o jogador desistiu, completou ou outra razão.
 * 
 */
void finalizar_jogo(Jogo* jogo, int causa);

#endif