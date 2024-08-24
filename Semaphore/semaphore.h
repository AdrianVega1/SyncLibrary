#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
  int value;
  pthread_mutex_t mutex;
} semaphore;

void semaphore_init(semaphore *s, int value) {
  s->value = value;
  pthread_mutex_init(&s->mutex, NULL);
}

void *wait(semaphore *s) {
  // Espera activa para los que tienen que hacer fila
  while (1) {
    pthread_mutex_lock(&s->mutex);

    if (s->value > 0) {
      s->value--;
      pthread_mutex_unlock(&s->mutex);
      break;
    }

    pthread_mutex_unlock(&s->mutex);

    usleep(900); // Para minimizar el consumo de CPU
  }

  return NULL;
}

void *signal(semaphore *s) {
  pthread_mutex_lock(&s->mutex);

  s->value++;

  pthread_mutex_unlock(&s->mutex);
  return NULL;
}