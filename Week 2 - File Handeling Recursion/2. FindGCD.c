// Name : Swayam Mishra
// Roll No. : 23052120

#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    char *source_filename = argv[1];
    char *dest_filename = argv[2];

    FILE *input_file = fopen(source_filename, "r");
    if (input_file == NULL) {
        printf("Error: Could not open source file '%s'\n", source_filename);
        return 1;
    }

    FILE *output_file = fopen(dest_filename, "w");
    if (output_file == NULL) {
        printf("Error: Could not open destination file '%s'\n", dest_filename);
        fclose(input_file);
        return 1;
    }

    int num1, num2;

    while (fscanf(input_file, "%d %d", &num1, &num2) == 2) {
        fprintf(output_file, "The GCD of %d and %d is %d.\n", num1, num2, gcd(num1, num2));
    }

    printf("GCD calculation complete. Check the file '%s'.\n", dest_filename);

    fclose(input_file);
    fclose(output_file);

    return 0;
}