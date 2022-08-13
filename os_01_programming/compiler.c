extern int g;

void foo(int x) {
  g++;
  // 访问内存
  asm volatile("nop" ::"r"(x) : "memory"); // compiler barrier
  g++;
}
