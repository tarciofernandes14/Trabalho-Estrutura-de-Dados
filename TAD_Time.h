//TAD_Time.h
#ifndef TAD_TIME_H
#define TAD_TIME_H

 typedef struct {

    int id;
    char nome[50];
    int v, e, d, gm, gs, sg, pg;

    } Time;

Time* create_Time(const int id, const char *nome);

int get_PG(Time *t);
int get_SG(Time *t);

#endif