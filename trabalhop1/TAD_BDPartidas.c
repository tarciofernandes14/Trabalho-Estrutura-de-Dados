//TAD_BDPartidas.c

#include "TAD_BDPartidas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BDPartidas* criar_BDPartidas(int capacidade_inicial) {
    BDPartidas *bd = (BDPartidas*) malloc(sizeof(BDPartidas));
    if (!bd) exit(1);

    bd->partidas = (Partida**) malloc(capacidade_inicial * sizeof(Partida*));
    bd->qtd_partidas = 0;
    bd->capacidade = capacidade_inicial;
    return bd;
}

void carregar_partidas_csv(BDPartidas *bd, const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("Erro ao abrir arquivo de partidas.\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), f); // Pula o cabeçalho (ID, Time1, Time2...) 

    while (fgets(linha, sizeof(linha), f) && bd->qtd_partidas < bd->capacidade) {
        int id, t1, t2, g1, g2;
        // Formato esperado: ID, Time1, Time2, Gols1, Gols2
        if (sscanf(linha, "%d,%d,%d,%d,%d", &id, &t1, &t2, &g1, &g2) == 5) {
            bd->partidas[bd->qtd_partidas] = criar_partida(id, t1, t2, g1, g2);
            bd->qtd_partidas++;
        }
    }
    fclose(f);
}

void destruir_BDPartidas(BDPartidas *bd) {
    if (bd) {
        for (int i = 0; i < bd->qtd_partidas; i++) {
            destruir_partida(bd->partidas[i]);
        }
        free(bd->partidas);
        free(bd);
    }
}