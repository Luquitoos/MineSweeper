#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <time.h>
#include <locale.h>

#include "../jogo/tabuleiro.h"
#include "../jogo/jogo.h"

#ifdef _WIN32
    #include <windows.h>
#endif

/**
 * Inicializa e configura o terminal para exibir corretamente os caracteres e o layout.
 */
void configurar_terminal();

/**
 * Move o cursor para o início e limpa a tela.
 */
void limpar_tela();

/**
 * Exibe um quadrado colorido no terminal, com fundo e texto coloridos.
 */
void desenhar_quadrado();

/**
 * Exibe uma bandeira colorida no terminal.
 */
void desenhar_bandeira();

/**
 * Aguarda um tempo determinado em milissegundos.
 */
void delay_ms(int milliseconds);

/**
 * Exibe um quadrado representando um espaço vazio ou numérico, dependendo da quantidade de minas próximas.
 */
void quadrados_espaco_vazio_ou_numerico(int num_minas_proximas);

/**
 * Exibe uma animação de explosão de mina.
 */
void mina_explosao_animada();

/**
 * Imprime as coordenadas superiores do tabuleiro.
 */
void imprimir_coordenadas_superiores(int colunas);

/**
 * Imprime a linha horizontal que separa as linhas do tabuleiro.
 */
void imprimir_linha_horizontal(int colunas);

/**
 * Imprime a linha intermediária do tabuleiro.
 */
void imprimir_linha_intermediaria(int colunas);

/**
 * Imprime a linha final do tabuleiro.
 */
void imprimir_linha_final(int colunas);

/**
 * Exibe a cabeça do jogo, incluindo título e elementos iniciais.
 */
void cabeca_jogo();

/**
 * Desenha o campo do jogo com base no estado atual do tabuleiro.
 */
void desenhar_campo(Tabuleiro* tabuleiro);

/**
 * Imprime o título do jogo na tela.
 */
void imprimir_titulo();

/**
 * Imprime os créditos do jogo.
 */
void imprimir_creditos();

/**
 * Exibe a tela de início do jogo.
 */
void imprimir_start_game();

/**
 * Exibe o menu de seleção de dimensões do tabuleiro.
 */
void menu_dimensoes();

/**
 * Exibe o menu de seleção de quantidade de minas, com base nas dimensões do tabuleiro.
 */
void menu_quantidade_minas(int linhas, int colunas, int *maxima);

/**
 * Exibe o menu principal do jogo.
 * Se 'jogoAtual' for NULL, apresenta o menu para criação de um novo jogo;
 * caso contrário, exibe o menu de ações disponíveis.
 */
void executar_menu(Jogo *jogoAtual);

/**
 * Exibe o menu para iniciar um novo jogo.
 */
void menu_novo_jogo(Jogo* jogoAtual);

#endif