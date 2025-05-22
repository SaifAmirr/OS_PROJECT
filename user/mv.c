#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* get_filename(char *path) {
  // Extract last part of the path
  char *p = path + strlen(path);
  while (p >= path && *p != '/') p--;
  return p + 1;
}

void move(char *path1, char *path2) {

  struct stat st;
  char finaldest[128];
  if (stat(path2, &st) == 0 && st.type == T_DIR){
    char *filename = get_filename(path1);
    strcpy(finaldest, path2);
    int len = strlen(finaldest);
    if (finaldest[len - 1] != '/') {
      finaldest[len++] = '/';
    }
    strcpy(finaldest + len, filename);
  }
  else{
     // dest is a file name
     strcpy(finaldest, path2);
  }
  int res=link(path1, finaldest);
  if ( res< 0) {
    printf("mv: failed to link %s to %s\n", path1, finaldest);
    exit(1);
  }
  int res2=unlink(path1);
  if (res2< 0) {
    printf("failed to unlink %s\n", path1);
    // Optional cleanup: remove the destination to avoid leaving a copy
    unlink(finaldest);
    exit(1);
  }
  printf("moved succefully\n");
}

int main(int argc, char *argv[]) {

  if (argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: mv <source> <destination>\n");
    exit(0);
  }
  if (argc != 3) {
    printf("enter 3 strings!!!\n");
    exit(1);
  }

  move(argv[1], argv[2]);
  exit(0);
}
