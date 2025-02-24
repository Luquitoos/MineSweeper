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
    printf("\033[H\033[J");
}

void desenhar_quadrado() {
    printf("\033[48;5;154;38;5;24m🔲 \033[0m");
}

void desenhar_bandeira() {
    printf("\033[48;5;154;38;5;196m🚩 \033[0m"); /*mostra o quadrado de Bandeira */
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

/**
 * Desenha o campo do jogo Campo Minado, exibindo coordenadas, células e bordas.
 * Cada célula pode conter uma bandeira, um número, um espaço vazio ou uma mina explosiva.
 * A interface utiliza códigos ANSI para cores e animações.
 *
 * @param tabuleiro Ponteiro para a estrutura do tabuleiro contendo a matriz de células.
 */
void desenhar_campo(Tabuleiro* tabuleiro) {  
    configurar_terminal();
    limpar_tela();
    cabeca_jogo();

    int linhas = tabuleiro->altura, colunas = tabuleiro->largura;

    imprimir_coordenadas_superiores(colunas);
    imprimir_linha_horizontal(colunas);

    for (int i = 0; i < linhas; i++) {
        printf("\033[38;5;255m %c \033[0m\033[38;5;27m║\033[0m", 'A' + i);

        for (int j = 0; j < colunas; j++) {
            No* no = obter_no(tabuleiro, 'A' + i, j + 1);

            if (no->possui_bandeira) {
                desenhar_bandeira();
            } else if (no->revelado) {
                no->bomba ? mina_explosao_animada() : quadrados_espaco_vazio_ou_numerico(no->total_minas_adjacentes);
            } else {
                desenhar_quadrado();
            }

            printf(j < colunas - 1 ? "\033[38;5;94m║\033[0m" : "\033[38;5;27m║\033[0m");
        }

        printf("\n");
        if (i < linhas - 1) imprimir_linha_intermediaria(colunas);
    }
    
    imprimir_linha_final(colunas);
}

/**
 * Executa o menu para um novo jogo,
 * valida as entradas recebidas e
 * atribui valores ao jogo.
 * @param jogoAtual O ponteiro para a struct 'Jogo' que será inicializado.
 */
void menu_novo_jogo(Jogo* jogoAtual) {
    int opcao = 0, dimensao = 0, minas = 0, linhas = 0, colunas = 0;
    int maxima = 7;
    char input[10];
    int leitura_valida = 0;
    int conversao = 0;

    imprimir_titulo();
    imprimir_creditos();
    imprimir_start_game();

    // Reseta o buffer de entrada antes de ler.
    fflush(stdin);

    // Verifica se a ação é válida.
    if (!(fgets(input, sizeof(input), stdin) && sscanf(input, "%d", &opcao) == 1 && opcao == 1)) {
        printf("\033[38;5;196mOpção inválida! Digite 1 para iniciar o jogo.\033[0m\n");
        delay_ms(2000);
        executar_menu(jogoAtual);
        return;
    }

    // Caso a entrada seja válida, executa o código abaixo.
    while (1) {
        menu_dimensoes();

        fflush(stdin);
        if (fgets(input, sizeof(input), stdin) && sscanf(input, "%dx%d", &linhas, &colunas) == 2 && 
            linhas >= 5 && colunas >= 5 && linhas <= 26 && colunas <= 40)
            // Com while (1), a condição de parada fica centralizada dentro do loop, tornando o código mais legível.
            // (Entendo que o professor não seja fã do break)
            break;

        printf("\033[38;5;196mFormato inválido. Use o formato Linha x Coluna (exemplo: 5x5)\033[0m\n");
        delay_ms(2000);
        limpar_tela();
    }

    printf("\033[38;5;196mCaso tenha inserido uma dimensão muito grande, recomendo deixar em tela cheia.\033[0m\n");
    printf("\033[0m\n");
    printf("\033[38;5;196m● Se o campo for grande e aparecer antes de por em tela cheia:\033[0m\n");
    printf("\033[38;5;196m● Ajuste o tamanho da janela do terminal com o mouse e depois ative a tela cheia.\033[0m\n");
    printf("\033[38;5;196m Aguarde......\033[0m\n");
    delay_ms(5000);

    while (1) {
        menu_quantidade_minas(linhas, colunas, &maxima);

        fflush(stdin);
        if (fgets(input, sizeof(input), stdin) && sscanf(input, "%d", &minas) == 1 && minas >= 7 && minas <= maxima)
            break;

        printf("\033[38;5;196mNúmero inválido! Digite um número entre 7 e %d.\033[0m\n", maxima);
        delay_ms(1000);
        limpar_tela();
    }

    jogoAtual = iniciar_jogo(colunas, linhas, minas);

    // Retorna para a função do menu.
    executar_menu(jogoAtual);
};

/**
 * Executa o menu de ações.
 * @param jogoAtual O jogo em questão.
 */
void menu_acao(Jogo* jogoAtual) {
    int retorno;

    Tabuleiro* tabuleiro = jogoAtual->tabuleiro;
    int largura = jogoAtual->largura;
    int altura = jogoAtual->altura;

    desenhar_campo(tabuleiro);
    while (jogoAtual->jogo_ativo) {
        retorno = processar_acao(jogoAtual);
        if (retorno == 1) {
            desenhar_campo(tabuleiro);
        } else {
            exibir_erro(retorno);
        }
    }

    finalizar_jogo(jogoAtual);
};

/**
 * Executa diferentes tarefas, considerando que um jogo
 * que deve ser inicializado ou que já foi.
 * @param jogoAtual O jogo em questão.
 */
void executar_menu(Jogo* jogoAtual) {
    // Inicialização
    configurar_terminal();
    limpar_tela();
        
    if (jogoAtual == NULL) {
        menu_novo_jogo(jogoAtual);
    } else {
        menu_acao(jogoAtual);
    }
}
