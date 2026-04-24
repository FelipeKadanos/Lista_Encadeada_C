# Sistema de Controle de Pedidos de Delivery

Projeto desenvolvido em linguagem C para implementar um sistema de controle de pedidos de delivery utilizando lista duplamente encadeada e menu de interação.

## Autores

| Autor | GitHub |
| --- | --- |
| ***Felipe Kadanos*** | [FelipeKadanos](https://github.com/FelipeKadanos) |
| ***Marcos Ferrari*** | [marcosferraridev](https://github.com/marcosferraridev) |

## Atividade

Atividade a ser realizada individualmente ou em dupla.

**Valor:** 1 ponto

## Critérios de avaliação

| Critério | Pontuação |
| --- | ---: |
| Todas as funções implementadas | 0,4 |
| Código comentado | 0,2 |
| Funcionalidades OK | 0,4 |

## Descrição

Desenvolva uma aplicação em linguagem C que implemente um sistema de controle de pedidos de delivery utilizando lista duplamente encadeada, permitindo interação por meio de um menu textual.

## Funcionalidades

A aplicação deverá disponibilizar as seguintes funcionalidades:

| Item(s) do enunciado | Funcionalidade | Observação |
| ---: | --- | --- |
| 1 e 2 | Inserir um novo pedido no início da lista | Pedido prioritário |
| 3 e 4 | Inserir um novo pedido no final da lista | Pedido comum, conforme ordem de chegada |
| 5 e 6 | Remover um pedido, informando o ID do pedido | Cancelamento de pedido |
| 7 | Exibir todos os pedidos do início para o fim | Mostrando todos os dados do pedido |
| 8 | Exibir todos os pedidos do fim para o início | Mostrando todos os dados do pedido |
| 9 | Encerrar o programa | - |

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
