#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct for item
// Struct que representa um item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct for linked list node
// Struct para nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ===== GLOBAL VARIABLES =====
// ===== VARIÁVEIS GLOBAIS =====

Item vetor[MAX_ITENS];
int totalVetor = 0;

No* inicioLista = NULL;

int comparacoes = 0;

// ===== FUNCTIONS FOR VECTOR =====
// ===== FUNÇÕES PARA VETOR =====

void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Mochila (vetor) cheia!\n");
        return;
    }

    Item novo;

    printf("Nome: ");
    scanf("%s", novo.nome);

    printf("Tipo: ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    vetor[totalVetor++] = novo;

    printf("Item inserido no vetor!\n");
}

void listarVetor() {
    printf("\n--- ITENS NO VETOR ---\n");

    for (int i = 0; i < totalVetor; i++) {
        printf("%s | %s | %d\n",
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].quantidade);
    }
}

void removerItemVetor() {
    char nome[30];
    printf("Nome do item para remover: ");
    scanf("%s", nome);

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {

            for (int j = i; j < totalVetor - 1; j++)
                vetor[j] = vetor[j + 1];

            totalVetor--;

            printf("Item removido do vetor!\n");
            return;
        }
    }

    printf("Item nao encontrado no vetor!\n");
}

void buscarSequencialVetor() {
    char nome[30];
    comparacoes = 0;

    printf("Nome para busca: ");
    scanf("%s", nome);

    for (int i = 0; i < totalVetor; i++) {
        comparacoes++;

        if (strcmp(vetor[i].nome, nome) == 0) {
            printf("Encontrado no vetor: %s\n", vetor[i].nome);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
    }

    printf("Nao encontrado!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    printf("Vetor ordenado por nome!\n");
}

void buscarBinariaVetor() {
    char nome[30];
    comparacoes = 0;

    printf("Nome para busca binaria: ");
    scanf("%s", nome);

    int inicio = 0;
    int fim = totalVetor - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0) {
            printf("Encontrado: %s\n", vetor[meio].nome);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Nao encontrado!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

// ===== FUNCTIONS FOR LINKED LIST =====
// ===== FUNÇÕES PARA LISTA ENCADEADA =====

void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));

    printf("Nome: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicioLista;
    inicioLista = novo;

    printf("Item inserido na lista!\n");
}

void listarLista() {
    printf("\n--- ITENS NA LISTA ---\n");

    No* atual = inicioLista;

    while (atual != NULL) {
        printf("%s | %s | %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);

        atual = atual->proximo;
    }
}

void removerItemLista() {
    char nome[30];
    printf("Nome para remover: ");
    scanf("%s", nome);

    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {

            if (anterior == NULL)
                inicioLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido da lista!\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado na lista!\n");
}

void buscarSequencialLista() {
    char nome[30];
    comparacoes = 0;

    printf("Nome para busca: ");
    scanf("%s", nome);

    No* atual = inicioLista;

    while (atual != NULL) {
        comparacoes++;

        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Encontrado na lista: %s\n", atual->dados.nome);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }

        atual = atual->proximo;
    }

    printf("Nao encontrado!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

// ===== MENU =====

int main() {
    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir no vetor\n");
        printf("2 - Listar vetor\n");
        printf("3 - Remover do vetor\n");
        printf("4 - Busca sequencial no vetor\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Busca binaria no vetor\n");

        printf("7 - Inserir na lista\n");
        printf("8 - Listar lista\n");
        printf("9 - Remover da lista\n");
        printf("10 - Busca sequencial na lista\n");

        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: listarVetor(); break;
            case 3: removerItemVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;

            case 7: inserirItemLista(); break;
            case 8: listarLista(); break;
            case 9: removerItemLista(); break;
            case 10: buscarSequencialLista(); break;
        }

    } while (opcao != 0);

    return 0;
}
