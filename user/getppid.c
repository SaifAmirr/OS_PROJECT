#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: parent's proccess id\n");
    exit(0);
  }
  int pid=getpid();
  int ppid=getppid();
  printf("procces id ->%d\n",pid);
  printf("parent's procces id->%d\n",ppid);
  exit(0);

}
