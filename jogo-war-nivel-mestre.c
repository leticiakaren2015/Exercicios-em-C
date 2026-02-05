// Libraries needed
// Bibliotecas necessarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Territory structure
// Estrutura de territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Function to assign a random mission to the player
// Funcao para atribuir uma missao aleatoria ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}  

// Function to display the mission
// Funcao para exibir a missao
void exibirMissao(char* missao) {
    printf("\nSua missao estrategica: %s\n\n", missao);
}

// Function to verify if the mission was completed
// Funcao para verificar se a missao foi cumprida
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {

    int cont = 0;

    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Jogador") == 0) {
                cont++;
            }
        }

        if (cont >= 3)
            return 1;
    }

    return 0;
}

// Function to simulate an attack between territories
// Funcao para simular um ataque entre territorios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("Ataque: %s (%d tropas) x %s (%d tropas)\n",
        atacante->nome, atacante->tropas,
        defensor->nome, defensor->tropas);

    if (dadoA > dadoD) {
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        printf("Atacante venceu!\n\n");
    } else {
        atacante->tropas--;
        printf("Defensor venceu!\n\n");
    }
}

// Function to display the map status
// Funcao para exibir o estado do mapa
void exibirMapa(struct Territorio* mapa, int tamanho) {

    printf("\n----- MAPA ATUAL -----\n");

    for (int i = 0; i < tamanho; i++) {
        printf("Territorio: %s | Dono: %s | Tropas: %d\n",
            mapa[i].nome,
            mapa[i].cor,
            mapa[i].tropas);
    }

    printf("----------------------\n\n");
}

// Function to free allocated memory
// Funcao para liberar memoria alocada
void liberarMemoria(char* missaoJogador) {
    free(missaoJogador);
}

// Main function
// Funcao principal
int main() {

    srand(time(NULL));

    // Creating territory map
    // Criando mapa de territorios
    struct Territorio* mapa = (struct Territorio*) calloc(5, sizeof(struct Territorio));

    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "Jogador");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "Inimigo");
    mapa[1].tropas = 4;

    strcpy(mapa[2].nome, "Chile");
    strcpy(mapa[2].cor, "Inimigo");
    mapa[2].tropas = 3;

    strcpy(mapa[3].nome, "Peru");
    strcpy(mapa[3].cor, "Jogador");
    mapa[3].tropas = 6;

    strcpy(mapa[4].nome, "Colombia");
    strcpy(mapa[4].cor, "Inimigo");
    mapa[4].tropas = 2;

    // Mission list
    // Lista de missoes
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar tropas vermelhas",
        "Dominar dois continentes",
        "Conquistar 5 territorios",
        "Eliminar tropas azuis"
    };

    // Dynamic allocation of player mission
    // Alocacao dinamica da missao do jogador
    char* missaoJogador = (char*) malloc(100 * sizeof(char));

    // Assigning random mission
    // Sorteando a missao
    atribuirMissao(missaoJogador, missoes, 5);

    // Showing mission only once
    // Exibindo a missao apenas uma vez
    exibirMissao(missaoJogador);

    int turno = 0;

    // Game loop simulation
    // Simulacao do loop do jogo
    while (1) {

        printf("===== TURNO %d =====\n", turno + 1);

        exibirMapa(mapa, 5);

        // Example attack simulation
        // Exemplo de simulacao de ataque
        atacar(&mapa[0], &mapa[1]);

        // Checking mission completion
        // Verificando se a missao foi cumprida
        if (verificarMissao(missaoJogador, mapa, 5)) {
            printf("Parabens! Voce cumpriu sua missao e venceu o jogo!\n");
            break;
        }

        turno++;

        if (turno >= 10) {
            printf("Limite de turnos atingido. Fim do jogo!\n");
            break;
        }
    }

    // Freeing memory
    // Liberando memoria
    liberarMemoria(missaoJogador);
    free(mapa);

    return 0;
}
