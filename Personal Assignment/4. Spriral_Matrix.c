#include <stdio.h>


int main() {
    int matrix[3][3];

    printf("Print 3x3 Matrix in Spiral Pattern \n");
    printf("Enter the 9 elements of the matrix:\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nThe matrix you entered is:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    // Print in spiral form (hardcoded for 3x3)
    printf("\nSpiral pattern: ");
    // Top row
    printf("%d %d %d ", matrix[0][0], matrix[0][1], matrix[0][2]);
    // Right column
    printf("%d ", matrix[1][2]);
    // Bottom row
    printf("%d %d %d ", matrix[2][2], matrix[2][1], matrix[2][0]);
    // Left column
    printf("%d ", matrix[1][0]);
    // Center element
    printf("%d\n", matrix[1][1]);

    return 0;
}
