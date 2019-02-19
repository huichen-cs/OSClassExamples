#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {

  char write_msg[BUFFER_SIZE] = "Greetings";
  char read_msg[BUFFER_SIZE];

  int fd[2]; /* a pipe has 2 ends, thus an array of size "2" */
  pid_t pid;

  /* create the pipe */
  if (pipe(fd) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
   }

   /* fork a child process */
   pid = fork();
   if (-1 == pid) { /* error occurred */
       perror("fork");
       exit(EXIT_FAILURE);
   } else if (pid > 0) { /* parent process */
     /* an ordinary pipe is unidirectional, and the array fd
      * is duplicated, but one end is to be used. Since 
      * by design of this program, the parent is to write
      * to the pipe, thus, we close the read end
      * of the pipe that is unused */
     close(fd[READ_END]);

     /* write to the pipe */
     write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

     /* we finished writing, so we close the
      * write end of the pipe */
     close(fd[WRITE_END]);
   } else { /* child process */
     /* an ordinary pipe is unidirectional, and the array fd
      * is duplicated, but one end is to be used. Since 
      * by design of this program, the child is to read
      * from the pipe, thus, we close the write end
      * of the pipe that is unused */
     close(fd[WRITE_END]);

     /* read from the pipe */
     read(fd[READ_END], read_msg, BUFFER_SIZE);

     printf("read %s",read_msg);

     /* close the read end of the pipe */
     close(fd[READ_END]);
   }

   return 0;
}

