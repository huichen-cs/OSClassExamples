/*
 * Sample program
 *   Silberschatz, Abraham, Greg Gagne, and Peter B. Galvin. Operating system
 *   concepts. Wiley, 2018. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 25

int main(VOID) {

  HANDLE ReadHandle, WriteHandle;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  char message[BUFFER_SIZE] = "Greetings";
  DWORD written;

  /* set up security attributes allowing pipes to be inherited */
  SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES),NULL,TRUE};

  /* allocate memory */
  ZeroMemory(&pi, sizeof(pi));

  /* create the pipe */
  if (!CreatePipe(&ReadHandle, &WriteHandle, &sa, 0)) {
   fprintf(stderr, "Create Pipe Failed");
   return 1;
  }

  /* establish the START_INFO structure for the child process */
  GetStartupInfo(&si);
  si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

  /* redirect standard input to the read end of the pipe */
  si.hStdInput = ReadHandle;
  si.dwFlags = STARTF_USESTDHANDLES;

  /* don't allow the child to inherit the write end of pipe */
  SetHandleInformation(WriteHandle, HANDLE_FLAG_INHERIT, 0);

  /* create the child process */
  CreateProcess(NULL, "child.exe", NULL, NULL,
                TRUE, /* inherit handles */
                0, NULL, NULL, &si, &pi);

  /* close the unused end of the pipe */
  CloseHandle(ReadHandle);

  /* the parent writes to the pipe */
  if (!WriteFile(WriteHandle, message,BUFFER_SIZE,&written,NULL)) {
   fprintf(stderr, "Error writing to pipe.");
  }

  /* close the write end of the pipe */
  CloseHandle(WriteHandle);

  /* wait for the child to exit */
  WaitForSingleObject(pi.hProcess, INFINITE);

  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  return 0;
}
