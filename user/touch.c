#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"


int
main(int argc, char *argv[])
{

  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: Creates an empty file if does not exist \n");
    exit(0);
  }
    if (argc != 2) {
        printf("Error: Invalid number of arguments \n");
        exit(0);
    }

    char *filename = argv[1];
    int fd = open(filename, 0);

    if (fd >= 0) {
        // File already exists
        printf("Error: File '%s' already exists\n", filename);
        close(fd);
        exit(0);
    }

    // Create a new file
    fd = open(filename, O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf("Error: Could not create file '%s'\n", filename);
        exit(0);
    }

    close(fd);
    exit(0);
}
