#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void showImage(char image[6][40], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", image[i][j]);
        }
        printf("\n");
    }
}

int main() {
    FILE *file;
    file = fopen("input.txt", "r");

    int cycleCount = 0, x = 1, solution = 0;
    char image[6][40];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            image[i][j] = '.';
        }
    }

    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        int isNoop = strcmp(line, "noop\n") == 0 ? 0 : 1;

        if (-(cycleCount < 20) + (cycleCount - 20) / 40 != (cycleCount + 1 + isNoop - 20) / 40 - (cycleCount + 1 + isNoop < 20)) {
            solution += x * abs(20 + 40 * ((cycleCount + 1 + isNoop - 20) / 40));
        }

        for (int cycle = cycleCount; cycle <= cycleCount + isNoop; cycle++) {
            if (cycle % 40 != x - 1 && cycle % 40 != x && cycle % 40 != x + 1) continue;
            image[cycle / 40][cycle % 40] = '#';
        }

        cycleCount += 1 + isNoop;
        if (!isNoop) continue;

        int value;
        sscanf(line + 5, "%d", &value);
        x += value;
    }

    fclose(file);

    printf("Part 1 solution: %d\n", solution);
    printf("Part 2 solution: \n");
    showImage(image, 6, 40);

    return 0;
}
