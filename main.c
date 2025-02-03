#include <stdlib.h>
#include <stdio.h>

#include "src/interface/interface.h"
#include "src/jogo/jogo.h"

int main () {    
    imprimir_titulo();
    imprimir_creditos();
    executar_menu();
    return EXIT_SUCCESS;
}