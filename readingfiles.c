#include <stdio.h>
#include <string.h>

int main(){
    char map[9][9];
    char *token;
    char test[100];
    size_t length = 19;
    FILE *fptr;

    fptr = fopen("island_map.txt", "r");

    if(fptr != NULL){
        int j = 0;
        while(fgets(test, 100, fptr) && j < 9){
            if(strlen(test) < length){
                continue;
            }
            token = strtok(test, " ");

            int i = 0;
            while (token != NULL && i < 9) {
                map[j][i] = token[0];
                token = strtok(NULL, " "); // Get the next token
                i++;
            }
            j++;
        }
    }
    else{
        printf("unable to locate or open file");
    }

    fclose(fptr);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}