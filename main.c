#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restaurante.h"

static void limpar_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int ler_inteiro(const char *mensagem) {
    int valor;

    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            limpar_entrada();
            return valor;
        }

        printf("Entrada invalida. Digite um numero inteiro.\n");
        limpar_entrada();
    }
}

static void ler_texto(const char *mensagem, char *destino, size_t tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, (int)tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }

    destino[strcspn(destino, "\n")] = '\0';
}

static void cadastrar_cliente(ListaReservas *lista) {
    char nome[TAM_NOME];
    int pessoas;
    int mesa;
    int opcao_reserva;
    StatusCliente status;

    ler_texto("Nome do cliente: ", nome, sizeof(nome));
    pessoas = ler_inteiro("Quantidade de pessoas: ");
    mesa = ler_inteiro("Numero da mesa desejada (0 se nao houver preferencia): ");
    opcao_reserva = ler_inteiro("Tipo de registro [1-Reserva | 2-Lista de espera]: ");

    status = (opcao_reserva == 1) ? STATUS_RESERVA : STATUS_ESPERA;

    if (inserir_cliente(lista, nome, pessoas, mesa, status)) {
        printf("Cliente cadastrado com sucesso.\n");
    } else {
        printf("Nao foi possivel cadastrar o cliente.\n");
    }
}

static void cancelar_registro(ListaReservas *lista) {
    int codigo = ler_inteiro("Codigo do registro para cancelamento: ");

    if (remover_cliente(lista, codigo)) {
        printf("Registro removido com sucesso.\n");
    } else {
        printf("Registro nao encontrado.\n");
    }
}

static void confirmar_chegada_cliente(ListaReservas *lista) {
    int codigo = ler_inteiro("Codigo da reserva/lista para confirmar chegada: ");

    if (confirmar_chegada(lista, codigo)) {
        printf("Chegada confirmada.\n");
    } else {
        printf("Nao foi possivel confirmar a chegada.\n");
    }
}

static void liberar_mesa_cliente(ListaReservas *lista) {
    if (atender_proximo_cliente(lista)) {
        printf("Mesa liberada e proximo cliente atendido.\n");
    } else {
        printf("Nenhum cliente apto para atendimento no momento.\n");
    }
}

static void buscar_cliente_menu(const ListaReservas *lista) {
    int codigo = ler_inteiro("Codigo do cliente: ");
    const NoReserva *cliente = buscar_cliente(lista, codigo);

    if (cliente == NULL) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    exibir_cliente(cliente);
}

static void exibir_menu(void) {
    printf("\n=== Sistema de Restaurante ===\n");
    printf("1. Cadastrar reserva ou espera\n");
    printf("2. Cancelar registro\n");
    printf("3. Confirmar chegada do cliente\n");
    printf("4. Liberar mesa para o proximo cliente\n");
    printf("5. Listar registros\n");
    printf("6. Buscar cliente por codigo\n");
    printf("7. Exibir resumo\n");
    printf("0. Sair\n");
}

int main(void) {
    ListaReservas lista;
    int opcao;

    inicializar_lista(&lista);

    do {
        exibir_menu();
        opcao = ler_inteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrar_cliente(&lista);
                break;
            case 2:
                cancelar_registro(&lista);
                break;
            case 3:
                confirmar_chegada_cliente(&lista);
                break;
            case 4:
                liberar_mesa_cliente(&lista);
                break;
            case 5:
                listar_clientes(&lista);
                break;
            case 6:
                buscar_cliente_menu(&lista);
                break;
            case 7:
                exibir_resumo(&lista);
                break;
            case 0:
                printf("Encerrando o sistema.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    liberar_lista(&lista);
    return 0;
}
