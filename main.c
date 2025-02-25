/*Lucas Magalhães Fontenele Bizeril - 572968:
    Organização do Trabalho, Interface.c, Makefile, reformulação e criação de algumas funções do Jogo.c e Tabuleiro.c, validação e Debug das funções do programa.
  Marcos Vinicius Pereira Araujo - 571042:
    Grande parte das funções do Jogo.c e Tabuleiro.c, foco na Estrutura de Dados
  Felipe Gabriel Lima Florindo - 569760:
    Makefile, reformulação e criação de algumas funções de jogo.c, tabuleiro.c e interface.c.
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h> 
#endif

#include "./src/interface/interface.h"

/**
 * Função principal. Direciona o usuário para a interface.
 */
int main () {
    // Inicializa a Struct do jogo.
    Jogo* novoJogo = NULL;

    executar_menu(novoJogo);

    return EXIT_SUCCESS;
}
