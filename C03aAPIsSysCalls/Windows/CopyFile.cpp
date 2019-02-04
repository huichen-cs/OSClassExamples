/**
 * This program is wrttien in a way to be as similar to the Linux
 * version of this program as possible. As such, it deviates somewhat
 * from recommended practice from Windows application development,
 * such as character encoding, Windows customized entry point of
 * application (_tmain or wmain, review the discussion here at,
 * https://stackoverflow.com/a/895894)
 */
#include <iostream>

#include <cstdlib>  /* to use exit: see "man 3 exit"            */

#include <windows.h> /* Windows API Functions: CreateFile, ReadFile, WriteFile */

static void Usage(char* app);
static void ExitIfFailed(char *pathname, HANDLE hFile);
static void ExitIfFailed(char *srcpathname, char *dstpathname, int status);
static int CopyFile(HANDLE hSrcFile, HANDLE hDstFile);

static const int BUFFER_SIZE = 1024;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        Usage(argv[0]);
        return 0;
    }

    // see https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-createfilea
    HANDLE hSrcFile =
            CreateFile(argv[1],                // path of the file
                       GENERIC_READ,           // open for reading
                       0,                      // do not share
                       NULL,                   // default security
                       OPEN_EXISTING,          // open existing file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template
    ExitIfFailed(argv[1], hSrcFile);


    HANDLE hDstFile =
            CreateFile(argv[2],                // path of the file
                       GENERIC_WRITE,          // open for reading
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_NEW,             // open existing file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template
    ExitIfFailed(argv[2], hDstFile);

    int status = CopyFile(hSrcFile, hDstFile);
    ExitIfFailed(argv[1], argv[2], status);

    CloseHandle(hSrcFile);
    CloseHandle(hDstFile);

    std::cout << "copyed " << argv[1] << " to " << argv[2] << std::endl;

    return EXIT_SUCCESS;
}

static void Usage(char* app) {
    std::cout << "Usage: " << app << " src_file dest_file" << std::endl;
}

static void ExitIfFailed(char *pathname, HANDLE hFile) {
  if (hFile == INVALID_HANDLE_VALUE) {
    DWORD errorCode = GetLastError();
    LPVOID lpMsgBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

        std::cerr
            << "When " << pathname
            << " being opened error occured with error no: "
            << errorCode << " and error message: "
            << (LPCTSTR)lpMsgBuf
            << std::endl;
        exit(EXIT_FAILURE);
    }
}

static void ExitIfFailed(char *srcpathname, char *dstpathname, int status) {
    if (status == -1) {
      DWORD errorCode = GetLastError();
      LPVOID lpMsgBuf;

      FormatMessage(
          FORMAT_MESSAGE_ALLOCATE_BUFFER |
          FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
          NULL,
          errorCode,
          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
          (LPTSTR) &lpMsgBuf,
          0, NULL );

        std::cerr
            << "When " << srcpathname << " was being copied to " << dstpathname
            << " error occured with error no: "
            << errorCode << " and error message: "
            << (LPCTSTR)lpMsgBuf
            << std::endl;
        exit(EXIT_FAILURE);
    }
}

static int CopyFile(HANDLE hSrcFile, HANDLE hDstFile) {
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, bytesWritten;
    BOOL readStatus;

    // See https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-readfile
    while ((readStatus = ReadFile(hSrcFile,
                                  buffer,
                                  BUFFER_SIZE - 1,
                                  &bytesRead,
                                  NULL))) {
        if (bytesRead == 0) break;
        // See https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-writefile
        if (!WriteFile(hDstFile,           // open file handle
                       buffer,             // start of data to write
                       bytesRead,          // number of bytes to write
                       &bytesWritten,      // number of bytes that were written
                       NULL)) {
            return -1;
        }
    }

    if (!readStatus) return -1;
    return 0;
}
