#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Example: %s <CommandName1;CommandName2;...>\n", argv[0]);
        return 1;
    }
    char *token;
    char *commands = strdup(argv[1]);

    token = strtok(commands, ";");
    while (token) {
        printf("Performing: %s\n", token);

        int returnCode = system(token);
        printf("FinishingCode: %d\n", returnCode);

        token = strtok(NULL, ";");
    }
    free(commands);
    return 0;
}

