#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#include <time.h>

#include "jogo.h"
#include "tabuleiro.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void delay_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void exibir_erro(int codigo_erro) {
    switch (codigo_erro) {
        case -1:
            printf("\033[38;5;196m");
            printf("                       ╔══════════════════════════════════════════╗\n");
            printf("                       ║   Ocorreu um erro ao executar a jogada.  ║\n");
            printf("                       ╚══════════════════════════════════════════╝\n");
            printf("\033[0m\n");
            break;
        case 1:
            printf("\033[38;5;196m");
            printf("                       ╔═══════════════════════════════════════════════════╗\n");
            printf("                       ║ Erro ao alocar memória, por favor tente novamente.║\n");
            printf("                       ╚═══════════════════════════════════════════════════╝\n");
            printf("\033[0m\n");
            break;
        case 2:
            printf("\033[38;5;196m");
            printf("                   ╔═══════════════════════════════════════════════════════════════════╗\n");
            printf("                   ║ A posição inserida não representa uma posição válida no tabuleiro.║\n");
            printf("                   ╚═══════════════════════════════════════════════════════════════════╝\n");
            printf("\033[0m\n");
            break;
        case 3:
            printf("\033[38;5;196m");
            printf("          ╔════════════════════════════════════════════════════════════════════════════╗\n");
            printf("          ║ A quantidade de bombas inseridas é maior do que limite máximo do tabuleiro.║\n");
            printf("          ╚════════════════════════════════════════════════════════════════════════════╝\n");
            printf("\033[0m\n");
            break;
        case 4:
            printf("\033[38;5;196m");
            printf("                       ╔═════════════════════════════════════════╗\n");
            printf("                       ║    O campo inserido já está revelado.   ║\n");
            printf("                       ╚═════════════════════════════════════════╝\n");
            printf("\033[0m\n");
            break;
        default:
            printf("\033[38;5;196m");
            printf("                       ╔═══════════════════════════════════════╗\n");
            printf("                       ║     A entrada inserida é inválida.    ║\n");
            printf("                       ╚═══════════════════════════════════════╝\n");
            printf("\033[0m\n");
            break;
    }

    delay_ms(1000);
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

/**
 * Processa a entrada do jogador e executa a ação correspondente.
 * 
 * Retorna 1 em caso de sucesso, -1 se o jogo terminar, ou 0 para entrada inválida.
 */
int processar_acao(Jogo* jogo) {
    char entrada[8], letra;
    int num, resultado;

    printf("\033[38;5;255mRealize sua ação: \033[0m");
    fflush(stdout);

    // Captura a entrada do usuário
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0; // Entrada inválida
    }

    // Remove o '\n' final da string, se existir
    char *newline = strchr(entrada, '\n');
    if (newline) *newline = 0;

    // Entrada vazia (Enter) -> exibir dica
    if (entrada[0] == '\0') {
        exibir_dica(jogo->tabuleiro);
        return 1;
    }

    // Comando de bandeira: '#[letra][número]' ou '![letra][número]'
    if ((entrada[0] == '#' || entrada[0] == '!') && sscanf(entrada + 1, " %c%d", &letra, &num) == 2) {
        if (letra >= 'a' && letra <= 'z') letra -= 32; // Converte para maiúscula

        if (letra >= 'A' && letra < ('A' + jogo->altura) && num > 0 && num <= jogo->largura) {
            resultado = (entrada[0] == '#') ? definir_bandeira(jogo->tabuleiro, letra, num)
                                            : remover_bandeira(jogo->tabuleiro, letra, num);
            return resultado == 0 ? 1 : 0;
        }
        return 0;
    }

    // Jogada normal: '[letra][número]'
    if (sscanf(entrada, " %c%d", &letra, &num) == 2) {
        if (letra >= 'a' && letra <= 'z') letra -= 32; // Converte para maiúscula

        if (letra >= 'A' && letra < ('A' + jogo->altura) && num > 0 && num <= jogo->largura) {
            resultado = revelar_campo(jogo->tabuleiro, jogo->quantidadeJogadas, letra, num, 0);
            
            if (resultado == 0) {
                jogo->quantidadeJogadas++;
            }

            if (resultado == 2) {
                exibir_bombas(jogo->tabuleiro);
                jogo->jogo_ativo = 0;
                return 1;
            }

            if (jogo->jogo_ativo && vitoria(jogo->tabuleiro)) {
                jogo->jogo_ativo = 0;
                return 1;
            }

            return resultado == 0 || resultado == 3 ? 1 : 0;
        }
    }

    return 0; // Entrada inválida
}

void exibir_dica(Tabuleiro* tabuleiro) {
    char* dica = obter_dica(tabuleiro);

    if (!dica) {
        printf("\033[38;5;226m");
        printf("\n");
        printf("                     ╔═════════════════════════════════════════════════════════════╗\n");
        printf("                     ║        A primeira dica é você iniciar o tabuleiro...        ║\n");
        printf("                     ╚═════════════════════════════════════════════════════════════╝\n");
    } else {
        printf("\033[38;5;46m");
        printf("                       ╔═══════════════════════════════════════════════════╗\n");
        printf("                       ║        Que tal você tentar a posição '%s'?        ║\n", dica);
        printf("                       ╚═══════════════════════════════════════════════════╝\n");
        printf("\033[0m\n");
    }

    delay_ms(2000);
}

void finalizar_jogo(Jogo* jogo) {
    if (!jogo) return;

    if (vitoria(jogo->tabuleiro)) {
        exibir_vitoria(jogo);
    } else {
        printf("\033[38;5;196m");
        printf("                       ╔══════════════════════════════════════╗\n");
        printf("                       ║        Você acertou uma mina!        ║\n");
        printf("                       ╚══════════════════════════════════════╝\n");
        printf("\033[0m\n");
    }

    // Libera memória do tabuleiro
    if (jogo->tabuleiro) {
        for (int i = 0; i < jogo->altura; i++) {
            free(jogo->tabuleiro->matriz[i]);
        }
        free(jogo->tabuleiro->matriz);
        free(jogo->tabuleiro);
    }

    free(jogo);
}


void exibir_vitoria(Jogo* jogo) {
    exibir_bombas(jogo->tabuleiro); // Mostra todo o campo
    printf("\033[38;5;46m");
    printf("                       ╔══════════════════════════════════════════╗\n");
    printf("                       ║           VOCÊ VENCEU!!!                 ║\n");
    printf("                       ║     Parabéns, você é um caba bom! 🏆     ║\n");
    printf("                       ╚══════════════════════════════════════════╝\n");
    printf("\033[0m\n");
}