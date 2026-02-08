#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a room in the mansion
// Estrutura que representa uma sala na mansao
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Structure that represents a node in the BST of clues
// Estrutura que representa um no na BST de pistas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Function that creates a room with name and clue
// Funcao que cria uma sala com nome e pista
Sala* criarSala(char nome[], char pista[]) {

    Sala* novaSala = (Sala*) malloc(sizeof(Sala));

    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);

    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

// Function that inserts a clue into BST
// Funcao que insere uma pista na arvore BST
PistaNode* inserirPista(PistaNode* raiz, char pista[]) {

    // If tree is empty, create new node
    // Se a arvore estiver vazia, cria novo no
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    // Insert alphabetically
    // Insere em ordem alfabetica
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

// Function that shows all clues in alphabetical order
// Funcao que exibe todas as pistas em ordem alfabetica
void exibirPistas(PistaNode* raiz) {

    if (raiz != NULL) {

        // In-order traversal
        // Percurso em ordem
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Function that explores rooms and collects clues
// Funcao que explora as salas e coleta pistas
void explorarSalasComPistas(Sala* atual, PistaNode** arvorePistas) {

    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta na sala: %s\n", atual->nome);

        // Check if there is a clue in the room
        // Verifica se ha pista na sala
        if (strlen(atual->pista) > 0) {
            printf("Voce encontrou uma pista: %s\n", atual->pista);

            // Insert clue into BST
            // Insere a pista na arvore BST
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        printf("\nEscolha o proximo caminho:\n");
        printf("e - esquerda\n");
        printf("d - direita\n");
        printf("s - sair\n");
        printf("Opcao: ");

        scanf(" %c", &opcao);

        if (opcao == 'e') {

            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao ha caminho para a esquerda!\n");
            }

        } else if (opcao == 'd') {

            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao ha caminho para a direita!\n");
            }

        } else if (opcao == 's') {

            printf("\nExploracao encerrada.\n");
            break;

        } else {

            printf("Opcao invalida!\n");
        }
    }
}

// Main function that builds the mansion map
// Funcao principal que monta o mapa da mansao
int main() {

    // Create rooms with clues
    // Cria as salas com pistas
    Sala* hall = criarSala("Hall de Entrada", "Chave antiga");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala* cozinha = criarSala("Cozinha", "Faca manchada");
    Sala* escritorio = criarSala("Escritorio", "Bilhete suspeito");
    Sala* salaSecreta = criarSala("Sala Secreta", "Mapa misterioso");
    Sala* despensa = criarSala("Despensa", "Frasco quebrado");
    Sala* jardim = criarSala("Jardim", "Pegadas no chao");

    // Build the binary tree map
    // Monta o mapa em arvore binaria
    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = escritorio;
    biblioteca->direita = salaSecreta;

    cozinha->esquerda = despensa;
    cozinha->direita = jardim;

    // Create empty BST for clues
    // Cria arvore BST vazia para pistas
    PistaNode* arvorePistas = NULL;

    // Start exploration
    // Inicia a exploracao
    explorarSalasComPistas(hall, &arvorePistas);

    // Show all collected clues
    // Exibe todas as pistas coletadas
    printf("\nPistas coletadas em ordem alfabetica:\n");
    exibirPistas(arvorePistas);

    return 0;
}
