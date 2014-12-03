#include <stdio.h>
#include <time.h>

int get_cpu_speed() {
  // TODO: this function should return the clock speed of the
  // CPU in MHz
  uint32_t low, high;
  asm (
       "cpuid;" //serializing instruction: force CPU to in-order execution
       "rdtsc;"
       : "=a"(low), "=d"(high)
       :
       );
  uint64_t ts_counter1 = ((uint64_t)high << 32) | low;
  //wait
  time_t time_a = time(NULL);
  time_t time_b = time(NULL);
  while (difftime(time_b, time_a) < 1) {
    time_b = time(NULL);
  }
  asm (
       "cpuid;"
       "rdtsc;"
       : "=a"(low), "=d"(high)
       :
       );
  uint64_t ts_counter2 = ((uint64_t)high << 32) | low;
  uint64_t cycles = ts_counter2 - ts_counter1;
  return (int)(cycles / 1000000);
}

int main() {
  printf("CPU clock has %d MHz\n", get_cpu_speed());
  return 0;
}

