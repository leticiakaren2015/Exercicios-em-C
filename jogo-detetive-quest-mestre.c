#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// Structure that represents a room in the mansion
// Estrutura que representa um comodo na mansao
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Structure for BST node that stores clues
// Estrutura para no da BST que armazena pistas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Structure for hash table entry
// Estrutura para entrada da tabela hash
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode *proximo;
} HashNode;

HashNode* tabelaHash[TAM_HASH];

// Hash function
// Funcao hash
int funcaoHash(char *str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        soma += str[i];
    }
    return soma % TAM_HASH;
}

// Function that creates a room dynamically
// Funcao que cria uma sala dinamicamente
Sala* criarSala(char nome[], char pista[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Function that inserts a clue into BST
// Funcao que insere uma pista na arvore BST
PistaNode* inserirPista(PistaNode* raiz, char pista[]) {

    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

// Function that inserts clue and suspect into hash table
// Funcao que insere pista e suspeito na tabela hash
void inserirNaHash(char pista[], char suspeito[]) {

    int indice = funcaoHash(pista);

    HashNode* novo = (HashNode*) malloc(sizeof(HashNode));

    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->proximo = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

// Function that finds suspect by clue
// Funcao que encontra o suspeito correspondente a pista
char* encontrarSuspeito(char pista[]) {

    int indice = funcaoHash(pista);

    HashNode* atual = tabelaHash[indice];

    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Function that shows all clues in alphabetical order
// Funcao que exibe todas as pistas em ordem alfabetica
void exibirPistas(PistaNode* raiz) {

    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Function that explores rooms and collects clues
// Funcao que explora as salas e coleta pistas
void explorarSalas(Sala* atual, PistaNode** arvorePistas) {

    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta na sala: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {

            printf("Pista encontrada: %s\n", atual->pista);

            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        printf("\nEscolha o caminho:\n");
        printf("e - esquerda\n");
        printf("d - direita\n");
        printf("s - sair\n");
        printf("Opcao: ");

        scanf(" %c", &opcao);

        if (opcao == 'e') {
            atual = atual->esquerda;
        } else if (opcao == 'd') {
            atual = atual->direita;
        } else if (opcao == 's') {
            break;
        } else {
            printf("Opcao invalida!\n");
        }
    }
}

// Function that verifies final suspect accusation
// Funcao que verifica o suspeito final acusado
void verificarSuspeitoFinal(PistaNode* pistas) {

    char acusado[50];
    int contador = 0;

    printf("\nDigite o nome do suspeito que voce deseja acusar: ");
    scanf("%s", acusado);

    PistaNode* pilha[50];
    int topo = -1;
    PistaNode* atual = pistas;

    // Traverse BST to count clues for suspect
    // Percorre BST para contar pistas do suspeito
    while (topo != -1 || atual != NULL) {

        if (atual != NULL) {
            pilha[++topo] = atual;
            atual = atual->esquerda;
        } else {
            atual = pilha[topo--];

            char* suspeito = encontrarSuspeito(atual->pista);

            if (suspeito != NULL && strcmp(suspeito, acusado) == 0) {
                contador++;
            }

            atual = atual->direita;
        }
    }

    // Final decision
    // Decisao final
    if (contador >= 2) {
        printf("\nHa provas suficientes! %s e o culpado!\n", acusado);
    } else {
        printf("\nProvas insuficientes para acusar %s.\n", acusado);
    }
}

// Main function that builds the entire game
// Funcao principal que monta todo o jogo
int main() {

    // Initialize hash table
    // Inicializa tabela hash
    for (int i = 0; i < TAM_HASH; i++) {
        tabelaHash[i] = NULL;
    }

    // Create mansion rooms
    // Cria os comodos da mansao
    Sala* hall = criarSala("Hall", "Faca suja");
    Sala* biblioteca = criarSala("Biblioteca", "Bilhete rasgado");
    Sala* cozinha = criarSala("Cozinha", "Copo quebrado");
    Sala* escritorio = criarSala("Escritorio", "Luvas pretas");
    Sala* jardim = criarSala("Jardim", "Pegadas na lama");

    // Build binary tree map
    // Monta o mapa em arvore binaria
    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = escritorio;
    cozinha->direita = jardim;

    // Insert clues and suspects in hash table
    // Insere pistas e suspeitos na tabela hash
    inserirNaHash("Faca suja", "Carlos");
    inserirNaHash("Bilhete rasgado", "Ana");
    inserirNaHash("Copo quebrado", "Carlos");
    inserirNaHash("Luvas pretas", "Bruno");
    inserirNaHash("Pegadas na lama", "Ana");

    PistaNode* arvorePistas = NULL;

    // Start exploration
    // Inicia exploracao
    explorarSalas(hall, &arvorePistas);

    // Show collected clues
    // Exibe pistas coletadas
    printf("\nPistas coletadas:\n");
    exibirPistas(arvorePistas);

    // Final judgment
    // Julgamento final
    verificarSuspeitoFinal(arvorePistas);

    return 0;
}
