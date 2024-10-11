/**
 * Revised based on the sample code in
 *   Silberschatz, Abraham, Greg Gagne, and Peter B. Galvin. Operating system
 *   concepts. Wiley, 2018.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
  /* the size (in bytes) of shared memory object */
  const int SIZE = 4096;

  /* name of the shared memory object */
  const char *name = "OS";

  /* shared memory file descriptor */
  int fd;

  /* pointer to shared memory obect */
  int *ptr;

  /* open the shared memory object */
  fd = shm_open(name, O_RDWR, 0666);
  if (-1 == fd) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }

  /* memory map the shared memory object */
  ptr = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if ((int *)-1 == ptr) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  /* read from the shared memory object */
  printf("%d", *ptr);

  /* remove the shared memory object */
  shm_unlink(name);

  return 0;
}
