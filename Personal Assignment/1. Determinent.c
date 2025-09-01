#include <stdio.h>

int main() {
    int matrix[3][3];
    int determinant;

    printf("Calculate Determinant of a 3x3 Matrix \n");
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

    // Formula: a(ei - fh) - b(di - fg) + c(dh - eg)
    int a = matrix[0][0], b = matrix[0][1], c = matrix[0][2];
    int d = matrix[1][0], e = matrix[1][1], f = matrix[1][2];
    int g = matrix[2][0], h = matrix[2][1], i = matrix[2][2];

    determinant = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);

    printf("\nDeterminant of the matrix is: %d\n", determinant);

    return 0;
}
