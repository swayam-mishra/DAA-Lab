// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>

void excahnge(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void rotate_right(int *p1, int p2) {
    if (p2 < 2) {
        return;
    }

    for (int i = p2 - 1; i > 0; i--) {
        excahnge(&p1[i], &p1[i-1]);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    int N = 9; 
    int elements_to_rotate = 5;

    printf("Before ROTATE:\t");
    printArray(A, N);

    rotate_right(A, elements_to_rotate);

    printf("After  ROTATE:\t");
    printArray(A, N);

    return 0;
}