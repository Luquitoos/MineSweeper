#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "jogo.h"
#include "tabuleiro.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

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
            printf("                       ╔══════════════════════════════════════╗\n");
            printf("                       ║     Ocorreu um erro desconhecido.    ║\n");
            printf("                       ╚══════════════════════════════════════╝\n");
            printf("\033[0m\n");
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
    char letra, jogada, entrada[20]; // Aumentei o tamanho do buffer
    int num, resultado;

    printf("\033[38;5;255mRealize sua ação: \033[0m");
    fflush(stdout);

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return acao;
    }

    // Remove o '\n' do final da string se existir
    char *newline = strchr(entrada, '\n');
    if (newline) *newline = 0;

    // Primeira jogada
    if (acao == 0) {
        if (sscanf(entrada, " %c%d", &letra, &num) == 2) {
            if (letra >= 'a' && letra <= 'z') {
                letra = letra - 'a' + 'A';
            }

            if ((letra >= 'A' && letra < 'A' + jogo->altura) &&
                num > 0 && num <= jogo->largura) {
                resultado = revelar_campo(jogo->tabuleiro, &acao, letra, num, 0);

                // Se acertar uma mina, fim de jogo
                if (resultado == 2) {
                    jogo->jogo_ativo = 0; // Marca o jogo como encerrado
                    exibir_bombas(jogo->tabuleiro);
                    return -1;
                }

                // 🏆 Só verifica vitória se o jogo ainda estiver ativo
                if (jogo->jogo_ativo && vitoria(jogo->tabuleiro)) {
                    exibir_vitoria(jogo);
                    return -1;
                }

                return acao + 1;
            }
            return acao;
        }
        return acao;
    }

    // Tenta ler comando de bandeira primeiro (#) ou remover bandeira (!)
    char comando[20];
    if (sscanf(entrada, "%s", comando) == 1) {
        if (comando[0] == '#' || comando[0] == '!') {
            jogada = comando[0];
            if (sscanf(comando + 1, "%c%d", &letra, &num) == 2) {
                if (letra >= 'a' && letra <= 'z') {
                    letra = letra - 'a' + 'A';
                }

                if ((letra >= 'A' && letra < 'A' + jogo->altura) &&
                    num > 0 && num <= jogo->largura) {
                    if (jogada == '#') {
                        resultado = definir_bandeira(jogo->tabuleiro, letra, num);
                        if (resultado == 0) return acao + 1;
                    }
                    else if (jogada == '!') {
                        resultado = remover_bandeira(jogo->tabuleiro, letra, num);
                        if (resultado == 0) return acao + 1;
                    }
                }
            }
            return acao;
        }
    }

    // Se não for comando de bandeira, tenta ler como jogada normal
    if (sscanf(entrada, " %c%d", &letra, &num) == 2) {
        if (letra >= 'a' && letra <= 'z') {
            letra = letra - 'a' + 'A';
        }

        if ((letra >= 'A' && letra < 'A' + jogo->altura) &&
            num > 0 && num <= jogo->largura) {
            resultado = revelar_campo(jogo->tabuleiro, &acao, letra, num, 0);

            // Se acertar uma mina, fim de jogo
            if (resultado == 2) {
                jogo->jogo_ativo = 0; // Marca o jogo como encerrado
                exibir_bombas(jogo->tabuleiro);
                return -1;
            }

            // Só verifica vitória se o jogo ainda estiver ativo
            if (jogo->jogo_ativo && vitoria(jogo->tabuleiro)) {
                exibir_vitoria(jogo);
                return -1;
            }

            if (resultado == 0) {
                return acao + 1;
            }
            else if (resultado == 3) {
                return acao;
            }
        }
    }

    return acao;
}



void finalizar_jogo(Jogo* jogo) {
    if (!jogo) return;

    // Verifica se o jogador perdeu
    if (jogo->jogo_ativo == 0) {  // Se o jogo foi desativado por acertar uma mina
        exibir_bombas(jogo->tabuleiro);
        printf("\033[38;5;196m");
        printf("                       ╔══════════════════════════════════════╗\n");
        printf("                       ║        Você acertou uma mina!        ║\n");
        printf("                       ╚══════════════════════════════════════╝\n");
        printf("\033[0m\n");
    }
    // Se o jogo ainda estiver ativo, verifica se foi vitória
    else if (vitoria(jogo->tabuleiro)) {
        exibir_vitoria(jogo);
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
    printf("                       ╔══════════════════════════════════════╗\n");
    printf("                       ║           VOCÊ VENCEU!!!             ║\n");
    printf("                       ║      Parabéns, você é caba bom 🏆    ║\n");
    printf("                       ╚══════════════════════════════════════╝\n");
    printf("\033[0m\n");
}