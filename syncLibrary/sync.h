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

void *waitSem(semaphore *s) {
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

void *signalSem(semaphore *s) {
  pthread_mutex_lock(&s->mutex);

  s->value++;

  pthread_mutex_unlock(&s->mutex);
  return NULL;
}

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
  pthread_mutex_lock(&barrier->mutex);

  barrier->count++;
  if (barrier->count == barrier->num_threads) {
    pthread_cond_broadcast(&barrier->condition);
    barrier->count = 0;
  } else {
    pthread_cond_wait(&barrier->condition, &barrier->mutex);
  }

  pthread_mutex_unlock(&barrier->mutex);
}

void barrier_destroy(barrera *barrier) {
  pthread_mutex_destroy(&barrier->mutex);
  pthread_cond_destroy(&barrier->condition);
}

typedef struct {
    pthread_mutex_t lock;//Mutex para sincronizar el acceso a la estructura
    int contador_lectores;//Contador de lectores activos
    int escritor_activo;//Flag para indicar si un escritor está activo
} mi_rwlock;

//Inicializar el mutex, con 0 escritores y con la flag de escritores activos en 0
void mi_rwlock_init(mi_rwlock *rw) {
    pthread_mutex_init(&rw->lock, NULL);
    rw->contador_lectores = 0;
    rw->escritor_activo = 0;
}

void adquirir_lock_lectura(mi_rwlock *rw) {
    while (1) {
        pthread_mutex_lock(&rw->lock);

        if (rw->escritor_activo == 0) {//Si no hay escritor activo
            rw->contador_lectores++;
            pthread_mutex_unlock(&rw->lock);
            break;//Lectura permitida, salir del bucle
        }

        pthread_mutex_unlock(&rw->lock);
        usleep(1000);//Evitar espera activa
    }
}

void liberar_lock_lectura(mi_rwlock *rw) {
    pthread_mutex_lock(&rw->lock);
    rw->contador_lectores--;
    pthread_mutex_unlock(&rw->lock);
}

void adquirir_lock_escritura(mi_rwlock *rw) {
    while (1) {
        pthread_mutex_lock(&rw->lock);

        if (rw->contador_lectores == 0 && rw->escritor_activo == 0) {// Si no hay lectores ni escritor activo
            rw->escritor_activo = 1;
            pthread_mutex_unlock(&rw->lock);
            break;//Escritura permitida, salir del bucle
        }

        pthread_mutex_unlock(&rw->lock);
        usleep(1000);//Evitar espera activa
    }
}

void liberar_lock_escritura(mi_rwlock *rw) {
    pthread_mutex_lock(&rw->lock);
    rw->escritor_activo = 0;
    pthread_mutex_unlock(&rw->lock);
}
