#ifndef LISTA_PEDIDOS_H
#define LISTA_PEDIDOS_H

#define TAM_NOME 100 // Tamanho maximo do nome do cliente
#define TAM_STATUS 40 // Tamanho maximo do status do pedido

typedef struct {                    // Dados do pedido
    int id;                         // ID do pedido
    char nome_cliente[TAM_NOME];    // Nome do cliente
    float valor_total;              // Valor do pedido
    char status[TAM_STATUS];        // Status atual
} Pedido;

typedef struct NoPedido {       // No da lista
    Pedido pedido;              // Pedido armazenado
    struct NoPedido *anterior;  // No anterior
    struct NoPedido *proximo;   // Proximo no
} NoPedido;

typedef struct {        // Controle da lista
    NoPedido *inicio;   // Primeiro no
    NoPedido *fim;      // Ultimo no
    int quantidade;     // Total de pedidos
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
