#include <sys/syscall.h>
#include <unistd.h>

int main() {
  // while (1) ;
  // printf("Hello, World\n");
  syscall(SYS_exit, 42);
  // return 0;
}