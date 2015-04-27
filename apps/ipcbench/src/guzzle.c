#include <stdio.h>

#define NITERATIONS     (1 << 30)
#define PRINT_INTERVAL  (1 << 20)

int run(void) {
  for (volatile int i = 0; i < NITERATIONS; i++) {
    if ((i % PRINT_INTERVAL) == 0) {
      printf("GUZZLE %d\n", i / PRINT_INTERVAL);
    }
  }
  printf("GUZZLE DONE\n");

  return 0;
}
