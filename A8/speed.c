#include <stdio.h>
#include <time.h>
#include <unistd.h>

int get_cpu_speed() {
  // TODO: this function should return the clock speed of the
  // CPU in MHz
  unsigned int low, high;
  asm (
       "cpuid;" //serializing instruction: force CPU to in-order execution
       "rdtsc;"
       : "=a"(low), "=d"(high)
       :
       );
  unsigned long long ts_counter1 = ((unsigned long long)high << 32) | low;
  //wait
  sleep(1);
  asm (
       "cpuid;"
       "rdtsc;"
       : "=a"(low), "=d"(high)
       :
       );
  unsigned long long ts_counter2 = ((unsigned long long)high << 32) | low;
  unsigned long long cycles = ts_counter2 - ts_counter1;
  return (int)(cycles / 1000000);
}

int main() {
  printf("CPU clock has %d MHz\n", get_cpu_speed());
  return 0;
}

