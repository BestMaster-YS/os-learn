#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define REGS_FOREACH(_) _(X) _(Y)
#define RUN_LOGIN                                                              \
  X1 = !X && Y;                                                                \
  Y1 = !X && !Y;

#define DEFINE(X) static int X, X##1;
#define UPDATE(X) X = X##1;
#define PRINT(X) printf(#X " = %d; ", X);

int main(int argc, char *argv[]) {
  REGS_FOREACH(DEFINE);
  while (1) {
    RUN_LOGIN;
    REGS_FOREACH(PRINT);
    REGS_FOREACH(UPDATE);
    putchar('\n');
    sleep(1);
  }
  return 0;
}
