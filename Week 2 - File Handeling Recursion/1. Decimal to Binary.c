// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>
#include <stdlib.h>

void printBinary(FILE *output_file, int n) {
    if (n > 1) {
        printBinary(output_file, n / 2);
    }
    fprintf(output_file, "%d", n % 2);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); 
    char *source_filename = argv[2];
    char *dest_filename = argv[3];

    FILE* input_file = fopen(source_filename, "r");
    if (input_file == NULL) {
        printf("Error: Could not open source file '%s'\n", source_filename);
        return 1;
    }

    FILE* output_file = fopen(dest_filename, "w");
    if (output_file == NULL) {
        printf("Error: Could not open destination file '%s'\n", dest_filename);
        fclose(input_file);
        return 1;
    }

    int number;

    for (int i = 0; i < n && fscanf(input_file, "%d", &number) == 1; i++) {
        fprintf(output_file, "The binary equivalent of %d is ", number);
        printBinary(output_file, number);
        fprintf(output_file, "\n");
    }

    printf("Conversion complete. Check the file '%s'.\n", dest_filename);

    fclose(input_file);
    fclose(output_file);

    return 0;
}