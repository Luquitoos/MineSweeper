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