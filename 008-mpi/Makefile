# GNU Makefile

CC = mpicc
CCFLAGS = -Wall -O3
LDFLAGS =
#LDFLAGS = -llmpe -lmpe
TARGET = gmat main_mpi help

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

main_mpi: matrizv3.o toolsv3.o matriz-operacoesv3.o matriz-operacoes-mpi.o main_mpi.c
			$(CC) $(CCFLAGS) matriz-operacoesv3.o matrizv3.o toolsv3.o matriz-operacoes-mpi.o main_mpi.c -o $@ $(LDFLAGS)

gmat: matrizv3.o toolsv3.o gera_matrizv3.c
		$(CC) $(CCFLAGS) matrizv3.o toolsv3.o gera_matrizv3.c -o $@ $(LDFLAGS)

#run: mpirun -np 4 main_mpi
#run: mpirun -np 6 --hostfile mp main_mpi (antes ssh ppa-2)

clean:
	rm -f *.o *~ $(TARGET)

help:
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./main_mpi 5x4-mat.map 4x5-mat.map"
	@echo "./main_mpi 1000x500-mat.map 500x1000-mat.map 10"