#include "thread.h"

#define N 100000000

enum { LOCK, UNLOCK };

long sum = 0;
int locked = UNLOCK;

void Tsum() {
retry:
  if (locked != UNLOCK) {
    goto retry;
  }
  locked = LOCK;

  sum++;
  locked = UNLOCK;
}

int main() {
  create(Tsum);
  create(Tsum);
  join();
  printf("sum = %ld\n", sum);
}
