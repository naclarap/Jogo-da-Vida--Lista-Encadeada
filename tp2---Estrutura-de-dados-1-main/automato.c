#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

// Adiciona uma célula viva na matriz esparsa
void adicionarCelula(AutomatoCelular *automato, int linha, int coluna) {
    Celula *novaCelula = (Celula*) malloc(sizeof(Celula));
    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    
    // Atualiza a lista encadeada da linha
    novaCelula->proxLinha = automato->matriz->linhas[linha].cabeca;
    automato->matriz->linhas[linha].cabeca = novaCelula;
    
    // Atualiza a lista encadeada da coluna
    novaCelula->proxColuna = automato->matriz->colunas[coluna].cabeca;
    automato->matriz->colunas[coluna].cabeca = novaCelula;
}

int contarVizinhosVivos(AutomatoCelular *automato, int linha, int coluna) {
    int vizinhos = 0;
    int direcao[3] = {-1, 0, 1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (direcao[i] == 0 && direcao[j] == 0) continue; // Ignorar a célula atual

            int novaLinha = linha + direcao[i];
            int novaColuna = coluna + direcao[j];

            if (novaLinha >= 0 && novaLinha < automato->tamanho && novaColuna >= 0 && novaColuna < automato->tamanho) {
                Celula *atual = automato->matriz->linhas[novaLinha].cabeca;
                while (atual != NULL) {
                    if (atual->coluna == novaColuna) {
                        vizinhos++;
                        break;
                    }
                    atual = atual->proxLinha;
                }
            }
        }
    }

    return vizinhos;
}

AutomatoCelular* evoluirReticulado(AutomatoCelular *automato, int geracoes) {
    for (int g = 0; g < geracoes; g++) {
        AutomatoCelular *novoAutomato = alocarReticulado(automato->tamanho);

        for (int i = 0; i < automato->tamanho; i++) {
            for (int j = 0; j < automato->tamanho; j++) {
                int vizinhos = contarVizinhosVivos(automato, i, j);
                Celula *atual = automato->matriz->linhas[i].cabeca;
                int vivo = 0;

                // Verifica se a célula atual está viva
                while (atual != NULL) {
                    if (atual->coluna == j) {
                        vivo = 1;
                        break;
                    }
                    atual = atual->proxLinha;
                }
                
                // Aplicar regras do jogo da vida
                if (vivo) {
                    if (vizinhos == 2 || vizinhos == 3) {
                        adicionarCelula(novoAutomato, i, j);
                    }
                } else {
                    if (vizinhos == 3) {
                        adicionarCelula(novoAutomato, i, j);
                    }
                }
            }
        }

        desalocarReticulado(automato);
        automato = novoAutomato;
    }

    return automato;
}



// Imprime o reticulado
void imprimeReticulado(AutomatoCelular *automato) {
    for (int i = 0; i < automato->tamanho; i++) {
        for (int j = 0; j < automato->tamanho; j++) {
            int vivo = 0;
            Celula *atual = automato->matriz->linhas[i].cabeca;
            while (atual != NULL) {
                if (atual->coluna == j) {
                    vivo = 1;
                    break;
                }
                atual = atual->proxLinha;
            }
            printf("%d ", vivo);
        }
        printf("\n");
    }
}

// Inicializa o autômato celular a partir da entrada do terminal
AutomatoCelular* leituraReticulado(int tamanho) {
    AutomatoCelular *automato = alocarReticulado(tamanho);
    
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            int valor;
            scanf("%d", &valor);
            if (valor == 1) {
                adicionarCelula(automato, i, j);
            }
        }
    }
    
    return automato;
}