#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int status, void *arg) {
    int handlerNum = *(int *)arg;
    sleep(1);
    printf("Handler #%d performing...\n", handlerNum);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Example: %s <quantity>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int *handlerNums = (int *)malloc(n * sizeof(int));
    if (!handlerNums) {
        perror("Error! Failed memory allocation\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        handlerNums[i] = n - i;
        if (on_exit(handler, &handlerNums[i])) {
            printf("Error with handler #%d\n", handlerNums[i]);
            free(handlerNums);
            return 1;
        }
    }

    printf("Registrated! Perfoming...\n");
    return 0;
}


