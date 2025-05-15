#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "?") == 0) {
        printf("Usage: rand\n");
        exit(0);
    }

    int random_number = random();
    printf("Random number: %d\n", random_number);

    exit(0);
}
