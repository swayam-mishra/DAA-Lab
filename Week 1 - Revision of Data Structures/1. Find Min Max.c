// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>

int main(int argv, char *argc[]) {
	FILE *input_file;
	int num, max, min;

	if (argv < 2) {
		printf("Usage: %s <filename>\n", argc[0]);
		return 1;
	}

	input_file = fopen(argc[1], "r");
    if (input_file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

	if (fscanf(input_file, "%d", &num) == 1) {
        min = num;
        max = num;
    } else {
        printf("File is empty or contains no integers.\n");
        fclose(input_file);
        return 1;
    }

	while(fscanf(input_file, "%d", &num) == 1) {
		if (min > num)
			min = num;
		if (max < num)
			max = num;
	}

	printf("%d,%d\n", min, max);
	
	fclose(input_file);

	return 0;
}
