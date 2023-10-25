#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: num not provided\n");
        return 1;
    }

    int num = atoi(argv[1]);
    char *base_name = getenv("FILE_NAME");
    if (!base_name) {
        base_name = "failik";
    }

    char file_name[100];
    sprintf(file_name, "%s_%d.txt", base_name, num);

    FILE *f = fopen(file_name, "w");
    if (!f) {
        perror("Failed to open file");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < num; i++) {
        fprintf(f, "%f\n", (double)rand() / RAND_MAX);
    }
    fclose(f);
    return 0;
}

