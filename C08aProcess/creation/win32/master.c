#include <windows.h>
#include <stdio.h>

int main(VOID) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL
                , "worker.exe"
                , NULL
                , NULL
                , FALSE
                , 0
                , NULL
                , NULL
                , &si
                , &pi)) {
        fprintf(stderr, "CreateProcess failed");
        exit(1);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("Child completes, and parent exists.");

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
