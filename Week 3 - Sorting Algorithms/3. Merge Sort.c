// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
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
    while (n < 1000 && fscanf(fin, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(fin);


    mergeSort(arr, 0, n - 1);

    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        perror("Error opening output file");
        free(arr);
        return 1;
    }


    for (int i = 0; i < n; ++i) {
        fprintf(fout, "%d ", arr[i]);
    }
    fprintf(fout, "\n");

    fclose(fout);
    free(arr);
    
    printf("Sorting complete. Check the output file: %s\n", argv[2]);

    return 0;
}