#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 5

// Struct to represent a Tetris piece
// Estrutura para representar uma peça do Tetris
typedef struct {
    char nome;
    int id;
} Peca;

// Queue structure
// Estrutura da fila
typedef struct {
    Peca fila[TAMANHO];
    int inicio;
    int fim;
    int quantidade;
} Fila;

int proximoId = 0;

// Function to initialize the queue
// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Function to generate a new piece
// Função para gerar uma nova peça automaticamente
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    p.nome = tipos[rand() % 4];
    p.id = proximoId++;

    return p;
}

// Function to check if queue is full
// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == TAMANHO;
}

// Function to check if queue is empty
// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Function to insert a piece in the queue
// Função para inserir peça na fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel inserir nova peca.\n");
        return;
    }

    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAMANHO;
    f->quantidade++;
}

// Function to remove a piece from the queue
// Função para remover peça da fila (dequeue)
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nao ha pecas para jogar.\n");
        return;
    }

    Peca removida = f->fila[f->inicio];
    printf("Peca jogada: [%c %d]\n", removida.nome, removida.id);

    f->inicio = (f->inicio + 1) % TAMANHO;
    f->quantidade--;
}

// Function to display the queue
// Função para exibir o estado atual da fila
void exibirFila(Fila *f) {
    printf("\nFila de pecas:\n");

    if (filaVazia(f)) {
        printf("[Fila vazia]\n");
        return;
    }

    int i = f->inicio;

    for (int cont = 0; cont < f->quantidade; cont++) {
        printf("[%c %d] ", f->fila[i].nome, f->fila[i].id);
        i = (i + 1) % TAMANHO;
    }

    printf("\n");
}

int main() {
    Fila fila;
    int opcao;

    srand(time(NULL));

    inicializarFila(&fila);

    // Fill queue initially with 5 pieces
    // Preenche a fila inicialmente com 5 peças
    for (int i = 0; i < TAMANHO; i++) {
        enqueue(&fila, gerarPeca());
    }

    do {
        exibirFila(&fila);

        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;

            case 2:
                enqueue(&fila, gerarPeca());
                break;

            case 0:
                printf("Encerrando o jogo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
