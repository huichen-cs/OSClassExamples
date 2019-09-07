/**
 * 1. To compile, run
 *  make
 * 2. Run size as in
 *  size memorylayout
 * 3. Run the program
 *  ./memorylayout
 * 4. Experiment it with 
 *    a) add a function, such as,
 *       void foo() { }
 *    b) add an uninitialized  global variable (one declared outside of the
 *       main function)
 *    c) add an initialized  global variable (one declared outside of the main
 *       function)
 *    d) add a local variable (one declared inside the main)
 *    for each, compile and run size, observe the differences. 
 */
#include <stdlib.h> 
#include <stdio.h>

int x;
int y = 5;

int main(int argc, char *argv[]) {
    int *p;
    int i;
   
    p = (int *)malloc(sizeof(int)*5);

    for (i = 0; i<5; i++) {
        p[i] = i*i;
    }

    printf("   argv's address %p\n", argv);
    printf("   argc's address %p\n", &argc);
    printf("      i's address %p (stack)\n", &i);
    printf("      p's address %p (stack)\n", &p);
    printf("p array's address %p (heap)\n", p);
    printf("      x's address %p (uninitialized data)\n", &x);
    printf("      y's address %p (initialized data or bss)\n", &y);
    printf("   main's address %p (text)\n", main);


    free(p);
    return 0;
}

