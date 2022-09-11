#include "thread.h"

#define N 100000000

long sum = 0;

void Tsum() {
  for (int i = 0; i < N; i++) {
    asm volatile("lock addq $1, %0" : "+m"(sum));
  }
}

int xchg(volatile int *addr, int newval) {
  int result;
  asm volatile("lock xchg %0, %1" : "+m"(*addr), "=a"(result) : "1"(newval));
  return result;
}

int main() {
  create(Tsum);
  create(Tsum);
  join();
  printf("sum = %ld\n", sum);
}
