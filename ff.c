#include <stdio.h>

int main(int argc, char *argv[]) {
    // Check if a filename is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file for reading
    FILE *file = fopen(argv[1], "r");

    // Check if the file is opened successfully
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Read and print each character in the file along with its ASCII code
    int character;
    while ((character = fgetc(file)) != EOF) {
        printf("Character: %c\tASCII Code: %d\n", character, character);
    }

    // Close the file
    fclose(file);

    return 0;
}

