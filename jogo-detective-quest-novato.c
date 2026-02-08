#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a room in the mansion
// Estrutura que representa uma sala na mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Function that creates a room dynamically
// Função que cria uma sala de forma dinâmica
Sala* criarSala(char nome[]) {

    // Allocate memory for new room
    // Aloca memória para a nova sala
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));

    // Copy name to structure
    // Copia o nome para a estrutura
    strcpy(novaSala->nome, nome);

    // Initialize child pointers
    // Inicializa os ponteiros filhos
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

// Function that allows player to explore the rooms
// Função que permite ao jogador explorar as salas
void explorarSalas(Sala* atual) {

    char opcao;

    // Loop while player is in a valid room
    // Repete enquanto o jogador estiver em uma sala válida
    while (atual != NULL) {

        // Show current room
        // Exibe a sala atual
        printf("\nVoce esta na sala: %s\n", atual->nome);

        // Check if it is a leaf node
        // Verifica se é um nó folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Voce chegou a um comodo final da mansao!\n");
            break;
        }

        // Ask user for direction
        // Pergunta ao usuario para onde ir
        printf("Para onde deseja ir?\n");
        printf("e - esquerda\n");
        printf("d - direita\n");
        printf("s - sair\n");
        printf("Opcao: ");

        scanf(" %c", &opcao);

        // Decision structure for navigation
        // Estrutura de decisao para navegacao
        if (opcao == 'e') {

            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao existe caminho para a esquerda!\n");
            }

        } else if (opcao == 'd') {

            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao existe caminho para a direita!\n");
            }

        } else if (opcao == 's') {

            printf("Exploracao encerrada.\n");
            break;

        } else {

            printf("Opcao invalida!\n");
        }
    }
}

// Main function that builds the mansion map
// Funcao principal que monta o mapa da mansao
int main() {

    // Creating rooms of the mansion
    // Criando as salas da mansao
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* escritorio = criarSala("Escritorio");
    Sala* salaSecreta = criarSala("Sala Secreta");
    Sala* despensa = criarSala("Despensa");
    Sala* jardim = criarSala("Jardim");

    // Building the binary tree structure
    // Montando a estrutura da arvore binaria
    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = escritorio;
    biblioteca->direita = salaSecreta;

    cozinha->esquerda = despensa;
    cozinha->direita = jardim;

    // Start exploration from hall
    // Inicia a exploracao a partir do hall
    explorarSalas(hall);

    return 0;
}