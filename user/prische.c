#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// Declare setpriority() if not in user.h
// int setpriority(int pid, int priority);

int main(int argc, char *argv[]) {
  int pid;
  int k, nprocess = 5;
  int z, steps = 1000000;
  char buffer_src[1024], buffer_dst[1024];

  for (k = 0; k < nprocess; k++) {
    sleep(2); // Stagger creation time to break FCFS pattern

    pid = fork();
    if (pid < 0) {
      printf("Fork failed!\n");
      exit(1);
    }

    if (pid == 0) {
      // === Child process ===
      int prio = nprocess - k; // Higher priority for later children
      setpriority(getpid(), prio);
      printf("[pid=%d] created with priority=%d\n", getpid(), prio);

      for (z = 0; z < steps; z++) {
        memmove(buffer_dst, buffer_src, 1024);
        memmove(buffer_src, buffer_dst, 1024);
      }

      printf("[pid=%d] finished\n", getpid());
      exit(0); // Important: prevent children from continuing the loop
    }

    // Parent continues to next fork
  }

  // === Parent waits for all children ===
  for (k = 0; k < nprocess; k++) {
    pid = wait(0);
    printf("[pid=%d] terminated\n", pid);
  }
  print_averages();
  printf("All processes completed.\n");
  exit(0);
}
