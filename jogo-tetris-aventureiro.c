#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Struct to represent a piece
// Estrutura para representar uma peça
typedef struct {
    char nome;
    int id;
} Peca;

// Circular queue structure
// Estrutura da fila circular
typedef struct {
    Peca fila[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Stack structure
// Estrutura da pilha
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo;
} Pilha;

int proximoId = 0;

// Function to generate a new piece
// Função para gerar uma nova peça
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    p.nome = tipos[rand() % 4];
    p.id = proximoId++;

    return p;
}

// Initialize queue
// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Initialize stack
// Inicializa a pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Check if queue is empty
// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Check if queue is full
// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

// Check if stack is full
// Verifica se a pilha está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

// Check if stack is empty
// Verifica se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Insert piece into queue
// Insere peça na fila
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) return;

    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

// Remove piece from queue
// Remove peça da fila
Peca dequeue(Fila *f) {
    Peca p = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return p;
}

// Push piece into stack
// Insere peça na pilha
void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("Pilha de reserva cheia!\n");
        return;
    }

    p->topo++;
    p->pilha[p->topo] = peca;
}

// Pop piece from stack
// Remove peça da pilha
Peca pop(Pilha *p) {
    return p->pilha[p->topo--];
}

// Display queue
// Exibe a fila
void exibirFila(Fila *f) {
    printf("Fila de pecas: ");

    int i = f->inicio;
    for (int c = 0; c < f->quantidade; c++) {
        printf("[%c %d] ", f->fila[i].nome, f->fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

// Display stack
// Exibe a pilha
void exibirPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");

    if (pilhaVazia(p)) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pilha[i].nome, p->pilha[i].id);
        }
    }
    printf("\n");
}

int main() {
    Fila fila;
    Pilha pilha;
    int opcao;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Fill initial queue
    // Preenche fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    do {
        printf("\nEstado atual:\n");
        exibirFila(&fila);
        exibirPilha(&pilha);

        printf("\nOpcoes:\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);

                    enqueue(&fila, gerarPeca());
                }
                break;

            case 2:
                if (pilhaCheia(&pilha)) {
                    printf("Nao e possivel reservar: pilha cheia!\n");
                } else if (!filaVazia(&fila)) {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    printf("Peca reservada: [%c %d]\n", reservada.nome, reservada.id);

                    enqueue(&fila, gerarPeca());
                }
                break;

            case 3:
                if (pilhaVazia(&pilha)) {
                    printf("Nao ha pecas na reserva!\n");
                } else {
                    Peca usada = pop(&pilha);
                    printf("Peca usada da reserva: [%c %d]\n", usada.nome, usada.id);
                }
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
