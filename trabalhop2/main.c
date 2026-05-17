#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_BDTimes.h"
#include "TAD_BDPartidas.h"
#include "TAD_Time.h"
#include "TAD_Partida.h"

int main(){

    
    BDTimes *bd_time = (BDTimes*)malloc(sizeof(BDTimes));
    if (bd_time == NULL) {
        return 1;
    }
    bd_time->qtd_times = 0;
    
    if(readteams(bd_time) == 0){
        printf("Erro ao carregar o arquivo times.csv \n");
        free(bd_time);
        return 1;
    }

   BDPartidas *bd_partida = criar_BDPartidas(100);
    if (bd_partida == NULL){
        printf("Erro: Faltou memoria para criar o banco de partidas.\n");
        // Limpa os times da memoria antes de fechar por erro
        for (int i = 0; i < bd_time->qtd_times; i++) {
            free(bd_time->lista_times[i]);
        }
        free(bd_time);
        return 1;
    }

    // 4. Carrega as partidas do arquivo CSV
    carregar_partidas_csv(bd_partida, "partidas_parcial.csv");

    processar_campeonato(bd_time, bd_partida);
    
    char option = ' '; 
    while (option != 'q' && option != 'Q'){
        printf("1 - Consultar time \n");
        printf("2 - Consultar partidas \n");
        printf("6 - Imprimir tabela de classificação \n");
        printf("Q - sair \n");
        scanf("%c", &option);
    
    if (option == '1'){
        char busca[50];
            printf("Digite o nome ou prefixo do time: ");
            scanf("%s", busca);
            
            printf("\nID  Time           V  E  D  GM  GS  S   PG\n");
            
            for (int i = 0; i < bd_time->qtd_times; i++) {
                Time *time_atual = bd_time->lista_times[i];
                
                // strncmp compara as letras da busca com o inicio do nome do time
                if (strncmp(time_atual->nome, busca, strlen(busca)) == 0) {
                    
                    int saldo = get_SG(time_atual);
                    int pontos = get_PG(time_atual);
                    
                    printf("%-3d %-14s %-2d %-2d %-2d %-3d %-3d %-3d %-3d\n", 
                           time_atual->id, time_atual->nome, time_atual->v, 
                           time_atual->e, time_atual->d, time_atual->gm, 
                           time_atual->gs, saldo, pontos);
                }
            }
    }


else if (option == '2') {
            char modo = ' ';
            printf("\nEscolha o modo de consulta:\n");
            printf("1 - Por time mandante\n");
            printf("2 - Por time visitante\n");
            printf("3 - Por time mandante ou visitante\n");
            printf("4 - Retornar ao menu princpal\n");
            scanf(" %c", &modo);

            if (modo == '1' || modo == '2' || modo == '3') {
                char busca[50];
                printf("Digite o nome: ");
                scanf("%s", busca);

                printf("\nID  Timel                  Time2\n");

                // Percorre todas as partidas
                for (int i = 0; i < bd_partida->qtd_partidas; i++) {
                    Partida *partida_atual = bd_partida->partidas[i];

                    char nome_time1[50] = "";
                    char nome_time2[50] = "";

                    // Busca os nomes dos times comparando os IDs
                    for (int t = 0; t < bd_time->qtd_times; t++) {
                        if (bd_time->lista_times[t]->id == partida_atual->id_time1) {
                            strcpy(nome_time1, bd_time->lista_times[t]->nome);
                        }
                        if (bd_time->lista_times[t]->id == partida_atual->id_time2) {
                            strcpy(nome_time2, bd_time->lista_times[t]->nome);
                        }
                    }

                    int deve_imprimir = 0;

                    // Verifica se bate com a busca dependendo do modo escolhido
                    if (modo == '1') {
                        if (strncmp(nome_time1, busca, strlen(busca)) == 0) {
                            deve_imprimir = 1;
                        }
                    } else if (modo == '2') {
                        if (strncmp(nome_time2, busca, strlen(busca)) == 0) {
                            deve_imprimir = 1;
                        }
                    } else if (modo == '3') {
                        if (strncmp(nome_time1, busca, strlen(busca)) == 0 || 
                            strncmp(nome_time2, busca, strlen(busca)) == 0) {
                            deve_imprimir = 1;
                        }
                    }

                    if (deve_imprimir == 1) {
                        printf("%-3d %-10s %d x %d  %-10s\n", 
                               partida_atual->id, 
                               nome_time1, 
                               partida_atual->gols_time1, 
                               partida_atual->gols_time2, 
                               nome_time2);
                    }
                }
            }
        }
        else if (option == '6') {
            printf("\n--- TABELA DE CLASSIFICACAO ---\n");
            printf("ID  Time           V  E  D  GM  GS  S   PG\n");
            
            for (int i = 0; i < bd_time->qtd_times; i++) {
                Time *time_atual = bd_time->lista_times[i];
                int saldo = get_SG(time_atual);
                int pontos = get_PG(time_atual);
                
                printf("%-3d %-14s %-2d %-2d %-2d %-3d %-3d %-3d %-3d\n", 
                       time_atual->id, time_atual->nome, time_atual->v, 
                       time_atual->e, time_atual->d, time_atual->gm, 
                       time_atual->gs, saldo, pontos);
            }
        } 
        else if (option == 'Q' || option == 'q') {
            printf("Saindo do sistema...\n");
        } 
        else {
            printf("Opção invalida!\n");
        }
    }

    // 5. Limpeza total da memoria antes do programa fechar
    for (int i = 0; i < bd_time->qtd_times; i++) {
        free(bd_time->lista_times[i]);}
    free(bd_time);

    destruir_BDPartidas(bd_partida);

    return 0;
}