#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/*
#include <time.h>
#include <sys/time.h>

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec + (double) t.tv_usec / 1000000;
}*/

int main (int argc, char *argv[]) {
  int i, n = 10, tid;

  //double start_time = wtime();
  #pragma omp parallel private(tid)
  {
   tid = omp_get_thread_num();
   printf("Hello World from thread = %d\n", tid);

   #pragma omp for schedule (dynamic,2) private (i)
    for (i=0; i < n; i++) {
      int load = tid % 2;
      if (!load) {
         printf ("TID (%d) ->Inside bigWork function(%d)(i=%d)\n", tid, load, i);
         sleep(10);
         printf ("TID (%d) ->Out of bigWork function(%d)\n", tid, load);
      } else { 
         printf ("TID (%d) ->Inside smallWork function(%d)(i=%d)\n", tid, load, i);
         sleep(1);
         printf ("TID (%d) ->Out of smallWork function(%d)\n", tid, load);
      }
  }
 }

 //double end_time = wtime();
 //printf("\nTempo:\t%.6f sec \n", end_time - start_time);

}
