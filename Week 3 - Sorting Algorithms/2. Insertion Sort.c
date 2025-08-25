// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.txt output.txt\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("Error opening input file");
        return 1;
    }

    int *arr = malloc(1000 * sizeof(int));
    if (!arr) {
        perror("Memory allocation failed");
        fclose(fin);
        return 1;
    }

    int n = 0;
    while (fscanf(fin, "%d", &arr[n]) == 1) {
        n++;
        if (n >= 1000) break;
    }
    fclose(fin);

    insertion_sort(arr, n);

    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        perror("Error opening output file");
        free(arr);
        return 1;
    }

    for (int i = 0; i < n; ++i)
        fprintf(fout, "%d ", arr[i]);
    fprintf(fout, "\n");

    fclose(fout);
    free(arr);
    return 0;
}

