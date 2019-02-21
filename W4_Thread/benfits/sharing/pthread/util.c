#include <stdio.h>
#include "util.h"

void print_array(char *name, int n, int *numbers) {
  for (int i=0; i<n; i++) {
    printf("%s[%d] = %d\n", name, i, numbers[i]);
  }
}
