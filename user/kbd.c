#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "?") == 0) {
        printf("Usage: kbdint\n");
        exit(0);
    }

    uint64 kbd_count = kbdint();
    printf("Keyboard interrupt count: %ld\n", kbd_count);

    exit(0);
}
