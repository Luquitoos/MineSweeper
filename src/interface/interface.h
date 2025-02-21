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
 * Formatação princiaplmente.
 */
void configurar_terminal();

/**
 * Move o cursor para início e limpa tela
 * */
void limpar_tela();

/**
 * Exibe um quadrado colorido no terminal, com fundo e texto coloridos.
 * O quadrado é representado por um emoji 🔲, com cor de fundo 154 e cor de texto 24.
 * Após exibir o quadrado, as configurações de cor do terminal são resetadas.
 */
void quadrados();

/**
 * Exibe uma bandeira colorida no terminal, representada por um emoji 🚩.
 * A bandeira tem fundo colorido com a cor 154 e texto (emoji) com a cor 196.
 * Após exibir a bandeira, as configurações de cor do terminal são resetadas.
 */
void desenhar_bandeira();

void delay_ms(int milliseconds);
void quadrados_espaco_vazio_ou_numerico(int num_minas_proximas);
void mina_explosao_animada();
void imprimir_coordenadas_superiores(int colunas);
void imprimir_linha_horizontal(int colunas);
void imprimir_linha_intermediaria(int colunas);
void imprimir_linha_final(int colunas);
void cabeca_jogo();


void desenhar_campo(Tabuleiro* tabuleiro);
void imprimir_titulo();
void imprimir_creditos();
void imprimir_start_game();
void menu_dimensoes();
void menu_quantidade_minas(int linhas, int colunas, int *maxima);

/**
 * Exibe o menu principal do jogo.
 *
 * Se o parâmetro 'jogoAtual' for NULL, apresenta o menu para criação de um novo jogo;
 * caso contrário, exibe o menu de ações disponíveis.
 *
 * @param jogoAtual Ponteiro para a estrutura do jogo. Um valor NULL indica que não há jogo em andamento.
 */
void executar_menu(Jogo *jogoAtual);
void menu_novo_jogo(Jogo* jogoAtual);

#endif