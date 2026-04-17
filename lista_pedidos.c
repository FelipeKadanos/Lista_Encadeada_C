#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_pedidos.h"

static NoPedido *criar_no(Pedido pedido) {
    NoPedido *novo_no = (NoPedido *)malloc(sizeof(NoPedido));

    if (novo_no == NULL) {
        return NULL;
    }

    novo_no->pedido = pedido;
    novo_no->anterior = NULL;
    novo_no->proximo = NULL;
    return novo_no;
}

void inicializar_lista(ListaPedidos *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantidade = 0;
}

int lista_vazia(const ListaPedidos *lista) {
    return lista->inicio == NULL;
}

int id_ja_cadastrado(const ListaPedidos *lista, int id) {
    NoPedido *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->pedido.id == id) {
            return 1;
        }
        atual = atual->proximo;
    }

    return 0;
}

int inserir_no_inicio(ListaPedidos *lista, Pedido pedido) {
    NoPedido *novo_no = criar_no(pedido);

    if (novo_no == NULL) {
        return 0;
    }

    if (lista_vazia(lista)) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        /* O novo pedido prioritario passa a ser o primeiro da fila. */
        novo_no->proximo = lista->inicio;
        lista->inicio->anterior = novo_no;
        lista->inicio = novo_no;
    }

    lista->quantidade++;
    return 1;
}

int inserir_no_fim(ListaPedidos *lista, Pedido pedido) {
    NoPedido *novo_no = criar_no(pedido);

    if (novo_no == NULL) {
        return 0;
    }

    if (lista_vazia(lista)) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        /* Mantem a ordem de chegada ligando o novo pedido ao antigo ultimo no. */
        novo_no->anterior = lista->fim;
        lista->fim->proximo = novo_no;
        lista->fim = novo_no;
    }

    lista->quantidade++;
    return 1;
}

int remover_por_id(ListaPedidos *lista, int id) {
    NoPedido *atual = lista->inicio;

    while (atual != NULL && atual->pedido.id != id) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 0;
    }

    /* Ajusta os encadeamentos nos casos de remocao do inicio, meio ou fim. */
    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        lista->inicio = atual->proximo;
    }

    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    } else {
        lista->fim = atual->anterior;
    }

    free(atual);
    lista->quantidade--;
    return 1;
}

static void exibir_pedido(const Pedido *pedido) {
    printf("ID: %d\n", pedido->id);
    printf("Cliente: %s\n", pedido->nome_cliente);
    printf("Valor total: R$ %.2f\n", pedido->valor_total);
    printf("Status: %s\n", pedido->status);
    printf("-----------------------------\n");
}

void exibir_do_inicio(const ListaPedidos *lista) {
    NoPedido *atual = lista->inicio;

    if (lista_vazia(lista)) {
        printf("A lista de pedidos esta vazia.\n");
        return;
    }

    printf("\nPedidos do inicio para o fim:\n");
    printf("-----------------------------\n");

    while (atual != NULL) {
        exibir_pedido(&atual->pedido);
        atual = atual->proximo;
    }
}

void exibir_do_fim(const ListaPedidos *lista) {
    NoPedido *atual = lista->fim;

    if (lista_vazia(lista)) {
        printf("A lista de pedidos esta vazia.\n");
        return;
    }

    printf("\nPedidos do fim para o inicio:\n");
    printf("-----------------------------\n");

    while (atual != NULL) {
        exibir_pedido(&atual->pedido);
        atual = atual->anterior;
    }
}

void liberar_lista(ListaPedidos *lista) {
    NoPedido *atual = lista->inicio;

    /* Libera todos os nos alocados dinamicamente antes de encerrar o programa. */
    while (atual != NULL) {
        NoPedido *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    inicializar_lista(lista);
}
