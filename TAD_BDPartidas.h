//TAD_BDPartidas.h

#ifndef TAD_BDPARTIDAS_H
#define TAD_BDPARTIDAS_H

#include "TAD_Partida.h"


typedef struct {
    Partida **partidas; 
    int qtd_partidas;   
    int capacidade;     
} BDPartidas;


BDPartidas* criar_BDPartidas(int capacidade_inicial);
void carregar_partidas_csv(BDPartidas *bd, const char *nome_arquivo);
void destruir_BDPartidas(BDPartidas *bd);

void consultar_partidas_por_time(BDPartidas *bd, const char *prefixo_time);

#endif