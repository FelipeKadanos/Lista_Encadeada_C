#include <stdio.h>
#include <string.h>

#include "lista_pedidos.h"

static void limpar_buffer(void) {
    int caractere;

    /* Descarta o restante da linha para evitar lixo no buffer de entrada. */
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

static int ler_inteiro(const char *mensagem) {
    int valor;

    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            limpar_buffer();
            return valor;
        }

        printf("Entrada invalida. Digite um numero inteiro.\n");
        limpar_buffer();
    }
}

static float ler_float(const char *mensagem) {
    float valor;

    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &valor) == 1) {
            limpar_buffer();
            return valor;
        }

        printf("Entrada invalida. Digite um valor numerico.\n");
        limpar_buffer();
    }
}

static void ler_texto(const char *mensagem, char *destino, int tamanho) {
    printf("%s", mensagem);

    if (fgets(destino, tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }

    destino[strcspn(destino, "\n")] = '\0';
}

static Pedido ler_dados_pedido(const ListaPedidos *lista) {
    Pedido pedido;

    while (1) {
        pedido.id = ler_inteiro("Informe o ID do pedido: ");
        if (pedido.id <= 0) {
            printf("O ID deve ser um numero positivo.\n");
            continue;
        }

        if (!id_ja_cadastrado(lista, pedido.id)) {
            break;
        }

        printf("Esse ID ja esta em uso. Informe outro valor.\n");
    }

    ler_texto("Nome do cliente: ", pedido.nome_cliente, TAM_NOME);

    while (1) {
        pedido.valor_total = ler_float("Valor total do pedido: ");
        if (pedido.valor_total >= 0.0f) {
            break;
        }

        printf("O valor do pedido nao pode ser negativo.\n");
    }

    ler_texto("Status do pedido: ", pedido.status, TAM_STATUS);

    return pedido;
}

static void inserir_pedido_prioritario(ListaPedidos *lista) {
    Pedido pedido = ler_dados_pedido(lista);

    if (inserir_no_inicio(lista, pedido)) {
        printf("Pedido prioritario inserido no inicio da lista com sucesso.\n");
    } else {
        printf("Falha ao inserir o pedido por falta de memoria.\n");
    }
}

static void inserir_pedido_comum(ListaPedidos *lista) {
    Pedido pedido = ler_dados_pedido(lista);

    if (inserir_no_fim(lista, pedido)) {
        printf("Pedido comum inserido no final da lista com sucesso.\n");
    } else {
        printf("Falha ao inserir o pedido por falta de memoria.\n");
    }
}

static void remover_pedido(ListaPedidos *lista) {
    int id = ler_inteiro("Informe o ID do pedido que deseja remover: ");

    if (remover_por_id(lista, id)) {
        printf("Pedido removido com sucesso.\n");
    } else {
        printf("Pedido nao encontrado.\n");
    }
}

static void exibir_menu(void) {
    printf("\n===== CONTROLE DE PEDIDOS DELIVERY =====\n");
    printf("1. Inserir novo pedido no inicio (prioritario)\n");
    printf("2. Inserir novo pedido no final (comum)\n");
    printf("3. Remover pedido pelo ID\n");
    printf("4. Exibir pedidos do inicio para o fim\n");
    printf("5. Exibir pedidos do fim para o inicio\n");
    printf("6. Encerrar o programa\n");
}

int main(void) {
    ListaPedidos lista;
    int opcao;

    /* A lista comeca vazia e vai sendo preenchida conforme o menu. */
    inicializar_lista(&lista);

    do {
        exibir_menu();
        opcao = ler_inteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                inserir_pedido_prioritario(&lista);
                break;
            case 2:
                inserir_pedido_comum(&lista);
                break;
            case 3:
                remover_pedido(&lista);
                break;
            case 4:
                exibir_do_inicio(&lista);
                break;
            case 5:
                exibir_do_fim(&lista);
                break;
            case 6:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 6);

    liberar_lista(&lista);
    return 0;
}
