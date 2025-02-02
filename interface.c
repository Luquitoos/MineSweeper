#include <stdio.h>
#include <time.h>
#include <locale.h>
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
    printf("\033[H\033[J");  /*Move cursor para início e limpa tela*/
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
            case 1: cor = 81;  break;  
            case 2: cor = 46;  break;  
            case 3: cor = 214; break;  
            case 4: cor = 201; break;  
            default: cor = 15;         
        }
        printf("\033[48;5;58;38;5;%dm %d \033[0m", cor, num_minas_proximas);
    }
}

void mina_explosao_animada() { /*Função da Mina (é uma animação), mostra a bomba no campo*/

    printf("\033[48;5;58m💣 \033[0m");
    fflush(stdout);
    delay_ms(700); 

    printf("\b\b\b\033[48;5;58m💥\033[0m");
    fflush(stdout);
}


void imprimir_coordenadas_superiores(int colunas) { /*Imprime as coodernadas de coluna, que são números, na parte superior do campo (FUNÇÃO AUXILIAR DE DESENHAR CAMPO)*/
    printf("   "); 
    for (int i = 0; i < colunas; i++) {
        printf("\033[38;5;255m %2d \033[0m", i + 1);
    }
    printf("\n");
}

void imprimir_linha_horizontal(int colunas) { /*Imprime as coodernadas de linha, que são as Letras, na parte esquerda do campo do campo (FUNÇÃO AUXILIAR DE DESENHAR CAMPO)*/
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
    printf("     ██╗  ██╗ █████╗ ██╗   ██╗███████╗    ███████╗██╗   ██╗███╗   ██╗  \n");
    printf("     ██║  ██║██╔══██╗██║   ██║██╔════╝    ██╔════╝██║   ██║████╗  ██║ \n");
    printf("     ███████║███████║██║   ██║█████╗      █████╗  ██║   ██║██╔██╗ ██║ \n");
    printf("     ██╔══██║██╔══██║╚██╗ ██╔╝██╔══╝      ██╔══╝  ██║   ██║██║╚██╗██║  \n");
    printf("     ██║  ██║██║  ██║ ╚████╔╝ ███████╗    ██║     ╚██████╔╝██║ ╚████║   \n");
    printf("     ╚═╝  ╚═╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝  \n");
    printf("\033[0m\n");
}

void desenhar_campo(int linhas, int colunas) { /*Cria o Campo Minado (A interface dele)*/
    configurar_terminal();
    limpar_tela();
    cabeca_jogo();
    
    imprimir_coordenadas_superiores(colunas);
    
    imprimir_linha_horizontal(colunas);
    
    for (int i = 0; i < linhas; i++) {
       
        printf("\033[38;5;255m %c \033[0m", 'A' + i);
        
        
        printf("\033[38;5;27m║\033[0m"); 
        for (int j = 0; j < colunas; j++) {
            quadrados();
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
    printf("     ███╗   ███╗██╗███╗   ██╗███████╗███████╗██╗    ██╗███████╗███████╗██████╗ ███████╗██████╗  \n");
    printf("     ████╗ ████║██║████╗  ██║██╔════╝██╔════╝██║    ██║██╔════╝██╔════╝██╔══██╗██╔═══ ╝██╔══██╗ \n");
    printf("     ██╔████╔██║██║██╔██╗ ██║█████╗  ███████╗██║ █╗ ██║█████╗  █████╗  ██████╔╝█████╗  ██████╔╝ \n");
    printf("     ██║╚██╔╝██║██║██║╚██╗██║██╔══╝  ╚════██║██║███╗██║██╔══╝  ██╔══╝  ██╔═══╝ ██╔══╝  ██╔══██╗  \n");
    printf("     ██║ ╚═╝ ██║██║██║ ╚████║███████╗███████║╚███╔███╔╝███████╗███████╗██║     ███████╗██║  ██║   \n");
    printf("     ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝╚══════╝ ╚══╝╚══╝ ╚══════╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝  \n");
    printf("                                                UFC                                                       \n");
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

void imprimir_opcao_dimensao(int numero, const char* dimensao) {
    printf("\033[38;5;46m");
    printf("                                ╔════════════════════════════════╗\n");
    printf("                                ║      %d. %s                  ║\n", numero, dimensao);
    printf("                                ╚════════════════════════════════╝\n");
    printf("\033[0m\n");
}

void menu_dimensoes() {
    limpar_tela();
    printf("\033[38;5;27m");
    printf("\n                  ╔═══════════════════════════════════════════════════════════╗\n");
    printf("                  ║  Selecione a Dimensão do Campo (Digite a opção de 1 a 7)  ║\n");
    printf("                  ╚═══════════════════════════════════════════════════════════╝\n\n");
    printf("\033[0m");
    
    imprimir_opcao_dimensao(1, "9x9");
    imprimir_opcao_dimensao(2, "16x16");
    imprimir_opcao_dimensao(3, "16x30");
    imprimir_opcao_dimensao(4, "18x25");
    imprimir_opcao_dimensao(5, "20x30");
    imprimir_opcao_dimensao(6, "22x35");
    imprimir_opcao_dimensao(7, "26x40");
}

void menu_quantidade_minas() {
    limpar_tela();
    printf("\033[38;5;46m"); 
    printf("\n                                ╔══════════════════════════════════╗\n");
    printf("                                ║ Digite o número de minas (1-35): ║\n");
    printf("                                ╚══════════════════════════════════╝\n");
    printf("\033[0m\n");
}

void executar_menu() {
    int opcao, dimensao, minas;

    do {
        configurar_terminal();
        limpar_tela();
        imprimir_titulo();
        imprimir_creditos();
        imprimir_start_game();
        
        scanf("%d", &opcao);

        if (opcao == 1) {
            do {
                menu_dimensoes();
                scanf("%d", &dimensao);
                limpar_tela();
            } while (dimensao < 1 || dimensao > 7);

            do {
                menu_quantidade_minas();
                scanf("%d", &minas);
                limpar_tela();
            } while (minas < 1 || minas > 35);

            int linhas, colunas;
            switch (dimensao) {
                case 1: linhas = 9; colunas = 9; break;
                case 2: linhas = 16; colunas = 16; break;
                case 3: linhas = 16; colunas = 30; break;
                case 4: linhas = 18; colunas = 25; break;
                case 5: linhas = 20; colunas = 30; break;
                case 6: linhas = 22; colunas = 35; break;
                case 7: linhas = 26; colunas = 40; break;
                default: linhas = 9; colunas = 9;
            }

            desenhar_campo(linhas, colunas);
            break; /*Seria a partir daqui a implementacao da estrutura de dados, voce vai tirar esse break e comecar a implementacao usando as funcoes de interface que criei
            
            Aqui depois que o campo foi criado voce irá associar//distribuir os nós na matriz criada (com a informaçao se é bomba ou não)
            
            De acordo com o que o usuario vai selecionando na matriz voce vai acessar o nó e descobrir se é mina ou não. 
            
            Se for mina voce vai fazer com que o quadrado vire bomba, fazendo o mesmo para todas outras bombas e transformando os quadrados nao bombas em vazios
            
            Caso não seja bomba, voce vai fazer o quadrado na posicao selecionada virar quadrado vazio e alguns ao redor também, o quadrado vazio recebe a quantidade de minas proximas
            se for 0 ele fica vazio e se for 1 a 4 ele adota uma numeraçao
            */
        }
    } while (opcao != 1);
}