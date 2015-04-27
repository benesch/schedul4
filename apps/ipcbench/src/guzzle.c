#include <stdio.h>

#define NITERATIONS  (1 << 25)

int run(void) {
  for (volatile int i = 0; i < NITERATIONS; i++) {
    if ((i % 1000000) == 0) {
      printf("GUZZLE\n");
    }
  }

  return 0;
}
