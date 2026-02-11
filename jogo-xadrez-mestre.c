#include <stdio.h>

// Função recursiva para a Torre

void moverTorreRec (int casas) 
{
    if (casas == 0) return;    // Condição de parada
    printf("→\n");             //cada linha representa uma casas para a direita
    moverTorreRec(casas - 1);  // chamada recursiva
}

// Função recursiva para o Bispo

void moverBispoRec (int casas)
{
    if (casas == 0) return;    // condição de parada
    for (int espaço = casas; espaço >= 1; espaço --)
    {
        printf("  ");          // espaço para diagonal
    }
    printf("↗︎\n");             // marca a posição do Bispo
    moverBispoRec(casas - 1);  // Chamada recursiva
}

// Função recursiva para a Rainha

void(moverRainhaRec) (int casas)
{
    if (casas == 0) return;     // condição de parada
    printf("←\n");              // cada linha representa uma casa para esquerda
    moverRainhaRec( casas - 1); // chamada recursiva
}

// Função recursiva para o cavalo

void moverCavaloRec (int cima, int direita)
{
    if (cima == 0 && direita == 0) return;     // condição de parada

    if (direita > 0)
    {
        printf("➞\n");  // primeira vai andar uma casa para direita é necessário pois só assim vai aparacer a movimentação correta para o usuário no ecrã
        moverCavaloRec( cima, direita - 1);
    }

    else if (cima > 0)
    {
        printf("↑\n");          // depois sobe 2 casas
        moverCavaloRec( cima - 1, direita);
    }
}


int main() 
{
    // Torre: 5 casas para a direita
    int casasTorre = 5;
    printf("Torre movendo para direita:\n");
    moverTorreRec(casasTorre);  // Chamada da  função recursiva
    printf("\n");

    // Bispo: 5 casas diagonal para cima direita
    int casasBispo = 5;
    printf("Bispo movendo na diagonal (cima, direita):\n");
    moverBispoRec(casasBispo);  // Chamada da função recursiva
    printf("\n");

    // Rainha: 8 casas para esquerda
    int casasRainha = 8;
    printf("Rainha movendo para esquerda:\n");
    moverRainhaRec(casasRainha); // chamada da função recursiva
    printf("\n");

    // Cavalo: 2 pra cima e 1 pra direita
    int cimaCavalo = 2;
    int direitaCavalo = 1;
    printf("Cavalo movendo em L (2 pra cima, 1 para direita):\n");
    moverCavaloRec(cimaCavalo, direitaCavalo);  // chamada da função recursiva
    printf("\n");

    return 0;

}