#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <time.h>
#include <locale.h>

#ifdef _WIN32
    #include <windows.h>
#endif

void configurar_terminal();
void limpar_tela();
void quadrados();
void desenhar_bandeira();
void delay_ms(int milliseconds);
void quadrados_espaco_vazio_ou_numerico(int num_minas_proximas);
void mina_explosao_animada();
void imprimir_coordenadas_superiores(int colunas);
void imprimir_linha_horizontal(int colunas);
void imprimir_linha_intermediaria(int colunas);
void imprimir_linha_final(int colunas);
void cabeca_jogo();
void desenhar_campo(int linhas, int colunas);
void imprimir_titulo();
void imprimir_creditos();
void imprimir_start_game();
void imprimir_opcao_dimensao(int numero, const char* dimensao);
void menu_dimensoes();
void menu_quantidade_minas();
void executar_menu();

#endif