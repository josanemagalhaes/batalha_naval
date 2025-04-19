#include <stdio.h>

// Define o tamanho do tabuleiro
#define TAMANHO_TABULEIRO 10

// Define o tamanho das matrizes de habilidade
#define TAMANHO_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0) e alguns navios (3)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
    // Posiciona alguns navios para teste
    tabuleiro[2][2] = 3;
    tabuleiro[3][5] = 3;
    tabuleiro[7][1] = 3;
}

// Função para criar a matriz de habilidade em Cone
void criarHabilidadeCone(int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i >= centro && j >= (centro - (i - centro)) && j <= (centro + (i - centro))) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em Cruz
void criarHabilidadeCruz(int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em Octaedro (Losango)
void criarHabilidadeOctaedro(int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }
}

// Função para aplicar a habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                      int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                      int linhaOrigem, int colunaOrigem) {
    int centroHabilidade = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTabuleiro = linhaOrigem - centroHabilidade + i;
                int colunaTabuleiro = colunaOrigem - centroHabilidade + j;
                // Verifica se a posição calculada está dentro dos limites do tabuleiro
                if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
                    colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = 5; // 5 representa área afetada
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    printf("-- -- -- -- -- -- -- -- -- --\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d|", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" ~"); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf(" #"); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf(" *"); // Área afetada
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Cria o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Cria as matrizes de habilidade
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    // Define os pontos de origem das habilidades no tabuleiro
    int linhaOrigemCone = 1;
    int colunaOrigemCone = 2;
    int linhaOrigemCruz = 4;
    int colunaOrigemCruz = 5;
    int linhaOrigemOctaedro = 7;
    int colunaOrigemOctaedro = 1;

    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, linhaOrigemCone, colunaOrigemCone);
    aplicarHabilidade(tabuleiro, cruz, linhaOrigemCruz, colunaOrigemCruz);
    aplicarHabilidade(tabuleiro, octaedro, linhaOrigemOctaedro, colunaOrigemOctaedro);

    // Exibe o tabuleiro com as áreas de efeito das habilidades
    printf("--- Tabuleiro com Habilidade em Cone ---\n");
    exibirTabuleiro(tabuleiro);

    // Reinicializa o tabuleiro para mostrar a próxima habilidade isoladamente
    inicializarTabuleiro(tabuleiro);
    aplicarHabilidade(tabuleiro, cruz, linhaOrigemCruz, colunaOrigemCruz);
    printf("--- Tabuleiro com Habilidade em Cruz ---\n");
    exibirTabuleiro(tabuleiro);

    // Reinicializa o tabuleiro novamente
    inicializarTabuleiro(tabuleiro);
    aplicarHabilidade(tabuleiro, octaedro, linhaOrigemOctaedro, colunaOrigemOctaedro);
    printf("--- Tabuleiro com Habilidade em Octaedro ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
