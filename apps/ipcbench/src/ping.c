#include <stdio.h>
#include <sel4/sel4.h>
#include <sel4bench/sel4bench.h>

#include "ipcbench.h"
#include "Ping.h"

unsigned long long total_latency;
unsigned long long trials;

static void pong_ev_callback(void *_ UNUSED);

static void ping_ev_fire(void)
{
  trials++;

  pong_ev_reg_callback(&pong_ev_callback, NULL);

  *data = sel4bench_get_cycle_count();
  ping_ev_emit();
}

static void pong_ev_callback(void *_ UNUSED) {
  unsigned long long latency = sel4bench_get_cycle_count() - *data;

  if ((trials % TRIAL_SPOT_INTERVAL) == 0) {
    printf("ping: spot latency %llu cycles\n", latency);
  }

  total_latency += latency;

  if (trials < NTRIALS) {
    ping_ev_fire();
  } else {
    printf("ping: average latency %llu cycles (%llu trials)\n",
      total_latency / trials, trials);
  }
}

int run(void) {
  sel4bench_init();

  printf("ping: giving pong some time...\n");
  for (int i = 0; i < 25; i++) {
    seL4_Yield();
  }

  ping_ev_fire();

  return 0;
}
