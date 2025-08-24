// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void findPairs_nlogn(int arr[], int n, int sum) {
    printf("\n--- O(n log n) Method (Sorting + Two Pointers) ---\n");
    
    qsort(arr, n, sizeof(int), compare);

    int left = 0;
    int right = n - 1;

    while (left < right) {
        if (arr[left] + arr[right] == sum) {
            printf("Pair found: (%d, %d)\n", arr[left], arr[right]);
            left++;
            right--;
        } else if (arr[left] + arr[right] < sum) {
            left++;
        } else {
            right--;
        }
    }
}

void findPairs_n(int arr[], int n, int sum) {
    printf("\n--- O(n) Method (Hashing) ---\n");

    int max_val = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int *hash = (int*)calloc(max_val + 1, sizeof(int));
    if (hash == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        int complement = sum - arr[i];

        if (complement >= 0 && hash[complement]) {
            printf("Pair found: (%d, %d)\n", arr[i], complement);
        }
        
        hash[arr[i]] = 1;
    }
    
    free(hash);
}


int main() {
    int arr[] = {1, 4, 45, 6, 10, 8, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 16;

    printf("Array: ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\nGiven sum: %d\n", sum);

    findPairs_nlogn(arr, n, sum);

    int arr2[] = {1, 4, 45, 6, 10, 8, 12}; 
    findPairs_n(arr2, n, sum);

    return 0;
}