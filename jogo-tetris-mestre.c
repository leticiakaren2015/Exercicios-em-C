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

// Check if stack is empty
// Verifica se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Check if stack is full
// Verifica se a pilha está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

// Insert into queue
// Inserir na fila
void enqueue(Fila *f, Peca p) {
    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

// Remove from queue
// Remover da fila
Peca dequeue(Fila *f) {
    Peca p = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return p;
}

// Push into stack
// Inserir na pilha
void push(Pilha *p, Peca peca) {
    p->pilha[++p->topo] = peca;
}

// Pop from stack
// Remover da pilha
Peca pop(Pilha *p) {
    return p->pilha[p->topo--];
}

// Display queue
// Exibir fila
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
// Exibir pilha
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

// Swap front of queue with top of stack
// Troca peça da frente da fila com topo da pilha
void trocarSimples(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Nao e possivel trocar: fila ou pilha vazia.\n");
        return;
    }

    Peca temp = f->fila[f->inicio];
    f->fila[f->inicio] = p->pilha[p->topo];
    p->pilha[p->topo] = temp;

    printf("Troca simples realizada!\n");
}

// Swap first three of queue with stack
// Troca os tres primeiros da fila com a pilha
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->quantidade < 3 || p->topo < 2) {
        printf("Nao ha pecas suficientes para troca multipla.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int posFila = (f->inicio + i) % TAM_FILA;

        Peca temp = f->fila[posFila];
        f->fila[posFila] = p->pilha[p->topo - i];
        p->pilha[p->topo - i] = temp;
    }

    printf("Troca multipla realizada com sucesso!\n");
}

int main() {
    Fila fila;
    Pilha pilha;
    int opcao;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Fill queue initially
    // Preencher fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    do {
        printf("\nEstado atual:\n");
        exibirFila(&fila);
        exibirPilha(&pilha);

        printf("\nOpcoes disponiveis:\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para pilha\n");
        printf("3 - Usar peca da pilha\n");
        printf("4 - Trocar peca da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com a pilha\n");
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
                    printf("Pilha cheia!\n");
                } else {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    printf("Peca reservada: [%c %d]\n", reservada.nome, reservada.id);
                    enqueue(&fila, gerarPeca());
                }
                break;

            case 3:
                if (!pilhaVazia(&pilha)) {
                    Peca usada = pop(&pilha);
                    printf("Peca usada: [%c %d]\n", usada.nome, usada.id);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;

            case 4:
                trocarSimples(&fila, &pilha);
                break;

            case 5:
                trocaMultipla(&fila, &pilha);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
