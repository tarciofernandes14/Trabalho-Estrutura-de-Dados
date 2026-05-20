#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_BDTimes.h"
#include "TAD_BDPartidas.h"
#include "TAD_Time.h"
#include "TAD_Partida.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Erro: Arquivo de partidas nao informado.\n");
        printf("Uso correto: %s <nome_do_arquivo.csv>\n", argv[0]);
        return 1; 
    }


    BDTimes *bd_time = (BDTimes*) malloc(sizeof(BDTimes));
    if (bd_time == NULL) return 1;
    bd_time->qtd_times = 0;

    if (readteams(bd_time) == 0) {
        printf("Erro ao carregar o arquivo times.csv\n");
        destruir_times(bd_time);
        return 1;
    }

    BDPartidas *bd_partida = criar_BDPartidas(100);
    if (bd_partida == NULL) {
        printf("Erro: Faltou memoria para criar o banco de partidas.\n");
        destruir_times(bd_time);
        return 1;
    }

    carregar_partidas_csv(bd_partida, argv[1]);
    processar_campeonato(bd_time, bd_partida);

    char option = ' ';
    while (option != 'q' && option != 'Q') {
        printf("\n--- Sistema de Gerenciamento de Partidas ---\n");
        printf("1 - Consultar time\n");
        printf("2 - Consultar partidas\n");
        printf("6 - Imprimir tabela de classificacao\n");
        printf("Q - Sair\n");
        printf("Opcao: ");
        scanf(" %c", &option);

if (option == '1') {
            char busca[50];
            printf("Digite o nome ou prefixo do time: ");
            scanf("%49s", busca);

            // Cabeçalho usando \t para tabulação fixa
            printf("\nID\tTime\t\tV\tE\tD\tGM\tGS\tS\tPG\n");

            int encontrou = 0;
            for (int i = 0; i < bd_time->qtd_times; i++) {
                Time *t = bd_time->lista_times[i];
                if (strncmp(t->nome, busca, strlen(busca)) == 0) {
                    
                    if (strlen(t->nome) < 8) {
                        printf("%d\t%s\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                               t->id, t->nome, t->v, t->e, t->d,
                               t->gm, t->gs, get_SG(t), get_PG(t));
                    } else {
                        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                               t->id, t->nome, t->v, t->e, t->d,
                               t->gm, t->gs, get_SG(t), get_PG(t));
                    }
                    encontrou = 1;
                }
            }
            if (!encontrou) printf("Nenhum time encontrado com o prefixo '%s'.\n", busca);

        } else if (option == '2') {
            char modo;
            printf("\nEscolha o modo de consulta:\n");
            printf("1 - Por time mandante\n");
            printf("2 - Por time visitante\n");
            printf("3 - Por time mandante ou visitante\n");
            printf("4 - Retornar ao menu principal\n");
            printf("Opcao: ");
            scanf(" %c", &modo);

            if (modo == '1' || modo == '2' || modo == '3') {
                char busca[50];
                printf("Digite o nome: ");
                scanf("%49s", busca);

                printf("\n%-4s %-12s %s\n", "ID", "Time1", "Time2");

                int encontrou = 0;
                for (int i = 0; i < bd_partida->qtd_partidas; i++) {
                    Partida *p = bd_partida->partidas[i];
                    char nome1[50] = "", nome2[50] = "";

                    for (int t = 0; t < bd_time->qtd_times; t++) {
                        if (bd_time->lista_times[t]->id == p->id_time1)
                            strcpy(nome1, bd_time->lista_times[t]->nome);
                        if (bd_time->lista_times[t]->id == p->id_time2)
                            strcpy(nome2, bd_time->lista_times[t]->nome);
                    }

                    int imprime = 0;
                    if (modo == '1' && strncmp(nome1, busca, strlen(busca)) == 0) imprime = 1;
                    else if (modo == '2' && strncmp(nome2, busca, strlen(busca)) == 0) imprime = 1;
                    else if (modo == '3' && (strncmp(nome1, busca, strlen(busca)) == 0 ||
                                             strncmp(nome2, busca, strlen(busca)) == 0)) imprime = 1;

                    if (imprime) {
                        printf("%-4d %-10s %d x %d  %-10s\n",
                               p->id, nome1, p->gols_time1, p->gols_time2, nome2);
                        encontrou = 1;
                    }
                }
                if (!encontrou) printf("Nenhuma partida encontrada com o prefixo '%s'.\n", busca);
            }

        } else if (option == '6') {
            imprimir_classificação(bd_time);
            
        }
        printf("\nPressione ENTER para sair...");
        getchar(); 
        getchar();
    }


    destruir_times(bd_time);
    destruir_BDPartidas(bd_partida);

    return 0;
}
