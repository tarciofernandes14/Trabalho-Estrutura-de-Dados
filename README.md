# Campeonato Computacional de Futebol — Parte I

**Disciplina:** Estrutura de Dados  
**Instituto:** IFES — Campus Serra  
**Professor:** Thiago M. Paixão  

**Alunos:**
- Gustavo da Paz Rauta Ramos
- Tarcio Fernandes Rodrigues

---

## Descrição

Sistema em linguagem C para gerenciamento de um campeonato computacional de futebol com 10 times. Os dados são persistidos em arquivos CSV e carregados em memória ao iniciar o programa. Nesta primeira parte, o sistema permite consultar times, consultar partidas e exibir a tabela de classificação.

---

## Estrutura do repositório

```
trabalhop1/
├── main.c                  # Programa principal e menu do sistema
├── TAD_Time.h / .c         # TAD que representa um único time
├── TAD_BDTimes.h / .c      # TAD que gerencia a coleção de times
├── TAD_Partida.h / .c      # TAD que representa uma única partida
├── TAD_BDPartidas.h / .c   # TAD que gerencia a coleção de partidas
├── Makefile                # Compilação do projeto
├── times.csv               # Banco de dados dos times
├── partidas_vazio.csv      # Cenário 1: campeonato sem partidas
├── partidas_parcial.csv    # Cenário 2: campeonato em andamento
└── partidas_completo.csv   # Cenário 3: campeonato finalizado
```

---

## Como compilar e executar

**Pré-requisitos:** GCC 11 e Make instalados em ambiente Linux Ubuntu 22.04.

**Compilar:**
```bash
make
```

**Executar:**
```bash
./sistema_futebol
```

**Limpar arquivos de compilação:**
```bash
make clean
```

**Trocar o cenário de partidas:**  
Por padrão o sistema carrega `partidas_parcial.csv`. Para testar outro cenário, altere a linha correspondente em `main.c`:
```c
carregar_partidas_csv(bd_partida, "partidas_completo.csv");
```

---

## Funcionalidades implementadas

**Opção 1 — Consultar time**  
O usuário digita um nome ou prefixo. O sistema exibe todos os times cujo nome começa com o texto informado, mostrando vitórias, empates, derrotas, gols marcados, gols sofridos, saldo de gols e pontos ganhos. Caso nenhum time seja encontrado, uma mensagem de erro é exibida.

**Opção 2 — Consultar partidas**  
O usuário escolhe se quer buscar por time mandante, visitante, ou qualquer um dos dois. A busca também é feita por prefixo. Os resultados exibem o placar no formato `Time1 N x N Time2`. Caso nenhuma partida seja encontrada, uma mensagem de erro é exibida.

**Opção 6 — Imprimir tabela de classificação**  
Exibe todos os 10 times em ordem de ID com suas estatísticas acumuladas (V, E, D, GM, GS, S, PG). Funciona corretamente nos três cenários de teste.

---

## Principais TADs

### TAD Time (`TAD_Time.h / .c`)
Representa um único time. Armazena `id`, `nome` e os contadores de desempenho (`v`, `e`, `d`, `gm`, `gs`). As funções `get_PG` e `get_SG` calculam os pontos ganhos e o saldo de gols sob demanda, garantindo que os valores derivados estejam sempre consistentes com os dados brutos.

### TAD BDTimes (`TAD_BDTimes.h / .c`)
Gerencia o conjunto de todos os times. Responsável por carregar o `times.csv` (`readteams`), buscar um time pelo ID (`buscar_time_por_id`), atualizar as estatísticas de um time após uma partida (`registrar_resultado_Time`) e processar todas as partidas de uma vez para calcular o campeonato completo (`processar_campeonato`).

### TAD Partida (`TAD_Partida.h / .c`)
Representa um único jogo, encapsulando `id`, `id_time1`, `id_time2`, `gols_time1` e `gols_time2`. Oferece funções de criação (`criar_partida`) e liberação de memória (`destruir_partida`).

### TAD BDPartidas (`TAD_BDPartidas.h / .c`)
Gerencia a coleção de partidas usando um vetor dinâmico de ponteiros para `Partida`. É responsável por alocar a estrutura (`criar_BDPartidas`), carregar o CSV de partidas (`carregar_partidas_csv`) e liberar toda a memória ao final (`destruir_BDPartidas`).

---

## Principais decisões de implementação

**Vetor estático para times, vetor dinâmico para partidas**  
Como o enunciado define exatamente 10 times, `BDTimes` usa um vetor estático de 11 posições. Já `BDPartidas` usa um vetor dinâmico de ponteiros, pois a quantidade de partidas varia conforme o cenário de teste.

**Cálculo de PG e SG sob demanda**  
Os campos `pg` e `sg` não são armazenados diretamente na struct `Time`. As funções `get_PG` e `get_SG` os calculam a partir de `v`, `e`, `gm` e `gs` no momento da consulta, evitando inconsistências caso os contadores base sejam atualizados.

**Busca por prefixo com `strncmp`**  
Tanto na consulta de times quanto na de partidas, a comparação é feita com `strncmp(nome, busca, strlen(busca))`, o que permite que o usuário informe apenas o início do nome e obtenha todos os resultados correspondentes.

**Separação entre carregamento e processamento**  
O carregamento do CSV de partidas (`carregar_partidas_csv`) é separado do cálculo das estatísticas (`processar_campeonato`). Isso deixa cada função com uma responsabilidade única e facilita a extensão para as próximas partes do trabalho, onde haverá inserção, atualização e remoção de partidas.

**Liberação completa de memória**  
Toda memória alocada dinamicamente é liberada ao encerrar o programa. Isso foi verificado com Valgrind (64 allocs, 64 frees, zero leaks).
