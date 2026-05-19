//TAD_BDTimes.h
#ifndef TAD_BDTIMES_H
#define TAD_BDTIMES_H
#include "TAD_Time.h"
#include "TAD_BDPartidas.h"

typedef struct {
    Time *lista_times[11];
    int qtd_times;
} BDTimes;

int readteams(BDTimes *bd);

Time* buscar_time_por_id(BDTimes *bd, int id_procurado);

void registrar_resultado_Time(Time *t, int gols_pro, int gols_contra);

void processar_campeonato(BDTimes *bdt, BDPartidas *bdp);

void destruir_times(BDTimes *bdt);

#endif