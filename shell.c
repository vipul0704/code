#include <stdio.h>
int main(int argc, char *argv[]) {
    // Check if there are at least two command line arguments (including the program name)
    if (argc < 2) {
        printf("Usage: %s <arg1> <arg2> ... <argN>\n", argv[0]);
        return 1; // Exit with an error code
    }
    // Display the command line arguments
    printf("Number of arguments: %d\n", argc - 1);

    printf("Arguments:\n");
    for (int i = 1; i < argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }
    return 0; // Exit successfully
}