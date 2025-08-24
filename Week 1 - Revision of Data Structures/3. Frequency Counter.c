// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>

int duplicateElements(int arr[], int n) {
	int count = 0;
	for(int i = 0; i < n; ++i) {
		int dup = 0;
		for(int j = 0; j < i; ++j)
			if(arr[i] == arr[j])
				dup = 1;
		if(dup) continue;
		int freq = 0;
		for(int k = i + 1; k < n; ++k)
			if(arr[i] == arr[k])
				++freq;
		if(freq > 0)
			++count;
	}
	return count;
}

int getMaxRepeatingElement(int A[], int n){
	int max_count = 0, max_element = A[0];
	for(int i = 0; i < n; ++i) {
		int count = 1;
		for(int j = i + 1; j < n; ++j)
			if(A[i] == A[j])
				++count;
		if(count > max_count) {
			max_count = count;
			max_element = A[i];
		}
	}
	return max_element;
}

int main(int argv, char *argc[]) {
	if(argv == 1) {
		printf("File path not provided\n");
		return 1;
	}

	FILE *input_file;
	input_file = fopen(argc[1], "r");

	int read_size;
	printf("How many numbers do you want to read from the file: ");
	scanf("%d", &read_size);
	int array[read_size], num;

	for(int i = 0; i < read_size && fscanf(input_file, "%d", &num); ++i)
		array[i] = num;
	fclose(input_file);

	printf("No. of Duplicate elements: %d\n", duplicateElements(array, read_size));
	printf("Most repeating element in array; %d\n", getMaxRepeatingElement(array, read_size));


	return 0;
}