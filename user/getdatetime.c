
#include "kernel/datetime.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{

  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: gets current date and time \n");
    exit(0);
  }

  struct datetime dt;
  if (datetime(&dt) == 0) {
    printf("Time: %d-%d-%d %d:%d:%d\n",
           dt.year, dt.month, dt.day,
           dt.hour, dt.minute, dt.second);
  } else {
    printf("Failed to get datetime.\n");
  }
  exit(0);
}
