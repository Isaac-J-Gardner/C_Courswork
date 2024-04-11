#include <stdio.h>
#include <string.h>

int main() {
    char test[100];
    FILE *fptr;

    fptr = fopen("island_map.txt", "r");

    if (fptr != NULL){
        fgets(test, 100, fptr);
    }
    else{
        printf("could not retrieve file");
    }

    printf("%zu", strlen(test));

    fclose(fptr);

    return 0;
}