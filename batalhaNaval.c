#include <stdio.h>
#include <stdlib.h> // para abs()

#define TAM 10
#define HAB 5 // tamanho das matrizes de habilidade (5x5)

// ===== Função para exibir o tabuleiro =====
void exibirTabuleiro(int tabuleiro[TAM][TAM], char *linha[]) {
    printf("\n   ");
    for (int i = 0; i < TAM; i++) {
        printf(" %s", linha[i]);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// ===== Função para aplicar uma habilidade ao tabuleiro =====
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[HAB][HAB], int origemLinha, int origemColuna) {
    int offset = HAB / 2; // deslocamento para centralizar

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (habilidade[i][j] == 1) { // célula afetada
                int linha = origemLinha - offset + i;
                int coluna = origemColuna - offset + j;

                // Garante que está dentro dos limites do tabuleiro
                if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                    if (tabuleiro[linha][coluna] != 3) { // não sobrescreve navio
                        tabuleiro[linha][coluna] = 5;   // marca como área de efeito
                    }
                }
            }
        }
    }
}

int main() {
    // Letras das colunas do tabuleiro (A a J)
    char *linha[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    int tabuleiro[TAM][TAM];
    int soma = 0;

    // === Inicializa o tabuleiro com 0 (água) ===
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // === Navios fixos ===
    // Navio horizontal
    tabuleiro[3][3] = 3;
    tabuleiro[3][4] = 3;
    tabuleiro[3][5] = 3;

    // Navio vertical
    tabuleiro[5][6] = 3;
    tabuleiro[6][6] = 3;
    tabuleiro[7][6] = 3;

    // Navio diagonal (canto superior direito)
    for (int k = 0; k < 3; k++) {
        tabuleiro[1 + k][9 - k] = 3;
    }

    // === Criação das matrizes de habilidades ===
    int cone[HAB][HAB];
    int cruz[HAB][HAB];
    int octaedro[HAB][HAB];

    // --- Matriz CONE (origem no topo, abre para baixo) ---
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (j >= (HAB / 2 - i) && j <= (HAB / 2 + i) && i <= HAB / 2)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // --- Matriz CRUZ (origem no centro) ---
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (i == HAB / 2 || j == HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // --- Matriz OCTAEDRO (formato de losango) ---
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (abs(i - HAB / 2) + abs(j - HAB / 2) <= HAB / 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }

    // === Aplica as habilidades no tabuleiro ===
    aplicarHabilidade(tabuleiro, cone, 2, 2);     // Cone centrado em (2,2)
    aplicarHabilidade(tabuleiro, cruz, 6, 3);     // Cruz centrada em (6,3)
    aplicarHabilidade(tabuleiro, octaedro, 5, 8); // Octaedro centrado em (5,8)

    // === Exibe o tabuleiro ===
    printf("\n--- Jogo Batalha Naval ---\n");
    exibirTabuleiro(tabuleiro, linha);

    // === Conta partes de navio ===
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 3) soma++;
        }
    }

    printf("\nTotal de partes de navios no tabuleiro: %d\n", soma);
    printf("\nLegenda:\n0 = Água\n3 = Navio\n5 = Área de habilidade\n");

    return 0;
}
