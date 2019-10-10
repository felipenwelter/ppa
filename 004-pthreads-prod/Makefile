# GNU Makefile

CC = gcc
CCFLAGS = -Wall
LDFLAGS = -pthread #-pg
TARGET = gmat pthreads-prod main_thread help

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

pthreads-prod: pthreads-prod.c

main_thread: matrizv3.o toolsv3.o matriz-operacoesv3.o matriz-operacoes-threads.o main_thread.c
			$(CC) $(CCFLAGS) matriz-operacoesv3.o matrizv3.o toolsv3.o matriz-operacoes-threads.o main_thread.c -o $@ $(LDFLAGS)

gmat: matrizv3.o toolsv3.o gera_matrizv3.c
		$(CC) $(CCFLAGS) matrizv3.o toolsv3.o gera_matrizv3.c -o $@ $(LDFLAGS)

clean:
	rm -f *.o *~ $(TARGET)

help:
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./main_thread 5x4-mat.map 4x5-mat.map"
	@echo "./main_thread 1000x500-mat.map 500x1000-mat.map 10"