/*
 * Sample program
 *   Silberschatz, Abraham, Greg Gagne, and Peter B. Galvin. Operating system
 *   concepts. Wiley, 2018. 
 */

#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 25

int main(VOID) {

  HANDLE ReadHandle;
  CHAR buffer[BUFFER_SIZE];
  DWORD read;

  /* get the read handle of the pipe */
  ReadHandle = GetStdHandle(STD_INPUT_HANDLE);

  /* the child reads from the pipe */
  if (ReadFile(ReadHandle, buffer, BUFFER_SIZE, &read, NULL)) {
     printf("child read %s",buffer);
  } else {
     fprintf(stderr, "Error reading from pipe");
  }

  return 0;
}
