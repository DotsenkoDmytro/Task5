#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char *file_name = NULL;
    int numChild = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i + 1 < argc) {
                file_name = argv[i + 1];
                i++;
            }
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
            if (i + 1 < argc) {
                numChild = atoi(argv[i + 1]);
                i++;
            }
        }
    }
    if (file_name) {
        setenv("FILE_NAME", file_name, 1);
    }

    for (int i = 0; i < numChild; i++) {
        char str_num[10];
        sprintf(str_num, "%d", i+1);
        if (fork() == 0) {
            execl("./child", "./child", str_num, NULL);
            exit(0);
        }
    }
    for (int i = 0; i < numChild; i++) {
        wait(NULL);
    }

    return 0;
}
