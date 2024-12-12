#include <inttypes.h>
#include <stdio.h>

int main() {
  int32_t numbers[5] = {1, 2, 4, 8, 16};

  for (int i = 0; i < 5; i++) {
    printf("%" SCNd32 "\n", numbers[i]);
  }

  return 0;
}
