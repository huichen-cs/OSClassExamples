#include <inttypes.h>
#include <stdio.h>

int main() {
  int32_t sum = 0l;
  int32_t n;
  int count = 0;

  while (EOF != scanf("%" SCNd32, &n)) {
    sum += n;
    count++;
  }

  printf("%f\n", (double)sum / (double)count);

  return 0;
}
