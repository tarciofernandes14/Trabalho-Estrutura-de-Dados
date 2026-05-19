//TAD_Partida.h
#ifndef TAD_PARTIDA_H
#define TAD_PARTIDA_H

// Estrutura que representa uma única partida [cite: 115]
typedef struct {
    int id;          
    int id_time1;    
    int id_time2;    
    int gols_time1;  
    int gols_time2;  
} Partida;


Partida* criar_partida(int id, int t1, int t2, int g1, int g2);

void destruir_partida(Partida *p);

#endif