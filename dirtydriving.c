#include <stdio.h>
#include <stdlib.h>

// Merge sort functions
void merge(int *array, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    // Create temporary arrays
    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        left[i] = array[start + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = array[mid + 1 + j];
    }

    // Merge the temporary arrays back into the original array
    int i = 0, j = 0, k = start;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of the left array, if there are any
    while (i < n1) {
        array[k] = left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of the right array, if there are any
    while (j < n2) {
        array[k] = right[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    free(left);
    free(right);
}

void mergeSort(int *array, int start, int end) {
    if (start < end) {
        // Find the middle point
        int mid = start + (end - start) / 2;

        // Sort the first and second halves
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);

        // Merge the sorted halves
        merge(array, start, mid, end);
    }
}

int main() {
    int n, p;
    if (scanf("%d %d", &n, &p) != 1) {
        fprintf(stderr, "Error reading input values for n and p.\n");
        return 1;
    }

    int *distances = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &distances[i]) != 1) {
            fprintf(stderr, "Error reading input values for distances.\n");
            free(distances);
            return 1;
        }
    }

    // Sort the distances
    mergeSort(distances, 0, n - 1);

    int maxMinDistance = 0;
    for (int i = 0; i < n; i++) {
        int minDistance = p * (i + 1) - distances[i] + 1;
        if (minDistance > maxMinDistance) {
            maxMinDistance = minDistance;
        }
    }

    printf("%d\n", maxMinDistance);

    // Free the dynamically allocated memory
    free(distances);

    return 0;
}








