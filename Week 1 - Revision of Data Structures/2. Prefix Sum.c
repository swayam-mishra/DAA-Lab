// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>

int main() {
	int size;
	printf("Enter size of the array: ");
	scanf("%d", &size);

	int array[size];
	int prefixSum[size];
	printf("Enter %d elements into the array: ", size);
	for(int i = 0; i < size; i++){
		scanf("%d", &array[i]);
		if (i == 0)
			prefixSum[i] = array[i];
		else
			prefixSum[i] = prefixSum[i-1] + array[i];
	}

	printf("Prefix Sum array: ");
	for(int i = 0; i < size; i++)
		printf("%d ", prefixSum[i]);
	printf("\n");

	return 0;
}
