// #include "thread.h"
#include <pthread.h>
#include <stdio.h>

void *Ta(void *arg) {
  while (1)
    printf("a");
  return NULL;
};

void *Tb(void *arg) {
  while (1)
    printf("b");
  return NULL;
};

void *Tc(void *arg) {
  while (1)
    printf("c");
  return NULL;
}

int main() {
  pthread_t ta, tb, tc;

  ta = pthread_create(&ta, NULL, Ta, NULL);
  tb = pthread_create(&tc, NULL, Tb, NULL);
  // tc = pthread_create(&tb, NULL, Tc, NULL);

  pthread_join(ta, NULL);
  pthread_join(tb, NULL);

  return 0;
}
