#include <stdio.h>
#include <string.h>

int main() {
    char sentence[] = "Hello, World!";
    char *token;

    // Tokenize the string using strtok()
    token = strtok(sentence, " ");

    // Process each token
    while (token != NULL) {
        // Print each character of the token
        for (int i = 0; token[i] != '\0'; i++) {
            printf("%c\n", token[i]);
        }
        // Get the next token
        token = strtok(NULL, " ");
    }

    return 0;
}