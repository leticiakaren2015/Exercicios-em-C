#include <stdio.h>

int main() {

    // ================================
    // Torre: 5 casas para a direita
    // ================================
    int casasTorre = 5;
    printf("Torre movendo para a direita:\n");
    for (int i = 1; i <= casasTorre; i++) {
        printf("→\n"); // Cada linha representa uma casa para direita
    }

    printf("\n");


    //==============================================
    // Bispo: 5 casas diagonal para cima e direita
    //==============================================
    int casasBispo = 5;
    printf("Bispo movendo na diagonal (Cima, Direita):\n");
    for (int i = casasBispo; i >= 1; i--) {
        for (int espaço = 0; espaço < i; espaço++){
            printf("  "); // Espaço para diagonal
        }
        printf("↗︎\n"); // Marca a posição do bispo
    }

    printf("\n");

    // ===============================
    // Rainha 8 casas para esquerda
    // ===============================
    int casasRainha = 8;
    printf("Rainha movendo para a esquerda:\n");
    for (int i = 1; i <= casasRainha; i++) {
        printf("←\n"); // Cada linha representa uma casa para esquerda
    }

    printf("\n");

    //====================================
    // Cavalo: 2 pra cima e 1 pra direita
    //====================================
    int movimentoCompleto = 1;

    while (movimentoCompleto--) 
    {
        printf("→\n"); // Cavalo indo 1 casa para direita // O PRINTF ficou na frente do FOR, pois só assim aparece corretamente no ecrã do usuário
        for (int i = 0; i < 2; i++) {
            printf("↑\n"); // Cavalo subido 2 casas
        }
    } 


    return 0;
}