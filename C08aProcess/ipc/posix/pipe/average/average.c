#include <stdio.h>

int main() {

    long sum = 0l;
    long n;
    int count = 0;

    while (EOF != scanf("%ld", &n)) {
        sum += n;
        count ++;
    }

    printf("%f\n", (double)sum / (double)count);

    return 0;
}
