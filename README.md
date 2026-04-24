# Atividade

Projeto desenvolvido em linguagem C para implementar um sistema de controle de pedidos de delivery utilizando lista duplamente encadeada e menu de interação.

### Autores: ***Felipe Kadanos*** GitHub: [FelipeKadanos](https://github.com/FelipeKadanos) e ***Marcos Ferrari*** GitHub: [marcosferraridev](https://github.com/marcosferraridev)

Atividade a ser realizada individualmente ou em dupla.

**Valor:** 1 ponto

## Critérios de avaliação

- todas as funções implementadas: 0,4
- código comentado: 0,2
- funcionalidades OK: 0,4

## Descrição

Desenvolva uma aplicação em linguagem C que implemente um sistema de controle de pedidos de delivery utilizando lista duplamente encadeada, permitindo interação por meio de um menu textual.

## Funcionalidades

A aplicação deverá disponibilizar as seguintes funcionalidades:

1. Inserir um novo pedido no início da lista
2. (pedido prioritário)
3. Inserir um novo pedido no final da lista
4. (pedido comum, conforme ordem de chegada)
5. Remover um pedido, informando o ID do pedido
6. (cancelamento de pedido)
7. Exibir todos os pedidos do início para o fim, mostrando todos os dados do pedido
8. Exibir todos os pedidos do fim para o início, mostrando todos os dados do pedido
9. Encerrar o programa

## Requisitos Técnicos

- Utilizar obrigatoriamente uma lista duplamente encadeada, com ponteiros para o nó anterior e o próximo.
- Cada pedido do sistema deverá conter obrigatoriamente as seguintes informações:
  - ID do pedido (inteiro)
  - Nome do cliente (string)
  - Valor total do pedido (float)
  - Status do pedido (string — por exemplo: “Recebido”, “Em preparo”, “Saiu para entrega”)
- Criar:
  - uma struct para representar os dados do pedido;
  - uma struct para representar o nó da lista.
- Utilizar alocação dinâmica de memória (malloc e free).
- Organizar o código em funções bem definidas (ex.: inserir pedido, remover pedido, exibir pedidos).
- Tratar corretamente os seguintes casos:
  - Lista vazia
  - Remoção do primeiro pedido
  - Remoção do último pedido
  - Pedido não encontrado
