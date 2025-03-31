#include <stdio.h>
#define TAMANHO_TABULEIRO 10 // Tamanho fixo do tabuleiro 10x10
#define TAMANHO_NAVIO 3      // Tamanho fixo dos navios

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
                  int linha, int coluna, int horizontal) {
    // Verifica se o navio cabe no tabuleiro e não há sobreposição
    if (horizontal) {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0; // Sobreposição detectada
        }
    } else {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0; // Sobreposição detectada
        }
    }
    return 1; // Posição válida
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                    int linha, int coluna, int horizontal) {
    if (horizontal) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = 3; // 3 representa parte do navio
        }
    } else {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 3; // 3 representa parte do navio
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    // Imprime cabeçalho com números das colunas
    printf("  ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    // Imprime linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);

    // Coordenadas fixas para os navios
    int navio1_linha = 2;    // Navio horizontal
    int navio1_coluna = 3;
    int navio2_linha = 5;    // Navio vertical
    int navio2_coluna = 7;

    // Valida e posiciona o primeiro navio (horizontal)
    if (validarPosicao(tabuleiro, navio1_linha, navio1_coluna, 1)) {
        posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, 1);
    } else {
        printf("Posicao invalida para o navio 1!\n");
        return 1;
    }

    // Valida e posiciona o segundo navio (vertical)
    if (validarPosicao(tabuleiro, navio2_linha, navio2_coluna, 0)) {
        posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, 0);
    } else {
        printf("Posicao invalida para o navio 2 ou sobreposicao detectada!\n");
        return 1;
    }

    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);

    printf("\nPressione Enter para encerrar o programa...");
    getchar();

    return 0;
}