#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#define TAM_NOME 80

typedef enum {
    STATUS_RESERVA = 1,
    STATUS_ESPERA = 2,
    STATUS_PRESENTE = 3,
    STATUS_ATENDIDO = 4
} StatusCliente;

typedef struct NoReserva {
    int codigo;
    char nome[TAM_NOME];
    int quantidade_pessoas;
    int mesa_desejada;
    StatusCliente status;
    struct NoReserva *anterior;
    struct NoReserva *proximo;
} NoReserva;

typedef struct {
    NoReserva *inicio;
    NoReserva *fim;
    int tamanho;
    int proximo_codigo;
} ListaReservas;

void inicializar_lista(ListaReservas *lista);
int inserir_cliente(ListaReservas *lista, const char *nome, int quantidade_pessoas, int mesa_desejada, StatusCliente status);
int remover_cliente(ListaReservas *lista, int codigo);
int confirmar_chegada(ListaReservas *lista, int codigo);
int atender_proximo_cliente(ListaReservas *lista);
const NoReserva *buscar_cliente(const ListaReservas *lista, int codigo);
void listar_clientes(const ListaReservas *lista);
void exibir_cliente(const NoReserva *cliente);
void exibir_resumo(const ListaReservas *lista);
void liberar_lista(ListaReservas *lista);

#endif
