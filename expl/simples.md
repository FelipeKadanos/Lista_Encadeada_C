# Explicação Simplificada do Projeto

Este projeto implementa um sistema de controle de pedidos de delivery em C usando uma lista duplamente encadeada. A ideia é guardar vários pedidos em uma estrutura dinâmica, onde cada elemento conhece o pedido anterior e o próximo pedido da lista.

## O que o programa faz

O sistema permite:

- inserir um pedido prioritário no início da lista;
- inserir um pedido comum no final da lista;
- remover um pedido pelo ID;
- exibir os pedidos do início para o fim;
- exibir os pedidos do fim para o início;
- encerrar o programa.

## Como a lista funciona

Cada pedido fica dentro de um nó. Esse nó possui:

- os dados do pedido;
- um ponteiro para o nó anterior;
- um ponteiro para o próximo nó.

Isso permite andar na lista em duas direções, que é justamente a principal característica da lista duplamente encadeada.

## Estrutura dos arquivos

- [main.c](./main.c): contém o menu textual, a leitura dos dados e a interação com o usuário.
- [lista_pedidos.h](./lista_pedidos.h): contém as structs e os protótipos das funções.
- [lista_pedidos.c](./lista_pedidos.c): contém a implementação da lista duplamente encadeada.

## Estruturas principais

No arquivo [lista_pedidos.h](./lista_pedidos.h), o projeto usa três estruturas principais:

- `Pedido`: guarda `id`, `nome_cliente`, `valor_total` e `status`.
- `NoPedido`: representa um nó da lista, com o pedido e os ponteiros `anterior` e `proximo`.
- `ListaPedidos`: guarda o começo da lista, o final e a quantidade de elementos.

## Fluxo geral do programa

O programa começa em [main.c](./main.c), inicializa a lista vazia e mostra um menu em loop. Enquanto o usuário não escolher sair, o programa lê a opção digitada e chama a função correspondente.

## Ideia principal das operações

- Inserir no início: usado para pedidos prioritários.
- Inserir no fim: usado para pedidos comuns.
- Remover por ID: procura o pedido e ajusta os ponteiros para retirar o nó da lista.
- Exibir do início para o fim: percorre a lista usando `proximo`.
- Exibir do fim para o início: percorre a lista usando `anterior`.

## Por que essa estrutura foi boa para o projeto

A lista duplamente encadeada encaixa bem nesse problema porque:

- permite inserir rapidamente no início e no fim;
- permite percorrer os pedidos nos dois sentidos;
- não exige um tamanho fixo de memória, já que os nós são criados com `malloc`.

## O que vale estudar primeiro

Se vocês quiserem entender o projeto de forma rápida, vale ler nesta ordem:

1. [lista_pedidos.h](./lista_pedidos.h)
2. [lista_pedidos.c](./lista_pedidos.c)
3. [main.c](./main.c)

Essa ordem ajuda porque primeiro vocês entendem os tipos de dados, depois as operações da lista e por fim a parte do menu.
