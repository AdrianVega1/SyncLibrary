#include <pthread.h>
#include <stdio.h>

typedef struct {

  pthread_mutex_t mutex;
  int count;
  int num_threads;
  pthread_cond_t condition;
} barrera;

void barrier_init(barrera *barrier, int num_threads) {
  barrier->count = 0;
  barrier->num_threads = num_threads;
  pthread_mutex_init(&barrier->mutex, NULL);
  pthread_cond_init(&barrier->condition, NULL);
}

void barrier_wait(barrera *barrier) {
  pthread_mutex_lock(&barrier->mutex); // hace mutex_lock para que solo acceda un hilo a la vez
  barrier->count++;     
  if (barrier->count == barrier->num_threads) { 
    pthread_cond_broadcast(&barrier->condition); // se desbloquean todos los hilos
    barrier->count = 0;       
  } else {
    pthread_cond_wait(&barrier->condition, &barrier->mutex); // hilo espera a que lleguen los hilos a la barrera
  }
  pthread_mutex_unlock(&barrier->mutex); // desbloquea el mutex
}

void barrier_destroy(barrera *barrier) {
  pthread_mutex_destroy(&barrier->mutex);    // destruye el mutex
  pthread_cond_destroy(&barrier->condition); // destruye la condición
}