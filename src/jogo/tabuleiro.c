#include <stdio.h>
#include <stdlib.h>

#include "tabuleiro.h"

Tabuleiro* iniciar_tabuleiro(
    int largura, 
    int altura,
    int quantidadeBombas
) {
    // Aloca memória para o tabuleiro
    Tabuleiro* tabuleiro = (Tabuleiro*) malloc(sizeof(Tabuleiro));
    if (!tabuleiro) return NULL;

    // Aloca memória para a matriz de ponteiros para linhas
    tabuleiro->matriz = (No**) malloc(altura * sizeof(No*));
    if (!tabuleiro->matriz) {
        free(tabuleiro);
        return NULL;
    }

    // Aloca memória para cada linha da matriz
    for (int i = 0; i < altura; i++) {
        tabuleiro->matriz[i] = (No*) malloc(largura * sizeof(No));
        if (!tabuleiro->matriz[i]) {
            // Libera memória alocada em caso de falha
            for (int j = 0; j < i; j++) {
                free(tabuleiro->matriz[j]);
            }
            free(tabuleiro->matriz);
            free(tabuleiro);
            return NULL;
        }
    }

    // Predefinir 

    return tabuleiro;
}

No* obter_no(
    char linha,
    int coluna
) {

}

int calcular_minas_adjacentes(
    Tabuleiro* tabuleiro, 
    char linha, 
    int coluna
) {

}

void reveler_campo(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
) {

}

void definir_bandeira(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
) {

}
