//TAD_Time.c
#include "TAD_Time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Time* create_Time(const int id, const char *nome){
    //alocação dinâmica 
    Time *new_Time =(Time*)malloc(sizeof(Time));
    if (new_Time == NULL){
        printf ("Erro na alocação de memória do Time.\n");
        exit(1);
    }

    

    strcpy(new_Time->nome, nome);
    new_Time->id = id;
    new_Time->v = 0;
    new_Time->e = 0;
    new_Time->d = 0;
    new_Time->gm = 0;
    new_Time->gs = 0;
    new_Time->sg = 0;
    new_Time->pg = 0;
    
    return new_Time;
}
// Retorna os pts ganhos (3V + E)
int get_PG(Time *t) {
    if (t == NULL) return 0;
    return (t->v * 3) + (t->e);
}

// Retorna o saldo de gols (GM - GS)
int get_SG(Time *t) {
    if (t == NULL) return 0;
    return (t->gm) - (t->gs);
}