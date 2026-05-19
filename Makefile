# Variáveis de compilação
CC = gcc
CFLAGS = -Wall -Wextra -g  
OBJ = main.o TAD_Time.o TAD_BDTimes.o TAD_Partida.o TAD_BDPartidas.o
EXEC = sistema_futebol


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)


main.o: main.c
	$(CC) $(CFLAGS) -c main.c

TAD_Time.o: TAD_Time.c TAD_Time.h
	$(CC) $(CFLAGS) -c TAD_Time.c

TAD_BDTimes.o: TAD_BDTimes.c TAD_BDTimes.h
	$(CC) $(CFLAGS) -c TAD_BDTimes.c

TAD_Partida.o: TAD_Partida.c TAD_Partida.h
	$(CC) $(CFLAGS) -c TAD_Partida.c

TAD_BDPartidas.o: TAD_BDPartidas.c TAD_BDPartidas.h
	$(CC) $(CFLAGS) -c TAD_BDPartidas.c

# Comando para limpar os arquivos temporários
clean:
	rm -f *.o $(EXEC)

# Comando para rodar o programa
run: all
	./$(EXEC)