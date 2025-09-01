#include <stdio.h>

#define MAX 10  

// Function to swap two rows
void swapRows(float mat[MAX][MAX], int row1, int row2, int col) {
    for (int i = 0; i < col; i++) {
        float temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}

// Function to find rank
int matrixRank(float mat[MAX][MAX], int row, int col) {
    int rank = col;

    for (int r = 0; r < rank; r++) {
        // If diagonal element is not zero, make others zero
        if (mat[r][r]) {
            for (int i = 0; i < row; i++) {
                if (i != r) {
                    float ratio = mat[i][r] / mat[r][r];
                    for (int j = 0; j < rank; j++)
                        mat[i][j] -= ratio * mat[r][j];
                }
            }
        } else {
            // Find non-zero element in same column
            int reduce = 1;
            for (int i = r + 1; i < row; i++) {
                if (mat[i][r]) {
                    swapRows(mat, r, i, col);
                    reduce = 0;
                    break;
                }
            }
            if (reduce) {
                rank--;
                for (int i = 0; i < row; i++)
                    mat[i][r] = mat[i][rank];
            }
            r--;
        }
    }
    return rank;
}

int main() {
    int row, col;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &row, &col);

    float mat[MAX][MAX];
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            scanf("%f", &mat[i][j]);

    int rank = matrixRank(mat, row, col);
    printf("The Rank of the Matrix is: %d\n", rank);

    return 0;
}
