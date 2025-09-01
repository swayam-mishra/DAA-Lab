#include <stdio.h>

int main() {
    int n;
    printf("Enter size of square matrix (n x n): ");
    scanf("%d", &n);

    int matrix[n][n];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int upper = 1, lower = 1; 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j && matrix[i][j] != 0) {
                // elements below diagonal should be 0 for upper triangular
                upper = 0;
            }
            if (i < j && matrix[i][j] != 0) {
                // elements above diagonal should be 0 for lower triangular
                lower = 0;
            }
        }
    }

    if (upper)
        printf("The matrix is Upper Triangular.\n");
    else if (lower)
        printf("The matrix is Lower Triangular.\n");
    else
        printf("The matrix is Neither Upper nor Lower Triangular.\n");

    return 0;
}
