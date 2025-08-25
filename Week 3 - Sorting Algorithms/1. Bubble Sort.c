// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Incomplete arguments");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        printf("Error opening input file");
        return 1;
    }

    int *arr = malloc(1000 * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed");
        fclose(fin);
        return 1;
    }

    int n = 0;
    while (fscanf(fin, "%d", &arr[n]) == 1) {
        n++;
        if (n >= 1000) break;
    }
    fclose(fin);

    bubble_sort(arr, n);

    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        printf("Error opening output file");
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