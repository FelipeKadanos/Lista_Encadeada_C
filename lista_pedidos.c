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
 * @return int|bool 1|true se a lista estiver vazia ou 0|false caso contrario.
 */
int lista_vazia(const ListaPedidos *lista) {
    return lista->inicio == NULL;
}

/**
 * Percorre a lista para descobrir se o ID informado ja esta em uso.
 * @param lista Lista onde a busca sera realizada.
 * @param id Identificador do pedido que sera procurado.
 * @return int|bool 1|true se o ID ja existir ou 0|false caso contrario.
 */
int id_ja_cadastrado(const ListaPedidos *lista, int id) {
    NoPedido *atual = lista->inicio;

    /* Faz uma busca linear porque os pedidos ficam armazenados na ordem de insercao. */
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
 * @return int|bool 1|true se a insercao ocorrer com sucesso ou 0|false em caso de falha.
 */
int inserir_no_inicio(ListaPedidos *lista, Pedido pedido) {
    NoPedido *novo_no = criar_no(pedido);

    if (novo_no == NULL) {
        return 0;
    }

    /* Se a lista estiver vazia, o mesmo no passa a ser inicio e fim ao mesmo tempo. */
    if (lista_vazia(lista)) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        /*
         * Na insercao no inicio, o novo no aponta para o antigo primeiro elemento.
         * Depois atualizamos o ponteiro "anterior" do antigo inicio para manter o
         * encadeamento duplo consistente nos dois sentidos.
         */
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
 * @return int|bool 1|true se a insercao ocorrer com sucesso ou 0|false em caso de falha.
 */
int inserir_no_fim(ListaPedidos *lista, Pedido pedido) {
    NoPedido *novo_no = criar_no(pedido);

    if (novo_no == NULL) {
        return 0;
    }

    /* Se a lista estiver vazia, o primeiro pedido tambem passa a ser o ultimo. */
    if (lista_vazia(lista)) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        /*
         * Na insercao no fim, ligamos o novo no ao antigo ultimo elemento.
         * Em seguida atualizamos o ponteiro "proximo" do antigo fim e movemos
         * o marcador de fim da lista para o novo no.
         */
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
 * @return int|bool 1|true se o pedido for removido ou 0|false se ele nao for encontrado.
 */
int remover_por_id(ListaPedidos *lista, int id) {
    NoPedido *atual = lista->inicio;

    /* Procura o primeiro no com o ID pedido, caminhando do inicio ate o fim. */
    while (atual != NULL && atual->pedido.id != id) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 0;
    }

    /*
     * A remocao precisa religar os nos vizinhos. Quando "anterior" e NULL,
     * estamos removendo o primeiro elemento; quando "proximo" e NULL, estamos
     * removendo o ultimo. Se ambos existirem, o no estava no meio da lista.
     */
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

    /* A leitura segue pelos ponteiros "proximo" ate chegar ao fim da lista. */
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

    /* Como a lista e duplamente encadeada, podemos voltar usando os ponteiros "anterior". */
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
        /* O proximo endereco e salvo antes do free para nao perder o restante da lista. */
        NoPedido *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    inicializar_lista(lista);
}
