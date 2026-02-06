#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// Struct definition for components
// Definição da struct Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Global counter for comparisons
// Contador global de comparações
int comparacoes = 0;

// Function to display components
// Função para mostrar os componentes
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s | %s | Prioridade: %d\n",
            v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// Bubble Sort by name
// Ordenação Bubble Sort por nome
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;

            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort by type
// Ordenação Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = chave;
    }
}

// Selection Sort by priority
// Ordenação Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;

            if (v[j].prioridade < v[menor].prioridade)
                menor = j;
        }

        Componente temp = v[i];
        v[i] = v[menor];
        v[menor] = temp;
    }
}

// Binary search by name
// Busca binária por nome
void buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int inicio = 0, fim = n - 1;
    comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) {
            printf("\nComponente encontrado: %s | %s | Prioridade %d\n",
                v[meio].nome, v[meio].tipo, v[meio].prioridade);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nComponente nao encontrado!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

// Function to measure time
// Função para medir tempo de execução
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio, fim;

    inicio = clock();
    algoritmo(v, n);
    fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Comparacoes: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
}

// ===== MAIN PROGRAM =====
// ===== PROGRAMA PRINCIPAL =====

int main() {
    Componente componentes[MAX];
    int total = 0;
    int opcao;

    do {
        printf("\n=== SISTEMA DE TORRE DE FUGA ===\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Ordenar por NOME (Bubble Sort)\n");
        printf("3 - Ordenar por TIPO (Insertion Sort)\n");
        printf("4 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5 - Buscar componente-chave (Busca Binaria)\n");
        printf("6 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

        case 1:
            if (total >= MAX) {
                printf("Limite atingido!\n");
                break;
            }

            printf("Nome: ");
            fgets(componentes[total].nome, 30, stdin);
            componentes[total].nome[strcspn(componentes[total].nome, "\n")] = 0;

            printf("Tipo: ");
            fgets(componentes[total].tipo, 20, stdin);
            componentes[total].tipo[strcspn(componentes[total].tipo, "\n")] = 0;

            printf("Prioridade (1-10): ");
            scanf("%d", &componentes[total].prioridade);
            getchar();

            total++;
            break;

        case 2:
            medirTempo(bubbleSortNome, componentes, total);
            printf("Ordenado por nome!\n");
            break;

        case 3:
            medirTempo(insertionSortTipo, componentes, total);
            printf("Ordenado por tipo!\n");
            break;

        case 4:
            medirTempo(selectionSortPrioridade, componentes, total);
            printf("Ordenado por prioridade!\n");
            break;

        case 5: {
            char chave[30];
            printf("Nome do componente-chave: ");
            fgets(chave, 30, stdin);
            chave[strcspn(chave, "\n")] = 0;

            buscaBinariaPorNome(componentes, total, chave);
            break;
        }

        case 6:
            mostrarComponentes(componentes, total);
            break;
        }

    } while (opcao != 0);

    printf("Sistema encerrado!\n");
    return 0;
}
