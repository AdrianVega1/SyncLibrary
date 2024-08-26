#include "sync.h"
#include <pthread.h>
#include <stdio.h>

#define NUM_LECTORES 5
#define NUM_ESCRITORES 3
#define NUM_THREADS 4

semaphore s;

int dato_global = 0;

mi_rwlock rwlock;

barrera barrier;

void *testSem(void *arg) {
  // Funcion de ejemplo para el semaforo. Este ejemplo
  // consiste en que en un restaurante hay un numero limitado
  // de mesas para los clientes. Por ende, los clientes que
  // lleguen cuando las mesas estan ocupadas, se quedan en
  // la fila hasta que una mesa sea liberada. En este caso,
  // los hilos representan a los clientes y las mesas representan
  // los recursos disponibles.
  long id = (long)arg;
  printf("Customer number %ld is waiting for a table to eat!\n", id);

  waitSem(&s);
  printf("Customer number %ld has taken a table!\n", id);

  usleep(2000); // simular tiempo de comida

  signalSem(&s);
  printf("Customer number %ld has left the table!\n", id);
  return NULL;
}

void* funcion_lector(void* arg) {
    long id = (long)arg;

    for (int i = 0; i < 4; i++) {//Cada lector realiza 4 lecturas
        adquirir_lock_lectura(&rwlock);
        printf("Lector %ld leyendo... (lectura %d): dato_global = %d\n", id, i + 1, dato_global);
        liberar_lock_lectura(&rwlock);
        usleep(100000);//Espera un poco antes de la próxima lectura
    }
    return NULL;
}

void* funcion_escritor(void* arg) {
    long id = (long)arg;

    for (int i = 0; i < 3; i++) {//Cada escritor realiza 3 escrituras
        adquirir_lock_escritura(&rwlock);
        dato_global = rand() % 100;//Modificar la variable global
        printf("Escritor %ld escribiendo... (escritura %d): dato_global = %d\n", id, i + 1, dato_global);
        liberar_lock_escritura(&rwlock);
        usleep(200000);//Espera un poco antes de la próxima escritura
    }
    return NULL;
}

void *testBar(void *arg) {
  int *thread_num = (int *)arg;
  printf("Jugador %d: esperando para jugar\n",
         *thread_num);

  barrier_wait(&barrier); // jugadores esperan a que lleguen a jugar

  printf("Jugador %d: ha empezado a jugar\n",
         *thread_num); // jugadores empiezan a jugar
  return NULL;
}

int main(void) {
    printf("Iniciando ejemplo de semaforo:\n");
    printf("--------------------------------------\n");
    semaphore_init(&s, 3);

    pthread_t threads[10];
    // Se crean los threads
    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, testSem, (void *)(long)i);
    }

    // Se espera a que los threads terminen
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("--------------------------------------\n");

    printf("Iniciando ejemplo de read/write lock:\n");
    printf("--------------------------------------\n");
    srand(time(NULL));
    pthread_t lectores[NUM_LECTORES], escritores[NUM_ESCRITORES];
    mi_rwlock_init(&rwlock);

    //Crear hilos de lectores
    for (long i = 0; i < NUM_LECTORES; i++) {
        pthread_create(&lectores[i], NULL, funcion_lector, (void*)i);
    }

    //Crear hilos de escritores
    for (long i = 0; i < NUM_ESCRITORES; i++) {
        pthread_create(&escritores[i], NULL, funcion_escritor, (void*)i);
    }

    //Esperar a que todos los lectores terminen
    for (int i = 0; i < NUM_LECTORES; i++) {
        pthread_join(lectores[i], NULL);
    }

    //Esperar a que todos los escritores terminen
    for (int i = 0; i < NUM_ESCRITORES; i++) {
        pthread_join(escritores[i], NULL);
    }
    printf("--------------------------------------\n");

    printf("Iniciando ejemplo de read/write lock:\n");
    printf("--------------------------------------\n");

    pthread_t threadsBar[NUM_THREADS];

    barrier_init(&barrier, NUM_THREADS);

    // Se crean los hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        int n = i;
        int *numPtr = (int *)malloc(sizeof(int));
        *numPtr = n;
        pthread_create(&threadsBar[i], NULL, testBar, (void *)numPtr);
    }
    // Se esperan a que los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadsBar[i], NULL);
    }

    barrier_destroy(&barrier);

    printf("--------------------------------------\n");

    return 0;
}
