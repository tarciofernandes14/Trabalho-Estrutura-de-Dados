#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct {

    int id;
    char nome[50];
    int v, e, gm, gs;

    } Time;

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
    new_Time->gm = 0;
    new_Time->gs = 0;

    return new_Time;
}

int main(){
    
    FILE *arquivo_time = fopen("times.csv","r");
    if (arquivo_time == NULL) {
        printf("Arquivo Inválido.");
        return 0;    
    }     

    Time *lista_times[11];
    char linha[256];
    int cont = 0;

    fgets(linha, sizeof(linha), arquivo_time); //lê o arquivo uma vez para ignorar primeira linha que contém (ID,Time)

    while (cont < 10 && fgets(linha, sizeof(linha), arquivo_time) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; //Troca \n por \0 para encerrar a linha sem o pulo de linha em cada time.

        char *id_texto = strtok(linha, ",");
        char *nome_texto = strtok(NULL, ",");
        
        if (id_texto != NULL && nome_texto != NULL) {
            
            int id_int = atoi(id_texto);
            lista_times[cont] = create_Time((id_int), nome_texto);
            cont++;
        }
    }
    fclose(arquivo_time);
    for (int j =0; j <cont; j++){
        printf("ID: %d | Nome: %s \n", lista_times[j]->id, lista_times[j]->nome);


    }
    //desaloca os itens da lista de números da memória
    for (int i = 0; i < cont; i++) {
        free(lista_times[i]);
    }
    return 0;
}
