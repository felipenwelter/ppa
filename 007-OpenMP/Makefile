# GNU Makefile

CC = gcc
CCFLAGS = -Wall
LDFLAGS = -fopenmp
TARGET = gmat main_omp help

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

main_omp: matrizv3.o toolsv3.o matriz-operacoesv3.o matriz-operacoes-omp.o main_omp.c
			$(CC) $(CCFLAGS) matriz-operacoesv3.o matrizv3.o toolsv3.o matriz-operacoes-omp.o main_omp.c -o $@ $(LDFLAGS)

gmat: matrizv3.o toolsv3.o gera_matrizv3.c
		$(CC) $(CCFLAGS) matrizv3.o toolsv3.o gera_matrizv3.c -o $@ $(LDFLAGS)

clean:
	rm -f *.o *~ $(TARGET)

help:
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./main_omp 5x4-mat.map 4x5-mat.map"
	@echo "./main_omp 1000x500-mat.map 500x1000-mat.map 10"