# 🧬 Autômato Celular com Matriz Esparsa — ED1 TP2

Implementação do **Jogo da Vida de Conway** para a disciplina de Estrutura de Dados I utilizando **matriz esparsa com listas encadeadas** como estrutura de dados para representação do tabuleiro. Apenas as células vivas são armazenadas, economizando memória em cenários com baixa densidade de células.

---

## 📐 Visão Geral

Em vez de alocar uma matriz `N×N` completa, o autômato mantém para cada linha e cada coluna uma **lista encadeada** de células vivas. Cada nó da lista guarda sua posição `(linha, coluna)` e dois ponteiros — um para o próximo elemento da mesma linha e outro para o próximo da mesma coluna.

```
Linha 1 → [1,2] → [1,5] → NULL
Linha 2 → [2,2] → NULL

Coluna 2 → [1,2] → [2,2] → NULL
Coluna 5 → [1,5] → NULL
```

---

## 📂 Estrutura do Projeto

```
tp2---Estrutura-de-dados-1-main/
├── matriz.h       # Definição das structs (Celula, Lista, MatrizEsparsa, AutomatoCelular)
├── matriz.c       # Alocação e desalocação da matriz esparsa
├── automato.h     # Declaração das funções do autômato
├── automato.c     # Lógica do autômato celular (inserção, evolução, impressão)
└── tp.c           # Ponto de entrada (main)
```

---

## 🏗️ Estruturas de Dados

```c
// Nó da lista — representa uma célula viva
typedef struct Celula {
    int linha;
    int coluna;
    struct Celula *proxLinha;    // próxima célula viva na mesma linha
    struct Celula *proxColuna;   // próxima célula viva na mesma coluna
} Celula;

// Cabeça de lista encadeada
typedef struct Lista {
    Celula *cabeca;
} Lista;

// Matriz esparsa: um array de listas por linha + um array de listas por coluna
typedef struct MatrizEsparsa {
    int tamanho;
    Lista *linhas;    // linhas[i] → lista de células vivas na linha i
    Lista *colunas;   // colunas[j] → lista de células vivas na coluna j
} MatrizEsparsa;

typedef struct AutomatoCelular {
    MatrizEsparsa *matriz;
    int tamanho;
} AutomatoCelular;
```

---

## ⚙️ Operações Principais

### Inserção de célula viva — `adicionarCelula()`
Insere o novo nó **no início** das listas da linha e da coluna correspondentes (O(1)):

```
linhas[i].cabeca  ← novaCelula → antigo início da linha
colunas[j].cabeca ← novaCelula → antigo início da coluna
```

### Contagem de vizinhos — `contarVizinhosVivos()`
Para cada um dos 8 vizinhos de Moore, percorre a lista encadeada da linha do vizinho buscando a coluna. Complexidade: O(k), onde k é o número de células vivas na linha.

### Evolução — `evoluirReticulado()`
A cada geração, varre todas as posições `(i, j)` do reticulado, conta vizinhos e aplica as regras do Conway. O novo estado é construído em um autômato separado; o anterior é desalocado ao final de cada geração.

---

## 🧩 Regras do Autômato Celular (Conway's Game of Life)

| Estado atual | Vizinhos vivos | Próximo estado               |
|:---:|:---:|:---:|
| Viva | < 2 ou > 3 | Morre (isolamento / superpopulação) |
| Viva | 2 ou 3     | Sobrevive                          |
| Morta | = 3       | Nasce                              |

---

## ▶️ Compilação e Execução

### Compilar manualmente

```bash
gcc tp.c automato.c matriz.c -o exe -Wall
```

### Executar

```bash
./exe < entrada.in
```

### Executar com Valgrind

```bash
gcc -g tp.c automato.c matriz.c -o exeval -Wall
valgrind --leak-check=full ./exeval < entrada.in
```

---

## 📥 Formato de Entrada e Saída

**Entrada:**
```
<tamanho> <geracoes>
<grid tamanho × tamanho com 0s e 1s>
```

**Saída:**
```
<grid tamanho × tamanho com estado após geracoes>
```

**Exemplo:**

```
Entrada:    Saída:
3 1         0 0 0
0 0 0       0 1 1
0 1 1       0 1 1
0 1 0
```

---

## 🆚 Comparação com a Versão Hash (TP3)

| Aspecto | TP2 — Matriz Esparsa | TP3 — Tabela Hash |
|---|---|---|
| Estrutura | Listas encadeadas por linha/coluna | Array com endereçamento aberto |
| Busca de célula | O(k) — percorre a lista da linha | O(1) amortizado |
| Inserção | O(1) — insere no início da lista | O(1) amortizado |
| Colisões | Não se aplica | Hash duplo / quadrático |
| Memória extra por célula | 2 ponteiros (`proxLinha`, `proxColuna`) | Apenas a chave na tabela |

---

## 🧠 Conceitos Abordados

- Matriz esparsa com listas encadeadas duplamente indexadas
- Representação esparsa do tabuleiro (somente células vivas)
- Autômato celular bidimensional (Conway's Game of Life)
- Vizinhança de Moore
- Gerenciamento manual de memória em C (`malloc`, `free`)
- Compilação modular em C
