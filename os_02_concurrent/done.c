extern int volatile done;

void t() {
  while (!done)
    ;
}
