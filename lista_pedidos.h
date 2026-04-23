#ifndef LISTA_PEDIDOS_H
#define LISTA_PEDIDOS_H

/* Tamanho maximo do nome do cliente armazenado no pedido. */
#define TAM_NOME 100
/* Tamanho maximo do texto usado para o status do pedido. */
#define TAM_STATUS 40

/* Representa os dados principais de um pedido cadastrado no sistema. */
typedef struct {
    /* Identificador unico do pedido. */
    int id;
    /* Nome do cliente responsavel pelo pedido. */
    char nome_cliente[TAM_NOME];
    /* Valor total cobrado pelo pedido. */
    float valor_total;
    /* Situacao atual do pedido, como "Em preparo" ou "Entregue". */
    char status[TAM_STATUS];
} Pedido;

/* No da lista duplamente encadeada que guarda um pedido. */
typedef struct NoPedido {
    /* Dados do pedido armazenado neste no. */
    Pedido pedido;
    /* Ponteiro para o no anterior da lista. */
    struct NoPedido *anterior;
    /* Ponteiro para o proximo no da lista. */
    struct NoPedido *proximo;
} NoPedido;

/* Estrutura principal usada para controlar o inicio, fim e tamanho da lista. */
typedef struct {
    /* Primeiro no da lista. */
    NoPedido *inicio;
    /* Ultimo no da lista. */
    NoPedido *fim;
    /* Quantidade atual de pedidos armazenados. */
    int quantidade;
} ListaPedidos;

/**
 * Inicializa a lista recebida.
 * @param lista Ponteiro valido para a lista que sera inicializada.
 * @return Nao retorna valor.
 */
void inicializar_lista(ListaPedidos *lista);
/**
 * Verifica se a lista esta vazia.
 * @param lista Lista que sera consultada.
 * @return int 1 se a lista estiver vazia ou 0 caso contrario.
 */
int lista_vazia(const ListaPedidos *lista);
/**
 * Procura o ID informado na lista.
 * @param lista Lista onde a busca sera realizada.
 * @param id Identificador do pedido procurado.
 * @return int 1 se o ID ja existir ou 0 caso contrario.
 */
int id_ja_cadastrado(const ListaPedidos *lista, int id);
/**
 * Insere um pedido no inicio da lista.
 * @param lista Lista que recebera o pedido.
 * @param pedido Estrutura preenchida com os dados do pedido.
 * @return int 1 se a insercao ocorrer com sucesso ou 0 em caso de falha.
 */
int inserir_no_inicio(ListaPedidos *lista, Pedido pedido);
/**
 * Insere um pedido no final da lista.
 * @param lista Lista que recebera o pedido.
 * @param pedido Estrutura preenchida com os dados do pedido.
 * @return int 1 se a insercao ocorrer com sucesso ou 0 em caso de falha.
 */
int inserir_no_fim(ListaPedidos *lista, Pedido pedido);
/**
 * Remove o pedido com o ID informado.
 * @param lista Lista de onde o pedido sera removido.
 * @param id Identificador do pedido que sera excluido.
 * @return int 1 se o pedido for removido ou 0 se ele nao for encontrado.
 */
int remover_por_id(ListaPedidos *lista, int id);
/**
 * Exibe todos os pedidos do primeiro ate o ultimo no.
 * @param lista Lista que sera exibida.
 * @return Nao retorna valor.
 */
void exibir_do_inicio(const ListaPedidos *lista);
/**
 * Exibe todos os pedidos do ultimo ate o primeiro no.
 * @param lista Lista que sera exibida.
 * @return Nao retorna valor.
 */
void exibir_do_fim(const ListaPedidos *lista);
/**
 * Libera toda a memoria da lista e a deixa vazia novamente.
 * @param lista Lista cujos elementos serao desalocados.
 * @return Nao retorna valor.
 */
void liberar_lista(ListaPedidos *lista);

#endif
