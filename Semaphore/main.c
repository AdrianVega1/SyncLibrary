#include "semaphore.h"
#include <pthread.h>
#include <stdio.h>

semaphore s;

void *test(void *arg) {
  // Funcion de ejemplo para el semaforo. Este ejemplo
  // consiste en que en un restaurante hay un numero limitado
  // de mesas para los clientes. Por ende, los clientes que
  // lleguen cuando las mesas estan ocupadas, se quedan en
  // la fila hasta que una mesa sea liberada. En este caso,
  // los hilos representan a los clientes y las mesas representan
  // los recursos disponibles.
  long id = (long)arg;
  printf("Customer number %ld is waiting for a table to eat!\n", id);

  wait(&s);
  printf("Customer number %ld has taken a table!\n", id);

  usleep(2000); // simular tiempo de comida

  signal(&s);
  printf("Customer number %ld has left the table!\n", id);
  return NULL;
}

int main(void) {

  semaphore_init(&s, 3);

  pthread_t threads[10];
  // Se crean los threads
  for (int i = 0; i < 10; i++) {
    pthread_create(&threads[i], NULL, test, (void *)(long)i);
  }

  // Se espera a que los threads terminen
  for (int i = 0; i < 10; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}