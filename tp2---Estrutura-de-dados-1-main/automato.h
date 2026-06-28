#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "matriz.h"

// Funções de alocação e desalocação
AutomatoCelular* alocarReticulado(int tamanho);
void desalocarReticulado(AutomatoCelular *automato);

// Funções de manipulação do autômato
void adicionarCelula(AutomatoCelular *automato, int linha, int coluna);
int contarVizinhosVivos(AutomatoCelular *automato, int linha, int coluna);
AutomatoCelular* evoluirReticulado(AutomatoCelular *automato, int geracoes);
void imprimeReticulado(AutomatoCelular *automato);

// Função para leitura do reticulado
AutomatoCelular* leituraReticulado(int tamanho);

#endif // AUTOMATO_H
