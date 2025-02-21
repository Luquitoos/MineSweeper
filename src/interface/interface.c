#include <stdio.h>
#include <time.h>
#include <locale.h>

#include "interface.h"

#ifdef _WIN32
    #include <windows.h> 
#endif

void configurar_terminal() {
    setlocale(LC_ALL, "en_US.UTF-8");  /*Configura a Linux e Mac para UTF-8, que suporta os simbolos*/

#ifdef _WIN32
    SetConsoleOutputCP(65001);  /*Configura o terminal do Windows para UTF-8, que suporta os simbolos*/
#endif
}

void limpar_tela() {
    printf("\033[H\033[J");  /*limpa tela*/
}

void quadrados() {
    printf("\033[48;5;154;38;5;24m🔲 \033[0m"); /*mostra o quadrado do campo*/
}

void desenhar_bandeira() {
    printf("\033[48;5;154;38;5;196m🚩 \033[0m"); /*mostra o quadrado de Bandeira */
}

void delay_ms(int milliseconds) { /*Função auxiliar para a animação da função mina_explosiva_animada*/
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void quadrados_espaco_vazio_ou_numerico(int num_minas_proximas) { /*Cria o quadrado clicado sem mina, dependendo do numero de minas proximas ele vai ser vazio ou vai ter um numero de minas proximas*/
    if (num_minas_proximas == 0) {
        printf("\033[48;5;58m   \033[0m");
    } else {    
        int cor;
        switch(num_minas_proximas) {
            case 1: cor = 81;  break;  /*Azul*/
            case 2: cor = 46;  break;  /* Verde */
            case 3: cor = 214; break;  /* Vermelho */
            case 4: cor = 57;  break;  /* Azul escuro */
            case 5: cor = 124; break;  /* Vermelho escuro */
            case 6: cor = 37;  break;  /* Ciano */
            case 7: cor = 53;  break;  /* Roxo */
            case 8: cor = 240; break;  /* Cinza escuro */
            default: cor = 15;         /* Branco (caso padrão) */  
        }
        printf("\033[48;5;58;38;5;%dm %d \033[0m", cor, num_minas_proximas);
    }
}

void mina_explosao_animada() { /*Função da Mina (é uma animação), mostra a bomba no campo*/

    printf("\033[48;5;58m💣 \033[0m");
    fflush(stdout);
    delay_ms(500); 

    printf("\b\b\b\033[48;5;58m💥 \033[0m");
    fflush(stdout);
}


void imprimir_coordenadas_superiores(int colunas) { /*Imprime as coodernadas de coluna, que são números, na parte superior do campo (FUNÇÃO AUXILIAR DE DESENHAR CAMPO)*/
    printf("   "); 
    for (int i = 0; i < colunas; i++) {
        printf("\033[38;5;255m %2d \033[0m", i + 1);
    }
    printf("\n");
}

void imprimir_linha_horizontal(int colunas) { /*Imprime as linhas que cortam o campo (FUNÇÃO AUXILIAR DE DESENHAR CAMPO)*/
    printf("   \033[38;5;27m╔"); 
    for (int i = 0; i < colunas; i++) {
        printf("═══"); 
        if (i < colunas - 1) printf("╦"); 
    }
    printf("╗\033[0m\n");
}

void imprimir_linha_intermediaria(int colunas) { /*Cria bordas internas (FUNÇÃO AUXILIAR DE DESENHAR CAMPO)*/
    printf("   \033[38;5;27m╠");
    for (int i = 0; i < colunas; i++) {
        printf("\033[38;5;94m═══"); 
        if (i < colunas - 1) printf("╬");
    }
    printf("\033[38;5;27m╣\033[0m\n");
}

void imprimir_linha_final(int colunas) { /*Funçao auxiliar do desenhar campo que faz a ultima linha da borda ser azul*/
    printf("   \033[38;5;27m╚");
    for (int i = 0; i < colunas; i++) {
        printf("═══");
        if (i < colunas - 1) printf("╩");
    }
    printf("╝\033[0m\n");
}

void cabeca_jogo() {
    printf("\033[38;5;226m");
    printf("\n");
    printf("     ██╗  ██╗ █████╗ ██╗   ██╗███████╗    ███████╗██╗   ██╗███╗   ██╗   ╔═══════════════════════════╗\n");
    printf("     ██║  ██║██╔══██╗██║   ██║██╔════╝    ██╔════╝██║   ██║████╗  ██║   ║ Open: [Letter][Number]    ║\n");
    printf("     ███████║███████║██║   ██║█████╗      █████╗  ██║   ██║██╔██╗ ██║   ║ Flag: #[Letter][Number]   ║\n");
    printf("     ██╔══██║██╔══██║╚██╗ ██╔╝██╔══╝      ██╔══╝  ██║   ██║██║╚██╗██║   ║ Unflag: ![Letter][Number] ║\n");
    printf("     ██║  ██║██║  ██║ ╚████╔╝ ███████╗    ██║     ╚██████╔╝██║ ╚████║   ║ Tip: Press Enter          ║\n");
    printf("     ╚═╝  ╚═╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝   ╚═══════════════════════════╝\n");
    printf("\033[0m\n");
}

void desenhar_campo(Tabuleiro* tabuleiro) { /*Cria o Campo Minado (A interface dele)*/
    configurar_terminal();
    limpar_tela();
    cabeca_jogo();
    int linhas, colunas;
    linhas = tabuleiro->altura;
    colunas = tabuleiro->largura;
    
    imprimir_coordenadas_superiores(colunas);
    
    imprimir_linha_horizontal(colunas);
    
    for (int i = 0; i < linhas; i++) {

        printf("\033[38;5;255m %c \033[0m", 'A' + i);
        
        printf("\033[38;5;27m║\033[0m"); 
        for (int j = 0; j < colunas; j++) {
            No* no = obter_no(tabuleiro, 'A' + i, j + 1);

            if(no->possui_bandeira == 1) {
                desenhar_bandeira();
            } else if (no->revelado == 1){
                if(no->bomba == 1) {
                    mina_explosao_animada();
                } else if (no->total_minas_adjacentes >= 0) {
                    quadrados_espaco_vazio_ou_numerico(no->total_minas_adjacentes);
                }
            } else {
                quadrados();
            }

            if (j < colunas - 1) {
                printf("\033[38;5;94m║\033[0m"); 
            } else {
                printf("\033[38;5;27m║\033[0m"); 
            }
        }
        printf("\n");
        
        if (i < linhas - 1) {
            imprimir_linha_intermediaria(colunas);
        }
    }
    imprimir_linha_final(colunas);
}

void imprimir_titulo() {
    printf("\033[38;5;226m");
    printf("\n");
    printf("     ███╗   ███╗██╗███╗   ██╗███████╗███████╗██╗    ██╗███████╗███████╗██████╗ ███████╗██████╗\n");
    printf("     ████╗ ████║██║████╗  ██║██╔════╝██╔════╝██║    ██║██╔════╝██╔════╝██╔══██╗██╔═══ ╝██╔══██╗\n");
    printf("     ██╔████╔██║██║██╔██╗ ██║█████╗  ███████╗██║ █╗ ██║█████╗  █████╗  ██████╔╝█████╗  ██████╔╝\n");
    printf("     ██║╚██╔╝██║██║██║╚██╗██║██╔══╝  ╚════██║██║███╗██║██╔══╝  ██╔══╝  ██╔═══╝ ██╔══╝  ██╔══██╗\n");
    printf("     ██║ ╚═╝ ██║██║██║ ╚████║███████╗███████║╚███╔███╔╝███████╗███████╗██║     ███████╗██║  ██║\n");
    printf("     ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝╚══════╝ ╚══╝╚══╝ ╚══════╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝\n");
    printf("                                                UFC\n");
    printf("\033[0m\n");
}

void imprimir_creditos() {
    printf("\033[38;5;27m");
    printf("                                ╔════════════════════════════════╗\n");
    printf("                                ║   by Lucas, Marcos and Felipe  ║\n");
    printf("                                ╚════════════════════════════════╝\n");
    printf("\033[0m\n");
}

void imprimir_start_game() {
    printf("\033[38;5;46m");
    printf("                                ╔════════════════════════════════╗\n");
    printf("                                ║         ➥ Start Game           ║\n");
    printf("                                ║       Digite 1 para jogar      ║\n");
    printf("                                ╚════════════════════════════════╝\n");
    printf("\033[0m\n");
}

void menu_dimensoes() {
    limpar_tela();
    printf("\033[38;5;27m");
    printf("\n                  ╔═══════════════════════════════════════════════════════════╗\n");
    printf("                  ║  Digite a Dimensão do Campo no Formato (Linha x Coluna):  ║\n");
    printf("                  ╚═══════════════════════════════════════════════════════════╝\n\n");
    printf("\033[0m");
}

void menu_quantidade_minas(int linhas, int colunas, int *maxima) {
    limpar_tela();
    
    *maxima = calcular_maximo_minas(colunas, linhas);

    printf("\033[38;5;46m"); 
    printf("\n                                ╔══════════════════════════════════╗\n");
    printf("                                ║ Digite o número de minas (7-%d): ║\n", *maxima);
    printf("                                ╚══════════════════════════════════╝\n");
    printf("\033[0m\n");
}

void menu_novo_jogo(Jogo* jogoAtual) 
{
    int opcao = 0, dimensao = 0, minas = 0, linhas = 0, colunas = 0;
    int maxima = 7;
    char input[10];
    int leitura_valida = 0;
    int conversao = 0;

    imprimir_titulo();
    imprimir_creditos();
    imprimir_start_game();

    fflush(stdin); /*Limpa o buffer de entrada antes de ler*/

    if (fgets(input, sizeof(input), stdin) != NULL)
    {                                                 /*Lê a entrada como string*/
        leitura_valida = sscanf(input, "%d", &opcao); /*Tenta converter a entrada no formato desejado retornando a quantidade do formato desejado*/
    }

    /* Se a conversão não resultou em 1 número ou os número é diferente de 1 */
    if (leitura_valida != 1 || opcao != 1) {
        printf("\033[38;5;196mOpção inválida! Digite 1 para iniciar o jogo.\033[0m\n"); /*Imprime erro*/
        delay_ms(2000);
        executar_menu(NULL);
        return;                                                   /*Pequeno delay para a mensagem ser visível*/
    }

    // Caso a entrada seja válida, executa o código abaixo.
    do
    {
        menu_dimensoes();

        fflush(stdin); /*Limpa o buffer de entrada antes de ler*/

        if (fgets(input, sizeof(input), stdin) != NULL)
        {                                                          /*Lê a entrada como string*/
            conversao = sscanf(input, "%dx%d", &linhas, &colunas); /*Tenta converter a entrada no formato desejado retornando a quantidade de numeros no formato desejado*/
        }

        limpar_tela();

        /* Se a conversão não resultou em 2 números ou os números não estão no formato desejado */
        if (conversao != 2)
        {
            printf("\033[38;5;196mFormato inválido. Use o formato LinhaxColuna (exemplo: 5x5)\033[0m\n"); /*Imprime erro*/
            delay_ms(2000);                                                                                 /*Pequeno delay para a mensagem ser visível*/
        }

    } while (linhas < 5 || colunas < 5 || linhas > 26 || colunas > 40);

    printf("\033[38;5;196mCaso tenha inserido uma dimensão muito grande, recomendo deixar em tela cheia.\033[0m\n");
    printf("\033[0m\n");
    printf("\033[38;5;196m● Se o campo for grande e aparecer antes de por em tela cheia:\033[0m\n");
    printf("\033[38;5;196m    ->Ajuste o tamanho da janela do terminal com o mouse e depois ative a tela cheia.\033[0m\n");
    printf("\033[38;5;196m                      Aguarde......\033[0m\n");
    delay_ms(6000);

    do
    {
        menu_quantidade_minas(linhas, colunas, &maxima);

        fflush(stdin); /* Limpa o buffer de entrada antes de ler*/
        if (fgets(input, sizeof(input), stdin) != NULL)
        {                                                 /*Lê a entrada como string*/
            leitura_valida = sscanf(input, "%d", &minas); /*Tenta converter a entrada no formato desejado retornando a quantidade do formato desejado*/
        }

        limpar_tela();

        /* Se a conversão não resultou em 1 número ou os números não estão no intervalo pedido */
        if (leitura_valida != 1 || minas < 7 || minas > maxima)
        {
            printf("\033[38;5;196mNúmero inválido! Digite um número entre 7 e %d.\033[0m\n", maxima); /*Imprime erro*/
            delay_ms(1000);
        }
    } while (minas < 7 || minas > maxima);

    jogoAtual = iniciar_jogo(colunas, linhas, minas);
    executar_menu(jogoAtual);
};

void menu_acao(Jogo* jogoAtual) {
    int acao;

    Tabuleiro* tabuleiro = jogoAtual->tabuleiro;
    int largura = jogoAtual->largura;
    int altura = jogoAtual->altura;

    desenhar_campo(tabuleiro);
    acao = 0;
    while(acao != -1) {
        acao = processar_acao(jogoAtual, acao);
        desenhar_campo(tabuleiro);
    }
    finalizar_jogo(jogoAtual);
};

void executar_menu(Jogo* jogoAtual) {
    configurar_terminal();
    limpar_tela();
        
    if (jogoAtual == NULL) {
        menu_novo_jogo(jogoAtual);
    } else {
        menu_acao(jogoAtual);
    }
}
