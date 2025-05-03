#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int found_flag=0;

void find(const char *path, const char *filename) {
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512], *p;

    // Open the directory
    if ((fd = open(path, 0)) < 0) {
        printf("find: cannot open %s\n", path);
        return;
    }

    // Get directory status
    if (fstat(fd, &st) < 0) { // fstat checks if the file is directory or regular file
        printf("find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    // If it's a directory, scan its contents
    if (st.type == T_DIR) {
        if (strlen(path) + 1 + DIRSIZ >= sizeof buf) {
            printf("find: path too long\n");
            close(fd);
            return;
        }

        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';

        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0) continue;
            if (!strcmp(de.name, ".") || !strcmp(de.name, "..")) continue;

            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;

            if (stat(buf, &st) < 0) {
                fprintf(2, "find: cannot stat %s\n", buf);
                continue;
            }

            // If the file matches, print its path
            if (!strcmp(de.name, filename)) {
              printf("Found: %s\n", buf);
              found_flag=1;
            }

            // Recursively search subdirectories
            if (st.type == T_DIR) {
                find(buf, filename);
            }
        }
    }


    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("error");
        exit(1);
    }

    find(argv[1], argv[2]);
    if (!found_flag) {
      printf("File not found: %s\n", argv[2]);
    }
    exit(0);
}
