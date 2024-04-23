#include <stdio.h>
#include <string.h>

// Function to mirror the image both left-to-right and top-to-bottom
void mirrorImage(char image[20][20], int rows, int cols) {
    char mirrored[20][20];

    // Mirror left-to-right
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mirrored[i][cols - 1 - j] = image[i][j];
        }
    }

    // Mirror top-to-bottom
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image[rows - 1 - i][j] = mirrored[i][j];
        }
    }
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) {
        return 1;
    }

    char results[20][20][20]; 

    for (int t = 1; t <= T; t++) {
        int R, C;
        if (scanf("%d %d", &R, &C) != 2) {
            return 1;
        }

        char image[20][20];

        // Input the image
        for (int i = 0; i < R; i++) {
            if (scanf("%s", image[i]) != 1) {
                return 1;
            }
        }

        mirrorImage(image, R, C);

        for (int i = 0; i < R; i++) {
            strcpy(results[t][i], image[i]);
        }
    }

    for (int t = 1; t <= T; t++) {
        printf("\nTest %d\n", t);
        int R;
        for (R = 0; results[t][R][0] != '\0'; R++) {
            printf("%s\n", results[t][R]);
        }

        // Print an empty line between test cases
        if (t < T) {
            printf("\n");
        }
    }

    return 0;
}