#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

int comparison_count = 0;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + j + 1];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        comparison_count++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void writeToFile(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot write to file %s\n", filename);
        return;
    }
    for (int i = 0; i < n; i++)
        fprintf(file, "%d ", arr[i]);
    fclose(file);
}

int readFromFile(const char *filename, int arr[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return -1;
    }
    int n = 0;
    while (fscanf(file, "%d", &arr[n]) != EOF && n < MAX)
        n++;
    fclose(file);
    return n;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void generateTestFiles() {
    FILE *f;

    // Ascending data
    f = fopen("inAsce.dat", "w");
    for (int i = 1; i <= MAX; i++) fprintf(f, "%d ", i);
    fclose(f);

    // Descending data
    f = fopen("inDesc.dat", "w");
    for (int i = MAX; i >= 1; i--) fprintf(f, "%d ", i);
    fclose(f);

    // Random data
    f = fopen("inRand.dat", "w");
    for (int i = 0; i < MAX; i++) fprintf(f, "%d ", rand() % 1000);
    fclose(f);
}

int main() {
    srand(time(NULL));
    generateTestFiles();

    int choice;
    char inFile[20], outFile[25];
    int arr[MAX];
    int n;
    clock_t start, end;

    while (1) {
        printf("\nMAIN MENU (MERGE SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                snprintf(inFile, sizeof(inFile), "inAsce.dat");
                snprintf(outFile, sizeof(outFile), "outMergeAsce.dat");
                break;
            case 2:
                snprintf(inFile, sizeof(inFile), "inDesc.dat");
                snprintf(outFile, sizeof(outFile), "outMergeDesc.dat");
                break;
            case 3:
                snprintf(inFile, sizeof(inFile), "inRand.dat");
                snprintf(outFile, sizeof(outFile), "outMergeRand.dat");
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                continue;
        }

        n = readFromFile(inFile, arr);
        if (n <= 0) continue;

        printf("\nBefore Sorting:\n");
        printArray(arr, n);

        comparison_count = 0;
        start = clock();
        mergeSort(arr, 0, n - 1);
        end = clock();

        double elapsed_time = ((double)(end - start) * 1000000000.0) / CLOCKS_PER_SEC;

        writeToFile(outFile, arr, n);

        printf("\nAfter Sorting:\n");
        printArray(arr, n);
        printf("Number of Comparisons: %d\n", comparison_count);
        printf("Execution Time: %.0f nanoseconds\n", elapsed_time);
    }

    return 0;
}
