#include <pthread.h>
#include <stdio.h>

volatile int i = 1;

void *spinWait() {
  while (i == 1);
  printf("Unlocked\n");
  return NULL;
}

void *unlock() {
  sleep(5);
  i = 0;
  return NULL;
}

int main(int argc, char const *argv[]) {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, spinWait, NULL);
  pthread_create(&t2, NULL, unlock, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
