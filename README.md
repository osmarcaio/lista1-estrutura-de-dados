# Trabalho 1 - Room Reservation System

## Descrição do projeto

Este projeto implementa um sistema simples de reserva de salas em C++, conforme proposto no Trabalho 1 da disciplina.

O sistema gerencia a alocação de disciplinas em salas de aula ao longo de uma semana. Para cada solicitação de reserva, o programa verifica automaticamente se existe alguma sala disponível no dia e horário informados e, caso exista, atribui a primeira sala que também possua capacidade suficiente para comportar a turma.

O sistema permite:

- realizar novas reservas;
- cancelar reservas existentes;
- exibir a grade atual de ocupação das salas.

Cada reserva contém as seguintes informações:

- nome da disciplina;
- dia da semana;
- horário de início;
- horário de término;
- quantidade de alunos.

## Organização dos arquivos

O projeto está organizado nos seguintes arquivos:

- `main.cpp`
- `ReservationSystem.hpp`
- `ReservationSystem.cpp`
- `ReservationRequest.hpp`
- `ReservationRequest.cpp`
- `Custom.hpp`

### Função de cada arquivo

- **main.cpp**: contém os testes que demonstram o funcionamento do sistema;
- **ReservationRequest.hpp / ReservationRequest.cpp**: definem e implementam a classe `ReservationRequest`, responsável por representar uma solicitação de reserva;
- **ReservationSystem.hpp / ReservationSystem.cpp**: definem e implementam a classe `ReservationSystem`, responsável por armazenar, gerenciar, reservar, cancelar e imprimir as reservas do sistema.
- **custom.hpp**: contém a definição das structures auxiliares Sala e Reserva.

## Instruções de compilação

Para compilar o projeto, utilize o comando:

```bash
g++ main.cpp ReservationSystem.cpp ReservationRequest.cpp -o reservation_system
```

## Instruções de execução

Após a compilação, execute o programa com:

```bash
./reservation_system
```

No Windows, a execução também pode ser feita com:

```bash
reservation_system.exe
```

## Organização interna dos dados

Internamente, o sistema foi implementado com estruturas manuais, sem uso de estruturas da STL como `vector`, `list` ou `map`.

### 1. Armazenamento das salas

A classe `ReservationSystem` mantém:

- a quantidade total de salas (`room_count`);
- um array com as capacidades das salas (`room_capacities`);
- uma estrutura interna contendo todas as salas cadastradas no sistema.

As salas são alocadas dinamicamente no construtor de `ReservationSystem`.

### 2. Estrutura de cada sala

Cada sala possui:

- sua capacidade máxima;
- uma grade semanal de reservas.

Essa grade semanal foi modelada como uma estrutura bidimensional com:

- **5 dias da semana**:
  - `segunda`
  - `terca`
  - `quarta`
  - `quinta`
  - `sexta`

- **14 posições de horário**, correspondentes ao intervalo de **7h até 21h**.

Cada posição da grade armazena um ponteiro para uma reserva (`Reserva*`). Quando não há reserva naquele horário, a posição contém `nullptr`.

De forma conceitual, a estrutura pode ser entendida como:

```cpp
Reserva* reservas_da_semana[5][14];
```

Nessa matriz:

- o primeiro índice representa o dia da semana;
- o segundo índice representa o horário;
- o conteúdo da posição indica se existe ou não uma reserva naquele slot.

### 3. Representação das reservas

As reservas são armazenadas por meio de uma estrutura interna que guarda:

- nome da disciplina;
- dia da semana;
- horário de início;
- horário de término;
- número de alunos.

Quando uma disciplina é reservada, o sistema cria uma reserva e marca todos os horários ocupados por ela na grade da sala escolhida.

Por exemplo, uma reserva de `9` até `11` ocupa os slots correspondentes a:

- 9h–10h
- 10h–11h

Como o horário final não está incluído no intervalo, reservas como `7-9` e `9-11` não entram em conflito.

### 4. Funcionamento da reserva

No método `reserve`, o sistema:

1. converte o dia da semana para um índice numérico;
2. percorre as salas em ordem;
3. verifica se a sala possui capacidade suficiente;
4. verifica se todos os horários necessários estão livres;
5. aloca a reserva na primeira sala válida encontrada.

Se nenhuma sala estiver disponível, o método retorna `false`.

### 5. Funcionamento do cancelamento

No método `cancel`, o sistema percorre todas as salas, todos os dias e todos os horários até encontrar a disciplina informada. Quando a reserva é localizada, todos os slots ocupados por ela são liberados, e o método retorna `true`.

Caso a disciplina não seja encontrada, o método retorna `false`.

### 6. Funcionamento da exibição da grade

No método `printSchedule`, o sistema percorre todas as salas e imprime as reservas encontradas, organizadas por sala, dia e horário. Como uma mesma reserva ocupa vários slots consecutivos, o método evita imprimir repetidamente a mesma disciplina.
