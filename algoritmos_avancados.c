#include <stdio.h>
#include <stdlib.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

Sala* criarSala(char* nome) {
    Sala* sala = (Sala*) malloc(sizeof(Sala));
    strcpy(sala->nome, nome);
    sala->esquerda = NULL;
    sala->direita = NULL;
    return sala;
}

void explorarSalas(Sala* salaAtual) {
    char escolha;

    while (1) {
        printf("Você está na sala: %s\n", salaAtual->nome);
        printf("Escolha uma opção:\n");
        printf("e - Ir para a esquerda\n");
        printf("d - Ir para a direita\n");
        printf("s - Sair da exploração\n");
        scanf(" %c", &escolha);

        switch (escolha) {
            case 'e':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("Não há sala à esquerda!\n");
                }
                break;
            case 'd':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("Não há sala à direita!\n");
                }
                break;
            case 's':
                printf("Saindo da exploração...\n");
                return;
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

    // Iniciar a exploração
    explorarSalas(hallEntrada); 


    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}

