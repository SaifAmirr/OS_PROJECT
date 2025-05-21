#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"




int main(int argc, char *argv[]) {
  int pid;
  int k, nprocess = 10;
  int pids[nprocess];
  int z, steps = 1000000;
  char buffer_src[1024], buffer_dst[1024];


  for (k = 0; k < nprocess; k++) {
    pid = fork();
    if (pid < 0) {
      printf("%d failed in fork!\n", getpid());
      exit(1);

    }
    else if (pid == 0) {
      // child
      sleep(30);

      for (z = 0; z < steps; z += 1) {
         // copy buffers one inside the other and back
         // used for wasting cpu time
         memmove(buffer_dst, buffer_src, 1024);
         memmove(buffer_src, buffer_dst, 1024);
      }
      printf("[pid=%d] finished\n", getpid());
      exit(0);
    }
    else {
      // parent
      pids[k] = pid;
    }
  }

  for (k = 0; k < nprocess; k++) {
    int prio = random() %100 + 1;
    setpriority(pids[k], prio);
    printf("[pid=%d] created with priority=%d\n", pids[k], prio);
  }

  for (k = 0; k < nprocess; k++) {
    pid = wait(0);
    printf("[pid=%d] terminated\n", pid);
  }

  print_averages();
  printf("All processes completed.\n");
  exit(0);
}
