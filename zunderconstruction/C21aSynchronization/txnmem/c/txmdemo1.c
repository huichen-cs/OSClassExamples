#include <stdio.h>

int main() {
    int counter = 0;    

    __transaction_atomic { 
        counter ++;
    }

    printf("counter = %d\n", counter);

    return 0;
}
