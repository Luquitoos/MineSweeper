#include <stdio.h>
#include <stdlib.h>

#include "jogo.h"
#include "tabuleiro.h"

void exibir_erro(int codigo_erro) {
    switch (codigo_erro) {
        case 1:
            printf("Erro ao alocar memória, por favor tente novamente.\n");
            break;
        case 2:
            printf("A posição inserida não representa uma posição válida no tabuleiro.\n");
            break;
        default:
            printf("Ocorreu um erro desconhecido.\n");
            break;
    }
}

int calcular_maximo_minas(
    int largura,
    int altura
) {
    return (largura * altura) / 5;
}

Jogo* iniciar_jogo(
    int largura,
    int altura
) {
    Jogo* novo_jogo = (Jogo*) malloc(sizeof(Jogo));
    if (novo_jogo == NULL) {
        exibir_erro(1)
        exit(1);
    }

    novo_jogo->largura = largura;
    novo_jogo->altura = altura;
    novo_jogo->maximoDeMinas = calcular_maximo_minas(largura, altura);
    novo_jogo->minasRestantes = calcular_maximo_minas(largura, altura);
    novo_jogo->actions = 0;
    novo_jogo->jogo_ativo = 1;
    novo_jogo->tabuleiro = iniciar_tabuleiro(largura, altura);

    return novo_jogo;
}

void processar_acao(Jogo* jogo, int acao) {
    // ...
}

void finalizar_jogo(Jogo* jogo, int causa) {
    free(jogo->tabuleiro);
    free(jogo);
}