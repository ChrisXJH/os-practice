#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile int counter = 0;
int loops;

#ifdef ENABLE_LOCK
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
#endif

void *worker(void *arg) {
  for (int i = 0; i < loops; i++) {
    #ifdef ENABLE_LOCK
    pthread_mutex_lock(&lock);
    #endif

    counter++;

    #ifdef ENABLE_LOCK
    pthread_mutex_unlock(&lock);
    #endif
  }
  return NULL;
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Invalid number of arguments. Usage: ./lock <loops>\n");
    exit(1);
  }
  loops = atoi(argv[1]);
  pthread_t p1, p2;
  printf("Initial value: %d\n", counter);
  pthread_create(&p1, NULL, worker, NULL);
  pthread_create(&p2, NULL, worker, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  printf("Final value: %d\n", counter);
  return 0;
}
