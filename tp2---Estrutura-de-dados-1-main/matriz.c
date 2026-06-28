#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

// Aloca um novo autômato celular com uma matriz esparsa
AutomatoCelular* alocarReticulado(int tamanho) {
    AutomatoCelular *automato = (AutomatoCelular*) malloc(sizeof(AutomatoCelular));
    automato->tamanho = tamanho;
    
    // Alocando a matriz esparsa
    automato->matriz = (MatrizEsparsa*) malloc(sizeof(MatrizEsparsa));
    automato->matriz->tamanho = tamanho;
    automato->matriz->linhas = (Lista*) malloc(tamanho * sizeof(Lista));
    automato->matriz->colunas = (Lista*) malloc(tamanho * sizeof(Lista));
    
    // Inicializando as listas encadeadas para as linhas e colunas
    for (int i = 0; i < tamanho; i++) {
        automato->matriz->linhas[i].cabeca = NULL;
        automato->matriz->colunas[i].cabeca = NULL;
    }
    
    return automato;
}

// Desaloca o autômato celular e a matriz esparsa
void desalocarReticulado(AutomatoCelular *automato) {
    int tamanho = automato->tamanho;
    
    // Desaloca as listas encadeadas
    for (int i = 0; i < tamanho; i++) {
        Celula *atual = automato->matriz->linhas[i].cabeca;
        while (atual != NULL) {
            Celula *prox = atual->proxLinha;
            free(atual);
            if (prox == automato->matriz->linhas[i].cabeca) break;
            atual = prox;
        }
    }
    
    // Desaloca as estruturas da matriz esparsa
    free(automato->matriz->linhas);
    free(automato->matriz->colunas);
    free(automato->matriz);
    free(automato);
}
