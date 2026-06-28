#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main() {
    int tamanho, geracoes;
    scanf("%d %d", &tamanho, &geracoes);

    AutomatoCelular *automato = leituraReticulado(tamanho);
    
    automato = evoluirReticulado(automato, geracoes);
    
    imprimeReticulado(automato);
    
    desalocarReticulado(automato);
    
    return 0;
}
