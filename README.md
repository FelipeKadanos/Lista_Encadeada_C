# Sistema de Restaurante com Lista Duplamente Encadeada

Este projeto e uma pequena aplicacao em C para controlar reservas e lista de espera de mesas de um restaurante.

## Estrutura utilizada

Cada cliente e armazenado em um no de uma lista duplamente encadeada, contendo:

- codigo do registro
- nome do cliente
- quantidade de pessoas
- numero da mesa desejada
- status do atendimento
- ponteiro para o no anterior
- ponteiro para o proximo no

## Funcionalidades

- cadastrar reserva ou entrada na lista de espera
- cancelar registro
- confirmar chegada do cliente
- liberar mesa para o proximo cliente
- listar todos os registros
- buscar cliente por codigo
- exibir resumo do sistema

## Compilacao

```bash
gcc main.c restaurante.c -o restaurante
```

## Execucao

```bash
./restaurante
```
