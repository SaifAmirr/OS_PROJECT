#include "kernel/types.h"
#include "user/user.h"
#include "kernel/ptinfo.h"

int main(int argc, char* argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: display current processes\n");
    exit(0);
  }

  if(argc != 1) {
    printf("ps takes 0 arguments \n");
    exit(0);
  }

  struct uproc table[64];
  int n = 64;

  if (getptable(n, table) == 0) {
    printf("getptable failed\n");
    exit(1);
  }

  printf("PID\tPPID\tSTATE\t\tSIZE\tNAME\n");

  for (int i = 0; i < n; i++) {
    if (table[i].pid == 0)
      continue;

    char *states[] = {
      "UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"
    };

    printf("%d\t%d\t%s\t%ld\t%s\n",
      table[i].pid,
      table[i].ppid,
      states[table[i].state],
      table[i].sz,
      table[i].name);
  }

  exit(0);
}
