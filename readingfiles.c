#include <stdio.h>

int main(){
    FILE *fptr;

    fptr = fopen("island_map.txt", "r");

    char test[100];

    while(fgets(test, 100, fptr)){
        printf("%s", test);
    }

    fclose(fptr);
    return 0;
}