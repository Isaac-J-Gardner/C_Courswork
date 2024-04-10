#include <stdio.h>
#include <string.h>

int main(){
    char map[9][9];
    char *token;
    char test[100];
    FILE *fptr;

    fptr = fopen("island_map.txt", "r");

    if(fptr != NULL){
        int j = 0;
        while(fgets(test, 100, fptr)){
            printf("%s", test);
            token = strtok(test, " ");

            int i = 0;
            while (token != NULL) {
                printf("%s", token);
                token = strtok(NULL, " "); // Get the next token
                i++;
            }
            j++;
            printf("\n");
        }
    }
    else{
        printf("unable to locate or open file");
    }

    fclose(fptr);

    return 0;
}