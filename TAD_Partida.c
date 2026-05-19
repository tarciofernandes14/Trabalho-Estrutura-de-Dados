//TAD_Partida.c
#include "TAD_Partida.h"
#include <stdlib.h>
#include <stdio.h>

Partida* criar_partida(int id, int t1, int t2, int g1, int g2) {

    Partida *nova_partida = (Partida*) malloc(sizeof(Partida));
    
    if (nova_partida == NULL) {
        printf("Erro ao alocar memoria para Partida.\n");
        exit(1);
    }


    nova_partida->id = id;
    nova_partida->id_time1 = t1;
    nova_partida->id_time2 = t2;
    nova_partida->gols_time1 = g1;
    nova_partida->gols_time2 = g2;

    return nova_partida;
}

void destruir_partida(Partida *p) {
    if (p != NULL) {
        free(p); 
    }
}