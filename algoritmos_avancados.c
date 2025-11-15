
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

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

// Estrutura para representar um nó da tabela hash (suspeito)
typedef struct NoHash {
    char suspeito[50];
    char pistas[10][100];
    int count;
    struct NoHash* proximo;
} NoHash;

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

// Função para criar um novo nó (suspeito)
NoHash* criarNoHash(char* suspeito) {
    NoHash* no = (NoHash*) malloc(sizeof(NoHash));
    strcpy(no->suspeito, suspeito);
    no->count = 0;
    no->proximo = NULL;
    return no;
}

// Função para calcular o índice da tabela hash
int hash(char* pista) {
    int soma = 0;
    for (int i = 0; i < strlen(pista); i++) {
        soma += pista[i];
    }
    return soma % 10;
}

// Função para inserir uma pista na árvore de busca
Pista* inserirPista(Pista* raiz, char* descricao) {
    if (raiz == NULL) {
        raiz = criarPista(descricao);
    } else if (strcmp(descricao, raiz->descricao) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, descricao);
    } else if (strcmp(descricao, raiz->descricao) > 0) {
        raiz->direita = inserirPista(raiz->direita, descricao);
    }
    return raiz;
}

// Função para exibir as pistas em ordem alfabética
void exibirPistas(Pista* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("%s\n", raiz->descricao);
        exibirPistas(raiz->direita);
    }
}

// Função para inserir uma pista na tabela hash
void inserirNaHash(NoHash** tabelaHash, char* pista, char* suspeito) {
    int indice = hash(pista);
    if (tabelaHash[indice] == NULL) {
        tabelaHash[indice] = criarNoHash(suspeito);
        strcpy(tabelaHash[indice]->pistas[tabelaHash[indice]->count], pista);
        tabelaHash[indice]->count++;
    } else {
        NoHash* atual = tabelaHash[indice];
        while (atual->proximo != NULL) {
            if (strcmp(atual->suspeito, suspeito) == 0) {
                strcpy(atual->pistas[atual->count], pista);
                atual->count++;
                return;
            }
            atual = atual->proximo;
        }
        if (strcmp(atual->suspeito, suspeito) == 0) {
            strcpy(atual->pistas[atual->count], pista);
            atual->count++;
        } else {
            atual->proximo = criarNoHash(suspeito);
            strcpy(atual->proximo->pistas[atual->proximo->count], pista);
            atual->proximo->count++;
        }
    }
}

// Função para exibir as pistas associadas a cada suspeito
void listarAssociacoes(NoHash** tabelaHash) {
    for (int i = 0; i < 10; i++) {
        NoHash* atual = tabelaHash[i];
        while (atual != NULL) {
            printf("Suspeito: %s\n", atual->suspeito);
            for (int j = 0; j < atual->count; j++) {
                printf(" Pista: %s\n", atual->pistas[j]);
            }
            atual = atual->proximo;
        }
    }
}

// Função para encontrar o suspeito mais relatado
void encontrarSuspeitoMaisRelatado(NoHash** tabelaHash) {
    int maxCount = 0;
    char suspeitoMaisRelatado[50];
    for (int i = 0; i < 10; i++) {
        NoHash* atual = tabelaHash[i];
        while (atual != NULL) {
            if (atual->count > maxCount) {
                maxCount = atual->count;
                strcpy(suspeitoMaisRelatado, atual->suspeito);
            }
            atual = atual->proximo; // Adicione essa linha
        }
    }
    printf("Suspeito mais relatado: %s com %d relatos\n", suspeitoMaisRelatado, maxCount);
}

// Função para explorar as salas
void explorarSalas(Sala* salaAtual, Pista** pistas, NoHash** tabelaHash) {
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
                        inserirNaHash(tabelaHash, "Pista 1", "Suspeito 1");
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
                        inserirNaHash(tabelaHash, "Pista 2", "Suspeito 2");
                        printf("Você encontrou uma pista!\n");
                    }
                } else {
                    printf("Não há sala à direita!\n");
                }
                break;
            case 's':
                printf("Saindo da exploração...\n");
                listarAssociacoes(tabelaHash);
                encontrarSuspeitoMaisRelatado(tabelaHash);
                return;
            case 'p':
                printf("Pistas:\n");
                exibirPistas(*pistas);
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

    // Inicializar a árvore de pistas
    Pista* pistas = NULL;

    // Inicializar a tabela hash
    NoHash* tabelaHash[10];
    for (int i = 0; i < 10; i++) {
        tabelaHash[i] = NULL;
    }

    // Iniciar a exploração
    explorarSalas(hallEntrada, &pistas, tabelaHash);

    return 0;
}