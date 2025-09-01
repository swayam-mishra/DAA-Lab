#include <stdio.h>


int main() {
    int matrix[3][3];
    int element;
    int found = 0; // Flag to check if the element was found

    printf("Find an Element in a 3x3 Matrix\n");
    printf("Enter the 9 elements of the matrix:\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nEnter the element to find: ");
    scanf("%d", &element);

    // Search for the element
    printf("\nSearching for element %d...\n", element);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == element) {
                printf("Element found at position [%d][%d]\n", i, j);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Element %d was not found in the matrix.\n", element);
    }

    return 0;
}
