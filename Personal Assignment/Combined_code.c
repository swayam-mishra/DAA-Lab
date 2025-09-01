#include <stdio.h>
#include <stdlib.h>

// Define a maximum size for the matrices to simplify memory management.
// For a real-world application, you might use dynamic memory allocation.
#define MAX_SIZE 10

// --- Function Prototypes ---

// Utility Functions
void getMatrixElements(int matrix[MAX_SIZE][MAX_SIZE], int row, int col);
void displayMatrix(int matrix[MAX_SIZE][MAX_SIZE], int row, int col);

// Core Matrix Operations
void calculateDeterminant();
void multiplyMatrices();
void findElement();
void printSpiral();
void checkTriangular();
void findRank();
void transposeMatrix();

// Helper functions for specific operations
void getCofactor(int mat[MAX_SIZE][MAX_SIZE], int temp[MAX_SIZE][MAX_SIZE], int p, int q, int n);
int determinantOfMatrix(int mat[MAX_SIZE][MAX_SIZE], int n);
void swapRows(int mat[MAX_SIZE][MAX_SIZE], int row1, int row2, int col);
int rankOfMatrix(int mat[MAX_SIZE][MAX_SIZE], int R, int C);


// --- Main Function ---
int main() {
    int choice;

    // The main loop continues until the user chooses to exit.
    while (1) {
        // Display the menu of options to the user.
        printf("\n--- Matrix Operations Menu ---\n");
        printf("1. Determinant of a Matrix\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Find an Element in a Matrix\n");
        printf("4. Print Matrix in Spiral Pattern\n");
        printf("5. Check for Upper/Lower Triangular\n");
        printf("6. Rank of a Matrix\n");
        printf("7. Transpose of a Matrix\n");
        printf("8. Exit\n");
        printf("-----------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // The switch statement directs the program to the chosen function.
        switch (choice) {
            case 1:
                calculateDeterminant();
                break;
            case 2:
                multiplyMatrices();
                break;
            case 3:
                findElement();
                break;
            case 4:
                printSpiral();
                break;
            case 5:
                checkTriangular();
                break;
            case 6:
                findRank();
                break;
            case 7:
                transposeMatrix();
                break;
            case 8:
                printf("Exiting program. Goodbye!\n");
                exit(0); // Successfully exits the program.
            default:
                printf("Invalid choice! Please enter a number between 1 and 8.\n");
        }
    }

    return 0;
}

// --- Utility Function Implementations ---

/**
 * @brief Reads matrix elements from the user.
 * @param matrix The 2D array to store the elements.
 * @param row The number of rows.
 * @param col The number of columns.
 */
void getMatrixElements(int matrix[MAX_SIZE][MAX_SIZE], int row, int col) {
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

/**
 * @brief Displays the matrix in a formatted way.
 * @param matrix The 2D array to display.
 * @param row The number of rows.
 * @param col The number of columns.
 */
void displayMatrix(int matrix[MAX_SIZE][MAX_SIZE], int row, int col) {
    printf("The matrix is:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}


// --- Core Operation Implementations ---

/**
 * 1. DETERMINANT OF A MATRIX
 * This function handles the user interaction for calculating the determinant.
 * It calls the recursive `determinantOfMatrix` function to do the calculation.
 */
void calculateDeterminant() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int n;

    printf("\n--- Calculate Determinant ---\n");
    printf("Enter the order of the square matrix (e.g., 3 for 3x3): ");
    scanf("%d", &n);

    if (n > MAX_SIZE || n <= 0) {
        printf("Matrix size must be between 1 and %d.\n", MAX_SIZE);
        return;
    }

    getMatrixElements(matrix, n, n);
    displayMatrix(matrix, n, n);

    printf("Determinant of the matrix is: %d\n", determinantOfMatrix(matrix, n));
}

// Helper function to get cofactor of mat[p][q] in temp[][]. n is current dimension of mat[][].
void getCofactor(int mat[MAX_SIZE][MAX_SIZE], int temp[MAX_SIZE][MAX_SIZE], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // Copying into temporary matrix only those elements which are not in given row and column
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                // Row is filled, so increase row index and reset col index
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Recursive function for finding determinant of a matrix.
int determinantOfMatrix(int mat[MAX_SIZE][MAX_SIZE], int n) {
    int D = 0; // Initialize result

    // Base case: if matrix contains single element
    if (n == 1)
        return mat[0][0];

    int temp[MAX_SIZE][MAX_SIZE]; // To store cofactors
    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++) {
        // Getting Cofactor of mat[0][f]
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}


/**
 * 2. MATRIX MULTIPLICATION
 * Multiplies two matrices after checking if they are compatible.
 */
void multiplyMatrices() {
    int first[MAX_SIZE][MAX_SIZE], second[MAX_SIZE][MAX_SIZE], result[MAX_SIZE][MAX_SIZE];
    int r1, c1, r2, c2;

    printf("\n--- Matrix Multiplication ---\n");
    printf("Enter rows and columns for the first matrix: ");
    scanf("%d %d", &r1, &c1);
    getMatrixElements(first, r1, c1);

    printf("Enter rows and columns for the second matrix: ");
    scanf("%d %d", &r2, &c2);

    // Check for compatibility: columns of first matrix must equal rows of second matrix.
    if (c1 != r2) {
        printf("Error: Matrices cannot be multiplied. Columns of first matrix must be equal to rows of second.\n");
        return;
    }

    getMatrixElements(second, r2, c2);

    // Initialize result matrix to zero
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
        }
    }

    // Perform multiplication
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }

    printf("Result of multiplication:\n");
    displayMatrix(result, r1, c2);
}


/**
 * 3. FIND AN ELEMENT IN A MATRIX
 * Searches for a given number in the matrix and reports its location(s).
 */
void findElement() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int r, c, element, found = 0;

    printf("\n--- Find Element in Matrix ---\n");
    printf("Enter rows and columns for the matrix: ");
    scanf("%d %d", &r, &c);
    getMatrixElements(matrix, r, c);
    displayMatrix(matrix, r, c);

    printf("Enter the element to find: ");
    scanf("%d", &element);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (matrix[i][j] == element) {
                printf("Element %d found at position [%d][%d]\n", element, i, j);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Element %d not found in the matrix.\n", element);
    }
}


/**
 * 4. PRINT MATRIX IN SPIRAL PATTERN
 * Prints the elements of the matrix in a clockwise spiral order.
 */
void printSpiral() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int r, c;

    printf("\n--- Print Matrix in Spiral Pattern ---\n");
    printf("Enter rows and columns for the matrix: ");
    scanf("%d %d", &r, &c);
    getMatrixElements(matrix, r, c);
    displayMatrix(matrix, r, c);

    printf("Spiral pattern: ");

    int top = 0, bottom = r - 1, left = 0, right = c - 1;
    int dir = 0; // 0: left->right, 1: top->bottom, 2: right->left, 3: bottom->top

    while (top <= bottom && left <= right) {
        if (dir == 0) {
            for (int i = left; i <= right; i++) printf("%d ", matrix[top][i]);
            top++;
        } else if (dir == 1) {
            for (int i = top; i <= bottom; i++) printf("%d ", matrix[i][right]);
            right--;
        } else if (dir == 2) {
            for (int i = right; i >= left; i--) printf("%d ", matrix[bottom][i]);
            bottom--;
        } else if (dir == 3) {
            for (int i = bottom; i >= top; i--) printf("%d ", matrix[i][left]);
            left++;
        }
        dir = (dir + 1) % 4;
    }
    printf("\n");
}


/**
 * 5. CHECK FOR UPPER/LOWER TRIANGULAR
 * Determines if a square matrix is upper triangular, lower triangular, both, or neither.
 */
void checkTriangular() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int n;
    int isUpper = 1, isLower = 1;

    printf("\n--- Check Triangular Matrix ---\n");
    printf("Enter the order of the square matrix: ");
    scanf("%d", &n);

    if (n > MAX_SIZE || n <= 0) {
        printf("Matrix size must be between 1 and %d.\n", MAX_SIZE);
        return;
    }

    getMatrixElements(matrix, n, n);
    displayMatrix(matrix, n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Check for lower triangular: elements above the main diagonal must be zero.
            if (i < j && matrix[i][j] != 0) {
                isLower = 0;
            }
            // Check for upper triangular: elements below the main diagonal must be zero.
            if (i > j && matrix[i][j] != 0) {
                isUpper = 0;
            }
        }
    }

    if (isUpper && isLower) {
        printf("The matrix is a diagonal matrix (both upper and lower triangular).\n");
    } else if (isUpper) {
        printf("The matrix is an upper triangular matrix.\n");
    } else if (isLower) {
        printf("The matrix is a lower triangular matrix.\n");
    } else {
        printf("The matrix is neither upper nor lower triangular.\n");
    }
}


/**
 * 6. RANK OF A MATRIX
 * Calculates the rank by converting the matrix to row echelon form.
 */
void findRank() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int r, c;

    printf("\n--- Find Rank of Matrix ---\n");
    printf("Enter rows and columns for the matrix: ");
    scanf("%d %d", &r, &c);
    getMatrixElements(matrix, r, c);
    displayMatrix(matrix, r, c);

    int rank = rankOfMatrix(matrix, r, c);
    printf("The rank of the matrix is: %d\n", rank);
}

// Helper function to swap two rows of a matrix
void swapRows(int mat[MAX_SIZE][MAX_SIZE], int row1, int row2, int col) {
    for (int i = 0; i < col; i++) {
        int temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}

// Function to find rank of a matrix
int rankOfMatrix(int mat[MAX_SIZE][MAX_SIZE], int R, int C) {
    int rank = C;

    for (int row = 0; row < rank; row++) {
        // If pivot element is zero, find a non-zero element in the same column and swap rows.
        if (mat[row][row] == 0) {
            int reduce = 1;
            for (int i = row + 1; i < R; i++) {
                if (mat[i][row] != 0) {
                    swapRows(mat, row, i, rank);
                    reduce = 0;
                    break;
                }
            }
            if (reduce) {
                rank--;
                for (int i = 0; i < R; i++) {
                    mat[i][row] = mat[i][rank];
                }
            }
            row--;
        } else {
            // Make all elements below the pivot zero.
            for (int i = row + 1; i < R; i++) {
                int mult = mat[i][row];
                int pivot = mat[row][row];
                for (int j = row; j < rank; j++) {
                    mat[i][j] = pivot * mat[i][j] - mult * mat[row][j];
                }
            }
        }
    }
    
    // Count non-zero rows in the echelon form
    int nonZeroRows = 0;
    for (int i = 0; i < R; i++) {
        int isZeroRow = 1;
        for (int j = 0; j < C; j++) {
            if (mat[i][j] != 0) {
                isZeroRow = 0;
                break;
            }
        }
        if (!isZeroRow) {
            nonZeroRows++;
        }
    }
    
    return nonZeroRows;
}


/**
 * 7. TRANSPOSE OF A MATRIX
 * Finds the transpose by swapping rows and columns.
 */
void transposeMatrix() {
    int matrix[MAX_SIZE][MAX_SIZE], transpose[MAX_SIZE][MAX_SIZE];
    int r, c;

    printf("\n--- Transpose of Matrix ---\n");
    printf("Enter rows and columns for the matrix: ");
    scanf("%d %d", &r, &c);
    getMatrixElements(matrix, r, c);
    printf("Original Matrix:\n");
    displayMatrix(matrix, r, c);

    // Finding the transpose
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }

    printf("Transposed Matrix:\n");
    // Note that rows and columns are swapped for display
    displayMatrix(transpose, c, r);
}
