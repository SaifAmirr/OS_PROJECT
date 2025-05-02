#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define BUF_SIZE 512

int
main(int argc, char *argv[])
{
  int src_fd, dst_fd, n;
  char buf[BUF_SIZE];

  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: copies the content of the source file to the destination file \n");
    exit(0);
  }

  if(argc != 3){
    printf("Error: Invalid number of arguments \n");
    exit(0);
  }

  src_fd = open(argv[1], O_RDONLY);
  if(src_fd < 0){
    printf("cp: cannot open source file %s\n", argv[1]);
    exit(0);
  }

  dst_fd = open(argv[2], O_WRONLY);
  if(dst_fd < 0){
    printf("cp: cannot open destination file %s\n", argv[2]);
    close(src_fd);
    exit(0);
  }

  while((n = read(src_fd, buf, sizeof(buf))) > 0){
    if(write(dst_fd, buf, n) != n){
      printf("cp: write error\n");
      close(src_fd);
      close(dst_fd);
      exit(0);
    }
  }

  if(n < 0){
    printf("cp: read error\n");
  }

  close(src_fd);
  close(dst_fd);
  exit(0);
}
