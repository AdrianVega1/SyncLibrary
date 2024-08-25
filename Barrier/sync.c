#include "barrera.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

barrera barrier;

void *test(void *arg) {
  int *thread_num = (int *)arg;
  printf("Jugador %d: esperando para jugar\n",
         *thread_num); 

  barrier_wait(&barrier); // jugadores esperan a que lleguen a jugar

  printf("Jugador %d: ha empezado a jugar\n",
         *thread_num); // jugadores empiezan a jugar
  return NULL;
}

int main() {

  pthread_t threads[NUM_THREADS];

  barrier_init(&barrier, NUM_THREADS);

  // Se crean los hilos
  for (int i = 0; i < NUM_THREADS; i++) {
    int n = i;
    int *numPtr = (int *)malloc(sizeof(int));
    *numPtr = n;
    pthread_create(&threads[i], NULL, test, (void *)numPtr);
  }
  // Se esperan a que los hilos terminen
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  barrier_destroy(&barrier);

  return 0;
}