#include "thread.h"
#include <assert.h>
#include <stdatomic.h>

#define N 100000
enum { A_LOCK, B_LOCK, UN_LOCK };
enum { UP, DOWN };

int volatile a = DOWN, b = DOWN, door = UN_LOCK;

atomic_long count;
atomic_int nested;

void critical_section() {
  long cnt = atomic_fetch_add(&count, 1);
  assert(atomic_fetch_add(&nested, 1) == 0);
  atomic_fetch_add(&nested, -1);
}

void TaSum() {
  while (1) {
    a = UP;
    door = B_LOCK;
    while (b == UP && door != A_LOCK)
      critical_section();
    a = DOWN;
  }
}

void TbSum() {
  while (1) {
    b = UP;
    door = A_LOCK;
    while (a == UP && door != B_LOCK)
      critical_section();
    a = DOWN;
  }
}

int main() {
  create(TaSum);
  create(TbSum);
  join();
  printf("nested = %d\n", nested);
  return 0;
}
