#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct definition for an item
// Definição da struct para um item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Global array to store items
// Vetor global para armazenar os itens
Item mochila[MAX_ITENS];
int totalItens = 0;

// Function prototypes
// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

int main() {
    int opcao;

    do {
        printf("\n=== Sistema de Inventario ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o \n do buffer

        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

// Function to insert an item into the inventory
// Função para inserir um item na mochila
void inserirItem() {
    if(totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove newline

    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar(); // Limpar o \n do buffer

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("Item inserido com sucesso!\n");
    listarItens();
}

// Function to remove an item by name
// Função para remover um item pelo nome
void removerItem() {
    if(totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int encontrado = 0;
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            // Shift items to fill the gap
            for(int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            totalItens--;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if(!encontrado) {
        printf("Item nao encontrado!\n");
    }

    listarItens();
}

// Function to list all items
// Função para listar todos os itens
void listarItens() {
    if(totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for(int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Function to search for an item by name
// Função para buscar um item pelo nome
void buscarItem() {
    if(totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("Item nao encontrado!\n");
}
