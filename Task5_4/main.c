#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>

void printHelp() {
    printf("Info:\n");
    printf("  -h, --help   Print \"Info\".\n");
    printf("  -b, --buffer <num> Set buffer size\n");
}

int main(int argc, char **argv) {
    size_t bufferSize = 127;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printHelp();
            return 0;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) {
            if (i + 1 < argc) {
                bufferSize = atoi(argv[i + 1]);
                i++;
            } else {
                printf("127 buffer capacity.\n");
            }
        }
    }

    char command[bufferSize + 1];
    struct passwd *pw = getpwuid(getuid());
    printf("User: %s!\n", pw->pw_gecos);

    while (1) {
        printf("[%s]$", pw->pw_name);
        fgets(command, bufferSize, stdin);

        // delete sym \n
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "stop") == 0) {
            printf("Wait 3 seconds...\n");
            sleep(3);
            system("clear");
            break;
        } else {
            int return_code = system(command);
            if (return_code != 0) {
                printf("Error!\n");
            }
        }
    }
    return 0;
}
