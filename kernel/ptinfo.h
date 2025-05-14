#include "types.h"

#define MAX_NAME_LEN 16

struct uproc {
  int pid;
  int ppid;
  int state;
  uint64 sz;
  char name[MAX_NAME_LEN];
};
