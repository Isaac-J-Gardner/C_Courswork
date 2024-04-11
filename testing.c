#include <stdio.h>
#include <string.h>

int main() {
    char string[] = "Hello World";
    char *token;

    // Tokenize the string using strtok()
    token = strtok(string, " ");

    // Print the first token
    if (token != NULL) {
        printf("First token: %s\n", token);
    } else {
        printf("No token found.\n");
    }

    return 0;
}
