#include <stdio.h>

int is_valid_line(char **line, int i) {
    int j = 0;

    while (line[i][j]) {
        if (line[i][j] != '1' && line[i][j] != '0' && line[i][j] != ' ' && line[i][j] != '\t') {
            return 0; // Non-valid character found
        }
        j++;
    }

    return 1; // Valid line
}

int find_first_valid_line(char **lines, int num_lines) {
    for (int i = 0; i < num_lines; i++) {
        if (is_valid_line(lines, i)) {
            return i; // Found the first valid line, return its index
        }
    }
    return -1; // No valid line found
}

int main() {
    char *lines[] = {
        "kdfkk sdfjjsjdf1sdf",
        "1111111111111111111111110111111111111",
        "1111000101111000000000010111100000011111111",
        "111100000000000100000000001011110000001",
        "100001000000000011111110001011110000001"
    };
    int num_lines = 5;

    int first_valid_index = find_first_valid_line(lines, num_lines);

    if (first_valid_index != -1) {
        printf("The first valid line is at index: %d\n", first_valid_index);
    } else {
        printf("No valid line found.\n");
    }

    return 0;
}

