#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    tabuleiro->quantidadeBombas = quantidadeBombas;

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

    // Predefinir os valores de cada nó
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            tabuleiro->matriz[i][j].revelado = 0;
            tabuleiro->matriz[i][j].bomba = 0;
            tabuleiro->matriz[i][j].possui_bandeira = 0;
            tabuleiro->matriz[i][j].total_minas_adjacentes = 0;

            tabuleiro->matriz[i][j].cima = (i > 0) ? &tabuleiro->matriz[i - 1][j] : NULL;
            tabuleiro->matriz[i][j].baixo = (i < altura - 1) ? &tabuleiro->matriz[i + 1][j] : NULL;
            tabuleiro->matriz[i][j].esquerda = (j > 0) ? &tabuleiro->matriz[i][j - 1] : NULL;
            tabuleiro->matriz[i][j].direita = (j < largura - 1) ? &tabuleiro->matriz[i][j + 1] : NULL;

            tabuleiro->matriz[i][j].cima_esquerda = (i > 0 && j > 0) ? &tabuleiro->matriz[i - 1][j - 1] : NULL;
            tabuleiro->matriz[i][j].cima_direita = (i > 0 && j < largura - 1) ? &tabuleiro->matriz[i - 1][j + 1] : NULL;
            tabuleiro->matriz[i][j].baixo_esquerda = (i < altura - 1 && j > 0) ? &tabuleiro->matriz[i + 1][j - 1] : NULL;
            tabuleiro->matriz[i][j].baixo_direita = (i < altura - 1 && j < largura - 1) ? &tabuleiro->matriz[i + 1][j + 1] : NULL;
        }
    }

    return tabuleiro;
}

No* obter_no(Tabuleiro* tabuleiro, char linha, int coluna) {
    if (!tabuleiro || !tabuleiro->matriz) return NULL;

    int indice_linha;
    if (linha >= 'A' && linha <= 'Z') {
        indice_linha = linha - 'A';
    } else if (linha >= 'a' && linha <= 'z') {
        indice_linha = linha - 'a';
    } else {
        return NULL;
    }

    // (inicia do zero)
    int indice_coluna = coluna - 1;

    /**
     * Caso passe dos limites do tabuleiro, ele retorna null.
     */
    if (indice_linha < 0 || indice_linha >= tabuleiro->altura ||
        indice_coluna < 0 || indice_coluna >= tabuleiro->largura) {
        return NULL;
    }

    return &tabuleiro->matriz[indice_linha][indice_coluna];
}

int calcular_minas_adjacentes(
    Tabuleiro* tabuleiro, 
    char linha, 
    int coluna
) {
    int total = 0;

    No* no = obter_no(tabuleiro, linha, coluna);
    if (!no)
        return total;

    if (no->cima && no->cima->bomba) total++;
    if (no->baixo && no->baixo->bomba) total++;
    if (no->esquerda && no->esquerda->bomba) total++;
    if (no->direita && no->direita->bomba) total++;
    if (no->cima_esquerda && no->cima_esquerda->bomba) total++;
    if (no->cima_direita && no->cima_direita->bomba) total++;
    if (no->baixo_esquerda && no->baixo_esquerda->bomba) total++;
    if (no->baixo_direita && no->baixo_direita->bomba) total++;


    return total;
}


void distribuir_bombas(
    Tabuleiro* tabuleiro
) {
    if (!tabuleiro || tabuleiro->quantidadeBombas <= 0)
        return;

    int totalCampos = tabuleiro->largura * tabuleiro->altura;
    int* indices = (int*) malloc(totalCampos * sizeof(int));
    if (!indices)
        return;

    // ele cria um array com vários indices
    // dps ele aleatoriza para aleatorizar as posições das bombas
    for (int i = 0; i < totalCampos; i++) {
        indices[i] = i;
    }

    srand(time(NULL));
    for (int i = totalCampos - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Ddefine as bombas nas posições sorteadas
    for (int i = 0; i < tabuleiro->quantidadeBombas; i++) {
        int idx = indices[i];
        int linha = idx / tabuleiro->largura;
        int coluna = idx % tabuleiro->largura;
        tabuleiro->matriz[linha][coluna].bomba = 1;
    }

    free(indices);
}


// 0 -> sucesso
// os outros códigos de erro estão relacionados com o arquivo 'jogo.c'
int revelar_campo(
    Tabuleiro* tabuleiro,
    int* jogadasTotais,
    char linha,
    int coluna
) {
    No* no = obter_no(tabuleiro, linha, coluna);

    // Esse erro só irá acontecer se o tabuleiro não tiver sido inicializado.
    // Na implementação adequada, é impossível, mas é boa verificação por segurança.
    if (no == NULL)
        return -1;
    
    if (no->revelado)
        return 4;

    no->revelado = 1;

    if (jogadasTotais == 0)
        // A distribuição de bombas acontece APÓS a primeira jogada.
        distribuir_bombas(tabuleiro);
    
    no->total_minas_adjacentes = calcular_minas_adjacentes(tabuleiro, linha, coluna);
    
    if (no->total_minas_adjacentes == 0) {
        // revela os adjacentes que tem 0 bombas adjacentes
    }

    (*jogadasTotais)++;
    return 0;
}


int definir_bandeira(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
) {
    No* no = obter_no(tabuleiro, linha, coluna);

    // Esse erro só irá acontecer se o tabuleiro não tiver sido inicializado.
    // Na implementação adequada, é impossível, mas é boa verificação por segurança.
    if (no == NULL)
        return -1;

    no->possui_bandeira = 1;
    return 0;
}

int remover_bandeira(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
) {
    No* no = obter_no(tabuleiro, linha, coluna);

    // Esse erro só irá acontecer se o tabuleiro não tiver sido inicializado.
    // Na implementação adequada, é impossível, mas é boa verificação por segurança.
    if (no == NULL)
        return -1;

    no->possui_bandeira = 0;

    return 0;
}