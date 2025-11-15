#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um nó da árvore binária (sala)
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura para representar um nó da árvore de busca (pista)
typedef struct Pista {
    char descricao[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

// Função para criar um novo nó (sala)
Sala* criarSala(char* nome) {
    Sala* sala = (Sala*) malloc(sizeof(Sala));
    strcpy(sala->nome, nome);
    sala->esquerda = NULL;
    sala->direita = NULL;
    return sala;
}

// Função para criar um novo nó (pista)
Pista* criarPista(char* descricao) {
    Pista* pista = (Pista*) malloc(sizeof(Pista));
    strcpy(pista->descricao, descricao);
    pista->esquerda = NULL;
    pista->direita = NULL;
    return pista;
}

// Função para inserir uma pista na árvore de busca
Pista* inserirPista(Pista* raiz, char* descricao) {
    if (raiz == NULL) {
        return criarPista(descricao);
    }

    if (strcmp(descricao, raiz->descricao) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, descricao);
    } else if (strcmp(descricao, raiz->descricao) > 0) {
        raiz->direita = inserirPista(raiz->direita, descricao);
    }

    return raiz;
}

// Função para exibir as pistas em ordem alfabética
void emOrdem(Pista* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%s\n", raiz->descricao);
        emOrdem(raiz->direita);
    }
}

// Função para explorar as salas
void explorarSalas(Sala* salaAtual, Pista** pistas) {
    char escolha;

    while (1) {
        printf("Você está na sala: %s\n", salaAtual->nome);
        printf("Escolha uma opção:\n");
        printf("e - Ir para a esquerda\n");
        printf("d - Ir para a direita\n");
        printf("s - Sair da exploração\n");
        printf("p - Visualizar pistas\n");
        scanf(" %c", &escolha);

        switch (escolha) {
            case 'e':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                    if (strcmp(salaAtual->nome, "Sala 3") == 0) {
                        *pistas = inserirPista(*pistas, "Pista 1");
                        printf("Você encontrou uma pista!\n");
                    }
                } else {
                    printf("Não há sala à esquerda!\n");
                }
                break;
            case 'd':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                    if (strcmp(salaAtual->nome, "Sala 4") == 0) {
                        *pistas = inserirPista(*pistas, "Pista 2");
                        printf("Você encontrou uma pista!\n");
                    }
                } else {
                    printf("Não há sala à direita!\n");
                }
                break;
            case 's':
                printf("Saindo da exploração...\n");
                return;
            case 'p':
                printf("Pistas:\n");
                emOrdem(*pistas);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

int main() {
    // Criar as salas
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* sala1 = criarSala("Sala 1");
    Sala* sala2 = criarSala("Sala 2");
    Sala* sala3 = criarSala("Sala 3");
    Sala* sala4 = criarSala("Sala 4");

    // Conectar as salas
    hallEntrada->esquerda = sala1;
    hallEntrada->direita = sala2;
    sala1->esquerda = sala3;
    sala1->direita = sala4;

    // Criar a árvore de pistas
    Pista* pistas = NULL;

    // Iniciar a exploração
    explorarSalas(hallEntrada, &pistas);

    return 0;
}