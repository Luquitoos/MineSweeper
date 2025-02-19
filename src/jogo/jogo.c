#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "jogo.h"
#include "tabuleiro.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void exibir_erro(int codigo_erro) {
    switch (codigo_erro) {
        case -1:
            printf("Ocorreu um erro ao executar a jogada.");
            break;
        case 1:
            printf("Erro ao alocar memória, por favor tente novamente.\n");
            break;
        case 2:
            printf("A posição inserida não representa uma posição válida no tabuleiro.\n");
            break;
        case 3:
            printf("A quantidade de bombas inseridas é maior do que limite máximo do tabuleiro.");
            break;
        case 4:
            printf("O campo inserido já está revelado.");
            break;
        default:
            printf("Ocorreu um erro desconhecido.\n");
            break;
    }
}

int calcular_maximo_minas(int largura, int altura) {
    return MAX(7, (int) floor((largura * altura) / 5.0));
}

Jogo* iniciar_jogo(
    int largura,
    int altura,
    int quantidadeMinas
) {
    Jogo* novo_jogo = (Jogo*) malloc(sizeof(Jogo));
    if (novo_jogo == NULL) {
        exibir_erro(1);
        return NULL;
    }

    int maxMinas = calcular_maximo_minas(largura, altura);
    if (quantidadeMinas > maxMinas) {
        exibir_erro(3);
        free(novo_jogo);
        return NULL;
    }

    novo_jogo->largura = largura;
    novo_jogo->altura = altura;
    novo_jogo->maximoDeMinas = maxMinas;
    novo_jogo->minasRestantes = quantidadeMinas;
    novo_jogo->quantidadeJogadas = 0;
    novo_jogo->jogo_ativo = 1;
    novo_jogo->tabuleiro = iniciar_tabuleiro(largura, altura, quantidadeMinas);

    return novo_jogo;
}

int processar_acao(Jogo* jogo, int acao) {
    int num, tamanho;
    char letra, jogada;

    printf("Realize sua ação: \n");
    scanf(" %c", &jogada);
    if(jogada == '#') {
        scanf(" %c %d", &letra, &num);
        definir_bandeira(jogo->tabuleiro, letra, num);
    } else if(jogada == '!') {
        //desmarcar
        scanf(" %c %d",&letra, &num);
        printf("desmarcar");
    } else {
        //abrir
        letra = jogada;
        scanf(" %d", &num);
        revelar_campo(jogo->tabuleiro, 0, letra, num);
        //função para finalizar
    }

    return 1;
}

void finalizar_jogo(Jogo* jogo, int causa) {
    free(jogo->tabuleiro);
    free(jogo); 
}