#include <stdio.h>
#define TAMANHO_TABULEIRO 10 // Tamanho fixo do tabuleiro 10x10
#define TAMANHO_NAVIO 3      // Tamanho fixo dos navios
#define TAMANHO_HABILIDADE 5 // Tamanho fixo das matrizes de habilidade (5x5)

// Função para inicializar o tabuleiro com zeros (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

// Função para verificar se o posicionamento do navio é válido
int validarPosicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                   int linha, int coluna, int horizontal, int diagonal) {
    if (horizontal) { // Navio horizontal
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0; // Sobreposição detectada
        }
    } else if (!diagonal) { // Navio vertical
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0; // Sobreposição detectada
        }
    } else { // Navio diagonal
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) return 0; // Sobreposição detectada
        }
    }
    return 1; // Posição válida
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linha, int coluna, int horizontal, int diagonal) {
    if (horizontal) { // Posiciona navio horizontalmente
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = 3; // 3 representa parte do navio
        }
    } else if (!diagonal) { // Posiciona navio verticalmente
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 3; // 3 representa parte do navio
        }
    } else { // Posiciona navio diagonalmente
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = 3; // 3 representa parte do navio
        }
    }
}

// Função para inicializar a matriz de habilidade em forma de cone
void inicializarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // O cone começa no topo (linha 0, coluna central) e se expande para baixo
            if (i >= 0 && j >= (TAMANHO_HABILIDADE/2 - i) && j <= (TAMANHO_HABILIDADE/2 + i)) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para inicializar a matriz de habilidade em forma de cruz
void inicializarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cruz: linha e coluna central são afetadas
            if (i == TAMANHO_HABILIDADE/2 || j == TAMANHO_HABILIDADE/2) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para inicializar a matriz de habilidade em forma de octaedro (losango)
void inicializarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Octaedro: forma de losango centrada no meio
            int centro = TAMANHO_HABILIDADE/2;
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para sobrepor a habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                       int origem_linha, int origem_coluna) {
    int offset = TAMANHO_HABILIDADE / 2; // Deslocamento para centralizar a habilidade
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha_tab = origem_linha - offset + i;
            int col_tab = origem_coluna - offset + j;
            // Verifica se está dentro dos limites do tabuleiro e se a posição é afetada
            if (linha_tab >= 0 && linha_tab < TAMANHO_TABULEIRO && 
                col_tab >= 0 && col_tab < TAMANHO_TABULEIRO && 
                habilidade[i][j] == 1 && tabuleiro[linha_tab][col_tab] != 3) {
                tabuleiro[linha_tab][col_tab] = 5; // 5 representa área afetada pela habilidade
            }
        }
    }
}

// Função para exibir o tabuleiro no console com caracteres visíveis
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" ~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf(" N "); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf(" X "); // Área afetada pela habilidade
            }
        }
        printf("\n");
    }
    printf("\nLegenda:\n");
    printf(" ~ : Água\n");
    printf(" N : Navio\n");
    printf(" X : Área afetada pela habilidade\n");
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicializa o tabuleiro e as habilidades
    inicializarTabuleiro(tabuleiro);
    inicializarCone(habilidadeCone);
    inicializarCruz(habilidadeCruz);
    inicializarOctaedro(habilidadeOctaedro);

    // Posiciona os navios
    int navio1_linha = 2, navio1_coluna = 3; // Horizontal
    int navio2_linha = 5, navio2_coluna = 7; // Vertical
    int navio3_linha = 0, navio3_coluna = 0; // Diagonal
    int navio4_linha = 4, navio4_coluna = 2; // Diagonal

    if (validarPosicao(tabuleiro, navio1_linha, navio1_coluna, 1, 0)) {
        posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, 1, 0);
    } else {
        printf("Posicao invalida para o navio 1!\n");
        return 1;
    }

    if (validarPosicao(tabuleiro, navio2_linha, navio2_coluna, 0, 0)) {
        posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, 0, 0);
    } else {
        printf("Posicao invalida para o navio 2!\n");
        return 1;
    }

    if (validarPosicao(tabuleiro, navio3_linha, navio3_coluna, 0, 1)) {
        posicionarNavio(tabuleiro, navio3_linha, navio3_coluna, 0, 1);
    } else {
        printf("Posicao invalida para o navio 3!\n");
        return 1;
    }

    if (validarPosicao(tabuleiro, navio4_linha, navio4_coluna, 0, 1)) {
        posicionarNavio(tabuleiro, navio4_linha, navio4_coluna, 0, 1);
    } else {
        printf("Posicao invalida para o navio 4!\n");
        return 1;
    }

    // Aplica as habilidades em pontos de origem fixos
    aplicarHabilidade(tabuleiro, habilidadeCone, 4, 4);     // Cone centrado em (4,4)
    aplicarHabilidade(tabuleiro, habilidadeCruz, 7, 2);     // Cruz centrada em (7,2)
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 1, 8); // Octaedro centrado em (1,8)

    // Exibe o tabuleiro com navios e áreas de efeito
    exibirTabuleiro(tabuleiro);

    printf("\nPressione Enter para encerrar o programa...");
    getchar();

    return 0;
}