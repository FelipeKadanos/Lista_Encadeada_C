#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_pedidos.h"

/**
 * Cria um novo no para armazenar o pedido informado.
 * @param pedido Estrutura com os dados que serao copiados para o novo no.
 * @return NoPedido*|NULL Ponteiro para o no criado ou NULL em caso de falha na alocacao.
 */
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

/**
 * Define a lista como vazia antes do primeiro uso.
 * @param lista Ponteiro para a lista que sera inicializada.
 * @return Nao retorna valor.
 */
void inicializar_lista(ListaPedidos *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantidade = 0;
}

/**
 * Verifica se ainda nao existe nenhum pedido armazenado.
 * @param lista Lista que sera consultada.
 * @return int 1 se a lista estiver vazia ou 0 caso contrario.
 */
int lista_vazia(const ListaPedidos *lista) {
    return lista->inicio == NULL;
}

/**
 * Percorre a lista para descobrir se o ID informado ja esta em uso.
 * @param lista Lista onde a busca sera realizada.
 * @param id Identificador do pedido que sera procurado.
 * @return int 1 se o ID ja existir ou 0 caso contrario.
 */
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

/**
 * Adiciona um pedido prioritario no inicio da lista.
 * @param lista Lista que recebera o novo pedido.
 * @param pedido Dados do pedido que sera inserido.
 * @return int 1 se a insercao ocorrer com sucesso ou 0 em caso de falha.
 */
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

/**
 * Adiciona um pedido comum no final da lista.
 * @param lista Lista que recebera o novo pedido.
 * @param pedido Dados do pedido que sera inserido.
 * @return int 1 se a insercao ocorrer com sucesso ou 0 em caso de falha.
 */
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

/**
 * Remove da lista o pedido que possui o ID informado.
 * @param lista Lista de onde o pedido sera removido.
 * @param id Identificador do pedido que deve ser excluido.
 * @return int 1 se o pedido for removido ou 0 se ele nao for encontrado.
 */
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

/**
 * Mostra na tela os campos de um unico pedido.
 * @param pedido Pedido que sera exibido.
 * @return Nao retorna valor.
 */
static void exibir_pedido(const Pedido *pedido) {
    printf("ID: %d\n", pedido->id);
    printf("Cliente: %s\n", pedido->nome_cliente);
    printf("Valor total: R$ %.2f\n", pedido->valor_total);
    printf("Status: %s\n", pedido->status);
    printf("-----------------------------\n");
}

/**
 * Exibe todos os pedidos caminhando do inicio para o fim da lista.
 * @param lista Lista que sera percorrida para exibicao.
 * @return Nao retorna valor.
 */
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

/**
 * Exibe todos os pedidos caminhando do fim para o inicio da lista.
 * @param lista Lista que sera percorrida para exibicao.
 * @return Nao retorna valor.
 */
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

/**
 * Libera todos os nos alocados e reinicia a estrutura da lista.
 * @param lista Lista cujos elementos serao desalocados.
 * @return Nao retorna valor.
 */
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
