#include "thread-sync.h"
#include "thread.h"

int n, count = 0;
mutex_t lk = MUTEX_INIT();
cond_t p_cv = COND_INIT();
cond_t c_cv = COND_INIT();

void Tproduce() {
  while (1) {
    mutex_lock(&lk);
    while (count == n) {
      cond_wait(&p_cv, &lk);
    }
    printf("(");
    count++;
    cond_signal(&c_cv);
    mutex_unlock(&lk);
  }
}

void Tconsume() {
  while (1) {
    mutex_lock(&lk);
    while (count == 0) {
      pthread_cond_wait(&c_cv, &lk);
    }
    printf(")");
    count--;
    cond_signal(&p_cv);
    mutex_unlock(&lk);
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  n = atoi(argv[1]);
  setbuf(stdout, NULL);
  for (int i = 0; i < 8; i++) {
    create(Tproduce);
    create(Tconsume);
  }
}
