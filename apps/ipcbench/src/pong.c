#include <stdio.h>
#include <sel4bench/sel4bench.h>

#include "ipcbench.h"
#include "Pong.h"

unsigned long long total_latency;
unsigned long long trials;

static void ping_ev_callback(void *_ UNUSED);

static void pong_ev_fire(void)
{
  ping_ev_reg_callback(&ping_ev_callback, NULL);

  *data = sel4bench_get_cycle_count();
  pong_ev_emit();
}

static void ping_ev_callback(void *_ UNUSED) {
  unsigned long long latency = sel4bench_get_cycle_count() - *data;

  if ((trials % TRIAL_SPOT_INTERVAL) == 0) {
    printf("pong: spot latency %llu cycles\n", latency);
  }

  total_latency += latency;

  if (++trials == NTRIALS) {
    printf("pong: average latency %llu cycles (%llu trials)\n",
      total_latency / trials, trials);
  }

  pong_ev_fire();
}

int run(void) {
  ping_ev_reg_callback(&ping_ev_callback, NULL);
  return 0;
}
