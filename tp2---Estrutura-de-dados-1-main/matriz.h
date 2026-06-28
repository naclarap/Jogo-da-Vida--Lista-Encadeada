#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Celula {
    int linha;
    int coluna;
    struct Celula *proxLinha;
    struct Celula *proxColuna;
} Celula;

typedef struct Lista {
    Celula *cabeca;
} Lista;

typedef struct MatrizEsparsa {
    int tamanho;
    Lista *linhas;
    Lista *colunas;
} MatrizEsparsa;

typedef struct AutomatoCelular {
    MatrizEsparsa *matriz;
    int tamanho;
} AutomatoCelular;

#endif // MATRIZ_H
