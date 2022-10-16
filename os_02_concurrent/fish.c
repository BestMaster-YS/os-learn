#include "thread-sync.h"
#include "thread.h"

typedef enum {
  LEFT,
  RIGHT,
  ___,
} FishPrevState;

int n = 0;
FishPrevState s = ___;
mutex_t lk = MUTEX_INIT();
cond_t cv = COND_INIT();

void printL() {
  while (1) {
    mutex_lock(&lk);
    while (s == LEFT || n == 3) {
      pthread_cond_wait(&cv, &lk);
    }
    printf("<");
    s = LEFT;
    n++;
    cond_broadcast(&cv);
    mutex_unlock(&lk);
  }
}

void printR() {
  while (1) {
    mutex_lock(&lk);
    while (s == RIGHT || n == 3) {
      pthread_cond_wait(&cv, &lk);
    }
    printf(">");
    s = RIGHT;
    n++;
    cond_broadcast(&cv);
    mutex_unlock(&lk);
  }
}

void print_() {
  while (1) {
    mutex_lock(&lk);
    while (n != 3) {
      pthread_cond_wait(&cv, &lk);
    }
    printf("_ ");
    s = ___;
    n = 0;
    cond_broadcast(&cv);
    mutex_unlock(&lk);
  }
}

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  create(printL);
  create(printR);
  create(print_);
}
