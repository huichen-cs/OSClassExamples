
#include <stdio.h>
#include <stdlib.h>

const int SIZE = 1024 * 1024 * 32;

int main(int argc, char *argv[]) {
  float *a, *b, *c, *d, *e, *f, *g, *h;

  a = malloc(SIZE * sizeof(float));
  b = malloc(SIZE * sizeof(float));
  c = malloc(SIZE * sizeof(float));
  d = malloc(SIZE * sizeof(float));
  e = malloc(SIZE * sizeof(float));
  f = malloc(SIZE * sizeof(float));
  g = malloc(SIZE * sizeof(float));
  h = malloc(SIZE * sizeof(float));
  printf("allocated\n");

  for (int i = 0; i < SIZE; i++) {
    a[i] = 0.1 + i * 0.002;
    b[i] = (i * 0.1) * 0.003;
    c[i] = (i * 0.3) * 0.004;
    d[i] = 0.2 + i * 0.005;
    e[i] = 0.3 + i * 0.006;
    f[i] = 0.4 + i * 0.001;
    g[i] = i * 0.002;
    h[i] = i * 0.003;
  }
  printf("initialized\n");

  for (int j = 0; j < 10; j++) {
    for (int i = 0; i < SIZE; i++) {
      a[random() % SIZE] = b[random() % SIZE] +
                           c[random() % SIZE] * d[random() % SIZE] -
                           e[random() % SIZE] / f[random() % SIZE] -
                           g[random() % SIZE] * h[random() % SIZE];
    }
  }

  /*
  for (int j=0; j<10; j++) {
    for (int i=0; i<SIZE; i++) {
            a[i] =
              b[i] +
              c[i]*d[i] -
              e[i]/f[i] -
              g[i]*h[i];
    }
  }
  */

  printf("%f\n", a[0]);
  printf("%f\n", a[SIZE - 1]);

  free(a);
  free(b);
  free(c);
  free(d);
  free(e);
  free(f);

  printf("done\n");
  return 0;
}
