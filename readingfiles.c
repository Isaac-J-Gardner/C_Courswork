#include <stdio.h>

int main(){
    FILE *fptr;

    fptr = fopen("island_map.txt", "r");

    char test[100];

    if(fptr != NULL){
        while(fgets(test, 100, fptr)){
            printf("%s", test);
        }
    }
    else{
        printf("unable to locate or open file");
    }

    fclose(fptr);
    return 0;
}