# Explicação Detalhada do Projeto

Este documento foi feito para servir como guia completo do projeto. A ideia é que vocês consigam entender não só o que o programa faz, mas também por que cada parte foi escrita desse jeito.

## Visão geral

O projeto é um sistema de controle de pedidos de delivery desenvolvido em C. Ele usa uma lista duplamente encadeada para armazenar os pedidos e um menu textual para permitir a interação do usuário.

Arquivos principais do projeto:

- [main.c](./main.c)
- [lista_pedidos.h](./lista_pedidos.h)
- [lista_pedidos.c](./lista_pedidos.c)

## Objetivo da estrutura de dados

A escolha da lista duplamente encadeada foi importante porque o enunciado exige:

- inserção no início da lista;
- inserção no final da lista;
- remoção por ID;
- exibição do início para o fim;
- exibição do fim para o início.

Uma lista simplesmente encadeada já permitiria várias dessas operações, mas a lista duplamente encadeada resolve melhor a exibição reversa porque cada nó já possui um ponteiro para o elemento anterior.

## Modelagem dos dados

Toda a modelagem do projeto está em [lista_pedidos.h](./lista_pedidos.h).

### Struct `Pedido`

A struct `Pedido` representa apenas os dados do pedido:

```c
typedef struct {
    int id;
    char nome_cliente[TAM_NOME];
    float valor_total;
    char status[TAM_STATUS];
} Pedido;
```

Esses campos atendem exatamente ao que o trabalho pede:

- `id`: identificador do pedido.
- `nome_cliente`: nome do cliente.
- `valor_total`: valor total do pedido.
- `status`: texto com o estado atual do pedido.

### Struct `NoPedido`

A struct `NoPedido` representa um nó da lista:

```c
typedef struct NoPedido {
    Pedido pedido;
    struct NoPedido *anterior;
    struct NoPedido *proximo;
} NoPedido;
```

Esse é o ponto mais importante da lista duplamente encadeada. Cada nó guarda:

- um `Pedido`;
- um ponteiro para o nó anterior;
- um ponteiro para o próximo nó.

Com isso, a navegação pode acontecer em duas direções.

### Struct `ListaPedidos`

A struct `ListaPedidos` representa a lista como um todo:

```c
typedef struct {
    NoPedido *inicio;
    NoPedido *fim;
    int quantidade;
} ListaPedidos;
```

Ela guarda:

- `inicio`: primeiro nó da lista;
- `fim`: último nó da lista;
- `quantidade`: total de pedidos armazenados.

Guardar `inicio` e `fim` facilita inserções e percursos nas duas extremidades.

## Organização do código

O projeto foi separado em arquivos com responsabilidades diferentes.

### [lista_pedidos.h](./lista_pedidos.h)

Esse arquivo contém:

- constantes de tamanho;
- definição das structs;
- protótipos das funções.

Ele funciona como um contrato entre o `main.c` e `lista_pedidos.c`.

### [lista_pedidos.c](./lista_pedidos.c)

Esse arquivo contém a implementação da estrutura de dados. É nele que estão as funções que realmente manipulam a lista.

### [main.c](./main.c)

Esse arquivo cuida da interação com o usuário:

- mostra o menu;
- lê os dados digitados;
- chama as funções da lista;
- exibe mensagens de sucesso ou erro.

## Inicialização da lista

Em [lista_pedidos.c](./lista_pedidos.c), a função `inicializar_lista` prepara a lista para uso:

```c
void inicializar_lista(ListaPedidos *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantidade = 0;
}
```

Isso significa que, no início:

- não existe primeiro nó;
- não existe último nó;
- não existe nenhum pedido cadastrado.

## Criação dinâmica dos nós

Cada pedido novo precisa de memória própria. Para isso, o projeto usa `malloc` na função `criar_no`, em [lista_pedidos.c](./lista_pedidos.c):

```c
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
```

Essa função:

- reserva memória para um novo nó;
- copia os dados do pedido para dentro dele;
- inicializa os ponteiros com `NULL`.

Se o `malloc` falhar, a função retorna `NULL` e a inserção é cancelada.

## Verificação de lista vazia

A função `lista_vazia`, em [lista_pedidos.c](./lista_pedidos.c), simplifica várias decisões do programa:

```c
int lista_vazia(const ListaPedidos *lista) {
    return lista->inicio == NULL;
}
```

Se `inicio` for `NULL`, significa que a lista não possui nenhum nó.

## Controle de IDs repetidos

No arquivo [main.c](./main.c), a leitura dos dados do pedido chama a função `id_ja_cadastrado`, implementada em [lista_pedidos.c](./lista_pedidos.c). Ela percorre a lista para impedir que dois pedidos tenham o mesmo ID.

Trecho principal:

```c
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
```

Isso melhora a consistência do sistema, já que a remoção é feita informando o ID.

## Inserção de pedido prioritário no início

Pedidos prioritários entram no começo da lista. Essa lógica está na função `inserir_no_inicio`, em [lista_pedidos.c](./lista_pedidos.c):

```c
int inserir_no_inicio(ListaPedidos *lista, Pedido pedido) {
    NoPedido *novo_no = criar_no(pedido);

    if (novo_no == NULL) {
        return 0;
    }

    if (lista_vazia(lista)) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        novo_no->proximo = lista->inicio;
        lista->inicio->anterior = novo_no;
        lista->inicio = novo_no;
    }

    lista->quantidade++;
    return 1;
}
```

### O que acontece nessa função

Se a lista estiver vazia:

- o novo nó vira o primeiro;
- o novo nó também vira o último.

Se a lista já tiver elementos:

- o novo nó aponta para o antigo início;
- o antigo início passa a apontar de volta para o novo nó;
- o início da lista é atualizado.

Esse ajuste dos ponteiros garante que a ligação continue correta nos dois sentidos.

## Inserção de pedido comum no final

Pedidos comuns entram no final da lista. Essa lógica está na função `inserir_no_fim`, em [lista_pedidos.c](./lista_pedidos.c):

```c
int inserir_no_fim(ListaPedidos *lista, Pedido pedido) {
    NoPedido *novo_no = criar_no(pedido);

    if (novo_no == NULL) {
        return 0;
    }

    if (lista_vazia(lista)) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        novo_no->anterior = lista->fim;
        lista->fim->proximo = novo_no;
        lista->fim = novo_no;
    }

    lista->quantidade++;
    return 1;
}
```

### O que acontece nessa função

Se a lista estiver vazia:

- o nó inserido será ao mesmo tempo início e fim.

Se a lista já tiver elementos:

- o novo nó aponta para o antigo fim;
- o antigo fim aponta para o novo nó;
- o ponteiro `fim` é atualizado.

## Remoção de pedido por ID

A remoção é uma das partes mais importantes do trabalho, porque precisa tratar casos especiais. A lógica está em `remover_por_id`, em [lista_pedidos.c](./lista_pedidos.c).

Trecho principal:

```c
int remover_por_id(ListaPedidos *lista, int id) {
    NoPedido *atual = lista->inicio;

    while (atual != NULL && atual->pedido.id != id) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 0;
    }

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
```

### Casos tratados

Essa função cobre exatamente os cenários pedidos no enunciado:

- pedido não encontrado: quando `atual` chega em `NULL`;
- remoção do primeiro pedido: quando `atual->anterior == NULL`;
- remoção do último pedido: quando `atual->proximo == NULL`;
- remoção de um pedido do meio: quando ele possui anterior e próximo.

### Por que a remoção funciona

O segredo está em religar os nós vizinhos:

- o nó anterior passa a apontar para o próximo;
- o nó seguinte passa a apontar para o anterior.

Quando o nó removido está na ponta da lista, em vez de religar vizinhos, o sistema atualiza `inicio` ou `fim`.

Depois disso, o nó removido é liberado com `free`.

## Exibição do início para o fim

Essa operação usa o ponteiro `proximo`. A implementação está em `exibir_do_inicio`, em [lista_pedidos.c](./lista_pedidos.c):

```c
void exibir_do_inicio(const ListaPedidos *lista) {
    NoPedido *atual = lista->inicio;

    if (lista_vazia(lista)) {
        printf("A lista de pedidos esta vazia.\n");
        return;
    }

    while (atual != NULL) {
        exibir_pedido(&atual->pedido);
        atual = atual->proximo;
    }
}
```

Essa função começa no primeiro nó e avança até o final.

## Exibição do fim para o início

Essa operação usa o ponteiro `anterior`. A implementação está em `exibir_do_fim`, em [lista_pedidos.c](./lista_pedidos.c):

```c
void exibir_do_fim(const ListaPedidos *lista) {
    NoPedido *atual = lista->fim;

    if (lista_vazia(lista)) {
        printf("A lista de pedidos esta vazia.\n");
        return;
    }

    while (atual != NULL) {
        exibir_pedido(&atual->pedido);
        atual = atual->anterior;
    }
}
```

Essa função só é possível de forma simples porque a lista é duplamente encadeada.

## Impressão dos dados do pedido

A função `exibir_pedido`, em [lista_pedidos.c](./lista_pedidos.c), centraliza a exibição dos dados:

```c
static void exibir_pedido(const Pedido *pedido) {
    printf("ID: %d\n", pedido->id);
    printf("Cliente: %s\n", pedido->nome_cliente);
    printf("Valor total: R$ %.2f\n", pedido->valor_total);
    printf("Status: %s\n", pedido->status);
    printf("-----------------------------\n");
}
```

Isso evita repetição de código nas funções de exibição.

## Parte do menu em `main.c`

O arquivo [main.c](./main.c) é responsável por conversar com o usuário.

### Leitura segura dos dados

Algumas funções auxiliares foram criadas para melhorar a entrada de dados:

- `limpar_buffer`: limpa caracteres restantes do teclado;
- `ler_inteiro`: lê inteiros com validação;
- `ler_float`: lê valores `float` com validação;
- `ler_texto`: lê strings com `fgets`.

Essas funções ajudam a evitar erros comuns de entrada no terminal.

### Montagem do pedido

A função `ler_dados_pedido`, em [main.c](./main.c), reúne todos os dados do pedido:

```c
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
```

Essa função já aplica duas validações importantes:

- o ID deve ser positivo;
- o valor do pedido não pode ser negativo.

Além disso, ela impede ID duplicado.

### Loop principal do menu

O funcionamento do programa acontece dentro do `do...while` de `main`, em [main.c](./main.c):

```c
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
```

Essa parte conecta o menu textual às funções da lista.

## Liberação da memória

No final do programa, a função `liberar_lista`, em [lista_pedidos.c](./lista_pedidos.c), percorre todos os nós e chama `free`:

```c
void liberar_lista(ListaPedidos *lista) {
    NoPedido *atual = lista->inicio;

    while (atual != NULL) {
        NoPedido *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    inicializar_lista(lista);
}
```

Isso é importante para evitar vazamento de memória.

## Casos especiais atendidos

O enunciado pede tratamento correto de alguns cenários, e o projeto cobre todos eles:

- lista vazia: tratado nas funções de exibição;
- remoção do primeiro pedido: tratado em `remover_por_id`;
- remoção do último pedido: tratado em `remover_por_id`;
- pedido não encontrado: tratado em `remover_por_id`;
- falha de alocação: tratada nas funções de inserção;
- ID duplicado: tratado em `ler_dados_pedido`;
- valor negativo: tratado em `ler_dados_pedido`.

## Exemplo de execução mental

Imagine esta sequência:

1. Inserir pedido comum com ID 10.
2. Inserir pedido comum com ID 20.
3. Inserir pedido prioritário com ID 5.

A lista ficará assim:

```text
[5] <-> [10] <-> [20]
```

Se o programa exibir do início para o fim, a saída será:

```text
5, 10, 20
```

Se o programa exibir do fim para o início, a saída será:

```text
20, 10, 5
```

Se remover o pedido 10, a lista ficará:

```text
[5] <-> [20]
```

Isso mostra claramente por que os ponteiros `anterior` e `proximo` precisam ser ajustados corretamente.

## Resumo técnico

Em termos de aprendizado de estrutura de dados, este projeto demonstra:

- criação de structs em C;
- uso de ponteiros;
- alocação dinâmica com `malloc`;
- liberação com `free`;
- encadeamento duplo entre nós;
- inserção nas extremidades;
- remoção com tratamento de casos especiais;
- percurso em duas direções;
- integração da estrutura de dados com menu textual.

## Ordem recomendada para estudar o código

Se vocês quiserem dominar o projeto com mais segurança, uma boa ordem é:

1. Ler [lista_pedidos.h](./lista_pedidos.h) para entender as structs.
2. Ler [lista_pedidos.c](./lista_pedidos.c) para entender como a lista funciona.
3. Ler [main.c](./main.c) para entender como o usuário interage com o sistema.
4. Voltar em `remover_por_id` e revisar com calma, porque essa é a função mais importante da lógica de ponteiros.

## Conclusão

O projeto foi estruturado para ficar simples de usar e claro de estudar. A parte principal da atividade está no uso correto da lista duplamente encadeada, e o código foi dividido em arquivos justamente para facilitar o entendimento, a manutenção e a apresentação do trabalho.
