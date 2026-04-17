#ifndef LISTA_PEDIDOS_H
#define LISTA_PEDIDOS_H

#define TAM_NOME 100
#define TAM_STATUS 40

typedef struct {
    int id;
    char nome_cliente[TAM_NOME];
    float valor_total;
    char status[TAM_STATUS];
} Pedido;

typedef struct NoPedido {
    Pedido pedido;
    struct NoPedido *anterior;
    struct NoPedido *proximo;
} NoPedido;

typedef struct {
    NoPedido *inicio;
    NoPedido *fim;
    int quantidade;
} ListaPedidos;

void inicializar_lista(ListaPedidos *lista);
int lista_vazia(const ListaPedidos *lista);
int id_ja_cadastrado(const ListaPedidos *lista, int id);
int inserir_no_inicio(ListaPedidos *lista, Pedido pedido);
int inserir_no_fim(ListaPedidos *lista, Pedido pedido);
int remover_por_id(ListaPedidos *lista, int id);
void exibir_do_inicio(const ListaPedidos *lista);
void exibir_do_fim(const ListaPedidos *lista);
void liberar_lista(ListaPedidos *lista);

#endif
