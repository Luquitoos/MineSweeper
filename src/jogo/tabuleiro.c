#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tabuleiro.h"

Tabuleiro* iniciar_tabuleiro(
    int largura, 
    int altura,
    int quantidadeBombas
) {
    // Aloca memória para o tabuleiro
    Tabuleiro* tabuleiro = (Tabuleiro*) malloc(sizeof(Tabuleiro));

    if (!tabuleiro) 
        return NULL;

    // Aloca memória para a matriz de ponteiros para linhas
    tabuleiro->matriz = (No**) malloc(altura * sizeof(No*));
    if (!tabuleiro->matriz) {
        free(tabuleiro);
        return NULL;
    }

    tabuleiro->largura = largura;
    tabuleiro->altura = altura;
    tabuleiro->quantidadeBombas = quantidadeBombas;

    // Aloca memória para cada linha da matriz
    for (int i = 0; i < altura; i++) {
        tabuleiro->matriz[i] = (No*) malloc(largura * sizeof(No));

        if (!tabuleiro->matriz[i]) {
            // Libera memória alocada em caso de falha
            for (int j = 0; j < i; j++) {
                free(tabuleiro->matriz[j]);
            }
            free(tabuleiro->matriz);
            free(tabuleiro);
            return NULL;
        }
    }

    // Predefinir os valores de cada nó
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            tabuleiro->matriz[i][j].revelado = 0;
            tabuleiro->matriz[i][j].bomba = 0;
            tabuleiro->matriz[i][j].possui_bandeira = 0;
            tabuleiro->matriz[i][j].total_minas_adjacentes = 0;

            tabuleiro->matriz[i][j].cima = (i > 0) ? &tabuleiro->matriz[i - 1][j] : NULL;
            tabuleiro->matriz[i][j].baixo = (i < altura - 1) ? &tabuleiro->matriz[i + 1][j] : NULL;
            tabuleiro->matriz[i][j].esquerda = (j > 0) ? &tabuleiro->matriz[i][j - 1] : NULL;
            tabuleiro->matriz[i][j].direita = (j < largura - 1) ? &tabuleiro->matriz[i][j + 1] : NULL;

            tabuleiro->matriz[i][j].cima_esquerda = (i > 0 && j > 0) ? &tabuleiro->matriz[i - 1][j - 1] : NULL;
            tabuleiro->matriz[i][j].cima_direita = (i > 0 && j < largura - 1) ? &tabuleiro->matriz[i - 1][j + 1] : NULL;
            tabuleiro->matriz[i][j].baixo_esquerda = (i < altura - 1 && j > 0) ? &tabuleiro->matriz[i + 1][j - 1] : NULL;
            tabuleiro->matriz[i][j].baixo_direita = (i < altura - 1 && j < largura - 1) ? &tabuleiro->matriz[i + 1][j + 1] : NULL;
        }
    }
    
    return tabuleiro;
}

No* obter_no(
    Tabuleiro* tabuleiro, 
    char linha, 
    int coluna
) {
    if (!tabuleiro || !tabuleiro->matriz) 
        return NULL;

    int indice_linha;
    if (linha >= 'A' && linha <= 'Z') {
        indice_linha = linha - 'A';
    } else if (linha >= 'a' && linha <= 'z') {
        indice_linha = linha - 'a';
    } else {
        return NULL;
    }

    // (inicia do zero)
    int indice_coluna = coluna - 1;

    /**
     * Caso passe dos limites do tabuleiro, ele retorna null.
     */
    if (indice_linha < 0 || indice_linha >= tabuleiro->altura || indice_coluna < 0 || indice_coluna >= tabuleiro->largura)
        return NULL;

    return &tabuleiro->matriz[indice_linha][indice_coluna];
}

int calcular_minas_adjacentes(
    Tabuleiro* tabuleiro, 
    char linha, 
    int coluna
) {
    int total = 0;

    No* no = obter_no(tabuleiro, linha, coluna);
    if (!no)
        return total;

    if (no->cima && no->cima->bomba) total++;
    if (no->baixo && no->baixo->bomba) total++;
    if (no->esquerda && no->esquerda->bomba) total++;
    if (no->direita && no->direita->bomba) total++;
    if (no->cima_esquerda && no->cima_esquerda->bomba) total++;
    if (no->cima_direita && no->cima_direita->bomba) total++;
    if (no->baixo_esquerda && no->baixo_esquerda->bomba) total++;
    if (no->baixo_direita && no->baixo_direita->bomba) total++;


    return total;
}


void distribuir_bombas(
    Tabuleiro* tabuleiro
) {
    if (!tabuleiro || tabuleiro->quantidadeBombas <= 0)
        return;

    int totalCampos = tabuleiro->largura * tabuleiro->altura;
    int* indices = (int*) malloc(totalCampos * sizeof(int));
    if (!indices)
        return;

    // ele cria um array com vários indices
    // dps ele aleatoriza para aleatorizar as posições das bombas
    for (int i = 0; i < totalCampos; i++) {
        indices[i] = i;
    }

    srand(time(NULL));
    for (int i = totalCampos - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Ddefine as bombas nas posições sorteadas
    for (int i = 0; i < tabuleiro->quantidadeBombas; i++) {
        int idx = indices[i];
        int linha = idx / tabuleiro->largura;
        int coluna = idx % tabuleiro->largura; //observar
        tabuleiro->matriz[linha][coluna].bomba = 1;
    }

    free(indices);
}

int realoca_bomba(Tabuleiro* tabuleiro, char linha_origem, int coluna_origem) {
    // Validações iniciais
    if (!tabuleiro || !tabuleiro->matriz) 
        return 0;

    No* realocar = obter_no(tabuleiro, linha_origem, coluna_origem);
    if (!realocar) {
        return 0;
    }

    // Busca uma posição livre para realocar a bomba
    for(int i = 0; i < tabuleiro->altura; i++) {
        for(int j = 0; j < tabuleiro->largura; j++) {
            No* no = &tabuleiro->matriz[i][j];
            // Verifica se é uma posição válida para realocar
            if(no && !no->bomba && no != realocar) {
                no->bomba = 1;
                return 1;  // Sucesso
            }
        }
    }

    return 0;  // Falha - não encontrou posição livre
}

// 0 -> sucesso
// os outros códigos de erro estão relacionados com o arquivo 'jogo.c'
/*Quando a função for chamada, deve começar com revelar_campo(tabuleiro, &jogadas_totais, linha, coluna, 0); com o parametro de recursão 0, esse é o controle para ele não contar
como jogada a mais*/
int revelar_campo(Tabuleiro* tabuleiro, int jogadasTotais, char linha, int coluna, int chamada_recursiva) {
    // Obtém o nó e faz validações iniciais
    No* no = obter_no(tabuleiro, linha, coluna);
    
    // Validações de limites e nó válido
    if (!no || linha < 'A' || linha >= 'A' + tabuleiro->altura || 
        coluna < 1 || coluna > tabuleiro->largura)
        return -1;
    
    // Verifica se já está revelado ou tem bandeira
    if (no->revelado || no->possui_bandeira)
        return 3;

    // Tratamento especial para primeira jogada
    if (jogadasTotais == 0) {
        distribuir_bombas(tabuleiro);
        // Se primeira posição tem bomba, realoca
        if(no->bomba) {
            no->bomba = 0;
            if(!realoca_bomba(tabuleiro, linha, coluna)) {
                return -1;
            }
        }
    }

    // Marca como revelado
    no->revelado = 1;
    
    // Verifica se acertou bomba (exceto na primeira jogada)
    if(jogadasTotais != 0 && no->bomba) {
        return 2;  // Código para fim de jogo
    }

    // Calcula minas adjacentes
    no->total_minas_adjacentes = calcular_minas_adjacentes(tabuleiro, linha, coluna);
    
    // Se não há minas adjacentes, revela os vizinhos recursivamente
    if (no->total_minas_adjacentes == 0) {
        // Arrays para calcular as 8 posições adjacentes
        int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
        int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};
        
        for(int i = 0; i < 8; i++) {
            char nova_linha = linha + dx[i];
            int nova_coluna = coluna + dy[i];
            // Chama recursivamente para cada vizinho
            revelar_campo(tabuleiro, jogadasTotais, nova_linha, nova_coluna, 1);
        }
    }
    
    return 0;  // Sucesso
}

No** obter_posicoes_reveladas(Tabuleiro* tabuleiro, int* total_revelados) {
    if (!tabuleiro || !tabuleiro->matriz) {
        return NULL;
    }

    // Contagem dos nós não revelados
    *total_revelados = 0;
    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            No* no = &tabuleiro->matriz[i][j];
            if (no && no->revelado && no->total_minas_adjacentes != 0) {
                (*total_revelados)++;
            }
        }
    }

    // Aloca espaço para armazenar os nós não revelados
    No** revelados = malloc(*total_revelados * sizeof(No*));
    if (!revelados)
        return NULL;
    
    int idx = 0;
    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            No* no = &tabuleiro->matriz[i][j];
            if (no && no->revelado && no->total_minas_adjacentes != 0) {
                revelados[idx++] = no;
            }
        }
    }

    return revelados;
}

char* obter_posicao(No* no) {
    int linha = 1, coluna = 1;
    No* atual = no;

    while (atual->cima) {
        atual = atual->cima;
        linha++;
    }

    atual = no;
    while (atual->esquerda) {
        atual = atual->esquerda;
        coluna++;
    }

    char* posicao = (char*) malloc(12 * sizeof(char));
    if (!posicao) return NULL;

    snprintf(posicao, 12, "%c%d", 'A' + (linha - 1), coluna);
    return posicao;
}

/**
 * Obtém as posições das bombas já descobertas no tabuleiro.
 * 
 * Retorna um vetor de strings (exemplo: ["A3", "C2", ...]).
 * O vetor deve ser liberado após o uso.
 * 
 * @param tabuleiro O tabuleiro do jogo.
 * @param total_bombas Ponteiro para armazenar a quantidade de bombas encontradas.
 * @return Vetor de strings com as coordenadas das bombas descobertas.
 */
No** obter_bombas(Tabuleiro* tabuleiro, int* bombasReveladas) {
    No** posicoes_reveladas;
    No* no_atual;
    int capacidade, total_revelados;
    No** bombas;

    if (!tabuleiro || !tabuleiro->matriz) 
        return NULL;

    capacidade = tabuleiro->quantidadeBombas;
    *bombasReveladas = 0;

    bombas = (No**) malloc(capacidade * sizeof(No*));
    if (!bombas) return NULL;

    posicoes_reveladas = obter_posicoes_reveladas(tabuleiro, &total_revelados);
    if (!posicoes_reveladas) {
        return NULL;
    }
    
    // Iterar sobre os nós revelados
    for (int i = 0; i < total_revelados; i++) {
        no_atual = posicoes_reveladas[i];

        int total_adjacentes_nao_revelados = 0;

        No* adjacentes[8] = {
            no_atual->cima,
            no_atual->baixo, 
            no_atual->esquerda, 
            no_atual->direita, 
            no_atual->cima_esquerda, 
            no_atual->cima_direita, 
            no_atual->baixo_esquerda, 
            no_atual->baixo_direita
        };

        No* adjacentes_nao_revelados[8] = {NULL};
        
        for (int k = 0; k <= 7; k++)
            if (adjacentes[k] && !adjacentes[k]->revelado) {
                adjacentes_nao_revelados[k] = adjacentes[k];
                total_adjacentes_nao_revelados++;
            }
    
        if (no_atual->total_minas_adjacentes == total_adjacentes_nao_revelados) {
            for (int z = 0; z <= 7; z++) {
                No* no_bomba = adjacentes_nao_revelados[z];
            
                if (no_bomba) {
                    int repetido = 0;
            
                    // Verifica se a posição já foi adicionada
                    for (int j = 0; j < *bombasReveladas; j++) {
                        if (bombas[j] == no_bomba) {
                            repetido = 1;
                            break;
                        }
                    }
            
                    // Se não for repetido, adiciona
                    if (!repetido) {
                        bombas[*bombasReveladas] = no_bomba;
                        (*bombasReveladas)++;
                    }
                }
            }
        }
    }

    free(posicoes_reveladas);
    return bombas;
}

int eh_bomba(int* total_bombas, No** bombas, No* no) {
    for (int i = 0; i < *total_bombas; i++) {
        if (bombas[i] == no) {
            return 1;
        }
    }
    
    return 0;
}

No* buscar_no_nao_revelado_adj(No* centro, int* total_bombas, No** bombas) {
    int i;
    No* adj;

    No* adjacentes[8] = {
        centro->cima,
        centro->baixo, 
        centro->esquerda, 
        centro->direita, 
        centro->cima_esquerda, 
        centro->cima_direita, 
        centro->baixo_esquerda, 
        centro->baixo_direita
    };

    for (i = 0; i < 8; i++) {
        adj = adjacentes[i];
        if (adj && !adj->revelado && !eh_bomba(total_bombas, bombas, adj))
            return adj;
    }

    return NULL;
}

/**
 * Obtém uma dica baseada nas células reveladas e suas minas adjacentes.
 * 
 * O algoritmo verifica se há uma célula revelada onde o número de células
 * ocultas ao redor seja igual ao número de minas adjacentes. Se isso acontecer,
 * sabemos que todas essas células ocultas são minas e podemos sugerir uma
 * célula segura adjacente.
 *
 * @param tabuleiro O tabuleiro do jogo.
 * @return Ponteiro para string contendo a posição da célula segura (ex: "A1").
 *         Retorna NULL se nenhuma dica estiver disponível.
 */
char* obter_dica(Tabuleiro* tabuleiro) {
    No* no_atual;

    if (!tabuleiro || !tabuleiro->matriz)
        return NULL;

    int total_bombas, total_revelados = 0;
    No** bombas = obter_bombas(tabuleiro, &total_bombas);
    if (!bombas) 
        return NULL;

    No** posicoes_reveladas = posicoes_reveladas = obter_posicoes_reveladas(tabuleiro, &total_revelados);
    if (!posicoes_reveladas)
        return NULL;

    for (int i = 0; i < total_revelados; i++) {
        no_atual = posicoes_reveladas[i];

        int total_adjacentes_nao_revelados = 0;

        No* adjacentes[8] = {
            no_atual->cima,
            no_atual->baixo, 
            no_atual->esquerda, 
            no_atual->direita, 
            no_atual->cima_esquerda, 
            no_atual->cima_direita, 
            no_atual->baixo_esquerda, 
            no_atual->baixo_direita
        };
        
        int quantidade_bomba_adjacente = no_atual->total_minas_adjacentes;
        
        for (int k = 0; k < 8; k++) {
            No* adj = adjacentes[k];
            if (adj) {
                quantidade_bomba_adjacente--;
                if (quantidade_bomba_adjacente == 0) {
                    // Busca um nó adjacente que não seja bomba
                    No* no_adj_nao_revelado = buscar_no_nao_revelado_adj(no_atual, &total_bombas, bombas);
                    if (no_adj_nao_revelado) {
                        char* dica = obter_posicao(no_adj_nao_revelado);
                        return dica;
                    }
                }
            }
        }
    }

    return NULL;
}

void exibir_bombas(Tabuleiro* tabuleiro) {
    // Validação do ponteiro
    if (!tabuleiro || !tabuleiro->matriz) return;

    // Primeiro revela todo o tabuleiro
    for (int i = 0; i < tabuleiro->altura; i++) {
        for (int j = 0; j < tabuleiro->largura; j++) {
            No* no = &tabuleiro->matriz[i][j];
            // Marca todos os campos como revelados
            no->revelado = 1;
            // Atualiza o número de minas adjacentes
            if (!no->bomba) {  // Só calcula para campos sem bomba
                no->total_minas_adjacentes = calcular_minas_adjacentes(
                    tabuleiro, 'A' + i, j + 1
                );
            }
        }
    }
}

int definir_bandeira(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
) {
    No* no = obter_no(tabuleiro, linha, coluna);

    // Esse erro só irá acontecer se o tabuleiro não tiver sido inicializado.
    // Na implementação adequada, é impossível, mas é boa verificação por segurança.
    //Se o nó já foi revelado também retorna -1, para não definir a bandeira em um quadrado que ja foi revelado
    if (no == NULL || no->revelado )
        return -1;

    no->possui_bandeira = 1;
    return 0;
}

int remover_bandeira(
    Tabuleiro* tabuleiro,
    char linha,
    int coluna
) {
    No* no = obter_no(tabuleiro, linha, coluna);

    // Esse erro só irá acontecer se o tabuleiro não tiver sido inicializado.
    // Na implementação adequada, é impossível, mas é boa verificação por segurança.
    if (no == NULL)
        return -1;

    no->possui_bandeira = 0;

    return 0;
}

int vitoria(Tabuleiro* tabuleiro) {
    // Percorre todo o tabuleiro
    for (int i = 0; i < tabuleiro->altura; i++) {
        for(int j = 0; j < tabuleiro->largura; j++) {
            No* no = &tabuleiro->matriz[i][j];
            // Se encontrar algum quadrado que não é bomba e não está revelado
            // então o jogo ainda não acabou
            if(no->bomba && no->revelado)
                return 0;
            
            if(!no->bomba && !no->revelado)
                return 0;
        }
    }
    // Se chegou aqui, todos os quadrados sem bomba estão revelados
    return 1;
}
