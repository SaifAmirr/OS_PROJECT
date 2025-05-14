#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: count the syscalls\n");
    exit(0);
  }
  int count=countsyscall();
  printf("system call count: %d\n", count);
  exit(0);
}
