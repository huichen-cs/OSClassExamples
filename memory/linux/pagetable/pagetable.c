#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  char pmpath[128];
  uint64_t pageno, frameno, entry;

  if (argc < 2) {
    printf("Usage: %s PID\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  snprintf(pmpath, sizeof(pmpath), "/proc/%s/pagemap", argv[1]);

  fd = open(pmpath, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "open %s: %s\n", pmpath, strerror(errno));
    exit(EXIT_FAILURE);
  }

  if (sizeof(uint64_t) < 64 / 8) {
    fprintf(stderr, "Logical error: data type too short\n");
    exit(EXIT_FAILURE);
  }

  pageno = 0;
  while (read(fd, &entry, 8) > 0) {
    frameno = entry & 0x003fffffffffffffull;
    if (entry & 0x8000000000000000ull) {
      printf("0x%016" PRIx64 "0x%016" PRIx64 "0x%16" PRIx64 "0x%016" PRIx64
             "\n",
             pageno, pageno << 12, entry, frameno);
    }
    pageno++;
  }
  printf("%18s %18s %18s %18s\n", "^", "^", "^", "^");
  printf("%18s %18s %18s %18s\n", "page number", "page base", "entry value",
         "frame number");
  printf("max(pageno) = 0x%016" PRIx64 "\n", pageno - 1);

  close(fd);

  return EXIT_SUCCESS;
}
