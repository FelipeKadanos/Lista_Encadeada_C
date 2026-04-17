#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restaurante.h"

static const char *descricao_status(StatusCliente status) {
    switch (status) {
        case STATUS_RESERVA:
            return "Reserva";
        case STATUS_ESPERA:
            return "Espera";
        case STATUS_PRESENTE:
            return "Presente";
        case STATUS_ATENDIDO:
            return "Atendido";
        default:
            return "Desconhecido";
    }
}

void inicializar_lista(ListaReservas *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    lista->proximo_codigo = 1;
}

int inserir_cliente(ListaReservas *lista, const char *nome, int quantidade_pessoas, int mesa_desejada, StatusCliente status) {
    NoReserva *novo = (NoReserva *)malloc(sizeof(NoReserva));

    if (novo == NULL) {
        return 0;
    }

    novo->codigo = lista->proximo_codigo++;
    strncpy(novo->nome, nome, TAM_NOME - 1);
    novo->nome[TAM_NOME - 1] = '\0';
    novo->quantidade_pessoas = quantidade_pessoas;
    novo->mesa_desejada = mesa_desejada;
    novo->status = status;
    novo->anterior = lista->fim;
    novo->proximo = NULL;

    if (lista->fim != NULL) {
        lista->fim->proximo = novo;
    } else {
        lista->inicio = novo;
    }

    lista->fim = novo;
    lista->tamanho++;
    return 1;
}

static void desconectar_no(ListaReservas *lista, NoReserva *atual) {
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

    lista->tamanho--;
}

int remover_cliente(ListaReservas *lista, int codigo) {
    NoReserva *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            desconectar_no(lista, atual);
            free(atual);
            return 1;
        }
        atual = atual->proximo;
    }

    return 0;
}

int confirmar_chegada(ListaReservas *lista, int codigo) {
    NoReserva *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->codigo == codigo && atual->status != STATUS_ATENDIDO) {
            atual->status = STATUS_PRESENTE;
            return 1;
        }
        atual = atual->proximo;
    }

    return 0;
}

int atender_proximo_cliente(ListaReservas *lista) {
    NoReserva *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->status == STATUS_PRESENTE) {
            atual->status = STATUS_ATENDIDO;
            return 1;
        }

        if (atual->status == STATUS_ESPERA) {
            atual->status = STATUS_ATENDIDO;
            return 1;
        }

        atual = atual->proximo;
    }

    return 0;
}

const NoReserva *buscar_cliente(const ListaReservas *lista, int codigo) {
    NoReserva *atual = lista->inicio;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

void exibir_cliente(const NoReserva *cliente) {
    printf("\nCodigo: %d\n", cliente->codigo);
    printf("Nome: %s\n", cliente->nome);
    printf("Pessoas: %d\n", cliente->quantidade_pessoas);
    printf("Mesa desejada: %d\n", cliente->mesa_desejada);
    printf("Status: %s\n", descricao_status(cliente->status));
}

void listar_clientes(const ListaReservas *lista) {
    NoReserva *atual = lista->inicio;

    if (atual == NULL) {
        printf("Nenhum registro cadastrado.\n");
        return;
    }

    printf("\n=== Registros do Restaurante ===\n");
    while (atual != NULL) {
        exibir_cliente(atual);
        atual = atual->proximo;
    }
}

void exibir_resumo(const ListaReservas *lista) {
    int reservas = 0;
    int espera = 0;
    int presentes = 0;
    int atendidos = 0;
    NoReserva *atual = lista->inicio;

    while (atual != NULL) {
        switch (atual->status) {
            case STATUS_RESERVA:
                reservas++;
                break;
            case STATUS_ESPERA:
                espera++;
                break;
            case STATUS_PRESENTE:
                presentes++;
                break;
            case STATUS_ATENDIDO:
                atendidos++;
                break;
            default:
                break;
        }
        atual = atual->proximo;
    }

    printf("\n=== Resumo ===\n");
    printf("Total de registros: %d\n", lista->tamanho);
    printf("Reservas aguardando: %d\n", reservas);
    printf("Lista de espera: %d\n", espera);
    printf("Clientes presentes: %d\n", presentes);
    printf("Clientes atendidos: %d\n", atendidos);
}

void liberar_lista(ListaReservas *lista) {
    NoReserva *atual = lista->inicio;

    while (atual != NULL) {
        NoReserva *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    inicializar_lista(lista);
}
