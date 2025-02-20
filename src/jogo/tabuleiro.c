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

    if (!tabuleiro) 
        return NULL;

    // Aloca memória para a matriz de ponteiros para linhas
    tabuleiro->matriz = (No**) malloc(altura * sizeof(No*));
    if (!tabuleiro->matriz) {
        free(tabuleiro);
        return NULL;
    }

    tabuleiro->largura = largura;
    tabuleiro->altura = altura;
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
        printf("Erro ao acessar nó (%c, %d): Índices fora dos limites! (Linhas: %d, Colunas: %d)\n",
            linha, coluna, tabuleiro->altura, tabuleiro->largura);
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
        int coluna = idx % tabuleiro->largura; //observar
        tabuleiro->matriz[linha][coluna].bomba = 1;
    }

    free(indices);
}

int realoca_bomba(Tabuleiro* tabuleiro, char linha_origem, int coluna_origem) {
    int largura, altura;
    int i, j;

    if (!tabuleiro) 
        return 0;

    No* realocar = obter_no(tabuleiro, linha_origem, coluna_origem);
    largura = tabuleiro->largura;
    altura = tabuleiro->altura;

    if (!realocar) {
        printf("Erro: não foi possível obter o nó de origem.\n");
        return 0; // Retorna 0 se o nó de origem não foi encontrado
    }

    for(i = 0; i < altura; i++) {
        for(j = 0; j < largura; j++) {
            No* no = obter_no(tabuleiro, 'A'+ i, j + 1);
            if(no && no->bomba == 0 && realocar != no) {
                no->bomba = 1;
                return 1;  
            }
        }
    }
    printf("Tabuleiro cheio, não foi possível realocar a bomba.\n");
    return 0;
}

// 0 -> sucesso
// os outros códigos de erro estão relacionados com o arquivo 'jogo.c'
/*Quando a função for chamada, deve começar com revelar_campo(tabuleiro, &jogadas_totais, linha, coluna, 0); com o parametro de recursão 0, esse é o controle para ele não contar
como jogada a mais*/
int revelar_campo(Tabuleiro* tabuleiro, int* jogadasTotais, char linha, int coluna, int chamada_recursiva) {
    /*Obtém o nó na posição especificada*/
    No* no = obter_no(tabuleiro, linha, coluna);
    int compare;
 
    /* Verifica se é uma posição válida*/
    if (no == NULL)
        return -1;
    
    /* Verifica se já está revelado*/
    if (no->revelado)
        return 3;
 
    /* Verifica se tem bandeira*/
    if (no->possui_bandeira)
        return 3;

    /* Se for a primeira jogada, distribui as bombas*/
    if (*jogadasTotais == 0) {
        distribuir_bombas(tabuleiro);
        if(no->bomba == 1) {
            no->bomba = 0;
            compare = realoca_bomba(tabuleiro, linha, coluna);
            if(compare == 0) {
                return -1;
            }
        }
    }

    no->revelado = 1;
    if(*jogadasTotais != 0 && no->bomba == 1) {
        return 2;
    }

    /* Calcula quantas bombas existem ao redor*/
    no->total_minas_adjacentes = calcular_minas_adjacentes(tabuleiro, linha, coluna);
    
    /* Se não tiver bombas adjacentes, revela recursivamente os 8 vizinhos*/
    if (no->total_minas_adjacentes == 0) {
        /* Revela diagonal superior esquerda*/
        revelar_campo(tabuleiro, jogadasTotais, linha - 1, coluna - 1, 1);
        /* Revela acima*/
        revelar_campo(tabuleiro, jogadasTotais, linha - 1, coluna, 1);
        /* Revela diagonal superior direita*/
        revelar_campo(tabuleiro, jogadasTotais, linha - 1, coluna + 1, 1);
        /* Revela à esquerda*/
        revelar_campo(tabuleiro, jogadasTotais, linha, coluna - 1, 1);
        /* Revela à direita*/
        revelar_campo(tabuleiro, jogadasTotais, linha, coluna + 1, 1);
        /* Revela diagonal inferior esquerda*/
        revelar_campo(tabuleiro, jogadasTotais, linha + 1, coluna - 1, 1);
        /* Revela abaixo*/
        revelar_campo(tabuleiro, jogadasTotais, linha + 1, coluna, 1);
        /* Revela diagonal inferior direita*/
        revelar_campo(tabuleiro, jogadasTotais, linha + 1, coluna + 1, 1);
    }
 
    /* Incrementa o contador de jogadas apenas se não for uma chamada recursiva*/
    if (!chamada_recursiva) {
        (*jogadasTotais)++;
    }
    
    return 0;
}

void exibir_bombas(Tabuleiro* tabuleiro) {
    int jogadas;
    jogadas = 1;
    // Primeiro calcula as minas adjacentes para todos os campos
    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            No* no = obter_no(tabuleiro, 'A' + i, j + 1);
            if (no) {
                no->total_minas_adjacentes = calcular_minas_adjacentes(tabuleiro, 'A' + i, j + 1);
            }
        }
    }

    // Depois revela todos os campos
    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            No* no = obter_no(tabuleiro, 'A' + i, j + 1);
            if (no) {
                no->revelado = 1;
            }
        }
    }
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