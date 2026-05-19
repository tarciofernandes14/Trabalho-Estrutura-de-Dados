//TAD_BDTimes.c-----------------
#include "TAD_BDTimes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readteams(BDTimes *bd){
    
    FILE *arquivo_time = fopen("times.csv","r");
    if (arquivo_time == NULL) {
        printf("Arquivo Inválido.");
        return 0;    
    }     

    char linha[256];
    int cont = 0;

    fgets(linha, sizeof(linha), arquivo_time); //lê o arquivo uma vez para ignorar primeira linha que contém (ID,Time)

    while (cont < 10 && fgets(linha, sizeof(linha), arquivo_time) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; //Troca \n por \0 para encerrar a linha sem o pulo de linha em cada time.

        char *id_texto = strtok(linha, ",");
        char *nome_texto = strtok(NULL, ",");
        
        if (id_texto != NULL && nome_texto != NULL) {
            
            int id_int = atoi(id_texto);
            bd->lista_times[cont] = create_Time((id_int), nome_texto);
            cont++;
        }
    }
    bd->qtd_times = cont; //atualizs quantos times foram lidos
    fclose(arquivo_time);
    
   return 1;
}
Time* buscar_time_por_id(BDTimes *bd, int id_procurado) {
    for (int i = 0; i < bd->qtd_times; i++) {
        if ((bd->lista_times[i]->id) == id_procurado) {
            return bd->lista_times[i]; 
        }
    }
    return NULL; 
}
void registrar_resultado_Time(Time *t, int gols_pro, int gols_contra) {
    if (t == NULL) return;
    t->gm += gols_pro;    
    t->gs += gols_contra; 
    if (gols_pro > gols_contra) {
        t->v++; 
    } else if (gols_pro < gols_contra) {
        t->d++; 
    } else {
        t->e++; 
    }
}
void processar_campeonato(BDTimes *bdt, BDPartidas *bdp) {
    for (int i = 0; i < bdp->qtd_partidas; i++) {
        Partida *p = bdp->partidas[i]; 
        Time *t1 = buscar_time_por_id(bdt, p->id_time1);
        Time *t2 = buscar_time_por_id(bdt, p->id_time2);
        if (t1 != NULL && t2 != NULL) {
            registrar_resultado_Time(t1, p->gols_time1, p->gols_time2);
            registrar_resultado_Time(t2, p->gols_time2, p->gols_time1);
        }
    }
}

void destruir_times(BDTimes *bdt) {
    if (bdt == NULL) return; 

    for (int i = 0; i < bdt->qtd_times; i++) {
        free(bdt->lista_times[i]); 
    }
    free(bdt); 
}
