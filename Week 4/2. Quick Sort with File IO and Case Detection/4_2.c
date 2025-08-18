#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for access()

#define MAX 1000

int comparison_count = 0;
int worst_case_flag = 0;

// Swap utility
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function (Lomuto)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparison_count++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    // Detect worst-case (all elements go to one side)
    int left_size = (i + 1) - low;
    int right_size = high - (i + 1);
    if (left_size == 0 || right_size == 0) {
        worst_case_flag = 1;
    }

    return i + 1;
}

// Quick Sort recursive
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

// Create file with sample data
void createSampleFile(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot create file %s\n", filename);
        return;
    }
    for (int i = 0; i < n; i++)
        fprintf(file, "%d ", arr[i]);
    fclose(file);
    printf("File '%s' created with sample data.\n", filename);
}

// Read array from file
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

// Write array to file
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

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int choice;
    char inFile[20], outFile[25];
    int arr[MAX];
    int n;

    while (1) {
        printf("\nMAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        int sample[10] = {0}; // will fill according to choice

        switch (choice) {
            case 1:
                strcpy(inFile, "inAsce.dat");
                strcpy(outFile, "outQuickAsce.dat");
                for (int i = 0; i < 10; i++) sample[i] = i + 1;
                break;
            case 2:
                strcpy(inFile, "inDesc.dat");
                strcpy(outFile, "outQuickDesc.dat");
                for (int i = 0; i < 10; i++) sample[i] = 10 - i;
                break;
            case 3:
                strcpy(inFile, "inRand.dat");
                strcpy(outFile, "outQuickRand.dat");
                {
                    int temp[10] = {7, 2, 9, 1, 6, 8, 3, 4, 10, 5};
                    memcpy(sample, temp, sizeof(temp));
                }
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                continue;
        }

        // If file doesn't exist, create it with sample data
        if (access(inFile, F_OK) != 0) {
            createSampleFile(inFile, sample, 10);
        }

        n = readFromFile(inFile, arr);
        if (n <= 0) continue;

        printf("\nBefore Sorting:\n");
        printArray(arr, n);

        comparison_count = 0;
        worst_case_flag = 0;

        quickSort(arr, 0, n - 1);

        writeToFile(outFile, arr, n);

        printf("\nAfter Sorting:\n");
        printArray(arr, n);
        printf("Number of Comparisons: %d\n", comparison_count);

        if (worst_case_flag)
            printf("Scenario: Worst-case partitioning\n");
        else
            printf("Scenario: Best-case or Balanced partitioning\n");
    }

    return 0;
}
