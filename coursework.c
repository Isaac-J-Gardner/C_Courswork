#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int map_prob(int position[2], char map[9][9]){
    srand(144);
    int moves[8][2] = {{1,0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    int total_steps = 0;
    int successful_runs = 0;
    for(int i = 0; i < 1000; i++){
        int current_position[2] = position;
        for(int steps = 0; steps <= 10; steps++){
            if(map[current_position[1]][current_position[0]] == "B"){
                printf("run %d succeeded with: %d steps", i, steps);
                successful_runs += 1;
                total_steps += steps;
                break;
            }
            else if(map[current_position[1]][current_position[0]] != "L"){
                printf("run %d failed with: %d steps", i, steps);
                total_steps += steps;
                break;
            }
            else if(steps == 10){
                printf("run %d failed by exceeding the step limit", i);
                total_steps += steps;
                break;
            }
            int move[2] = moves[rand() % 8];

        }
        
    }
    return 0;
}

int main(){
    char map[9][9]; //this will hold the 9x9 grid of characters read from the .txt file

    FILE *fptr; 

    fptr = fopen("island_map.txt", "r");

    if(fptr != NULL){ //if the file could be found/opened

        int j = 0; //used in the while loop, j is increased by 1 when a full line has successfully been added to the map

        char *token; //used by strtok. it will point to the location in a string where a given character appears
        char line[30]; //string that holds the line that has been read from the text file

        while(fgets(line, 100, fptr) != NULL && j <= 9){ //if fgets is NULL, the end of the file has been reached. j should equal 8 when this while loop finishes

            size_t line_length = strlen(line);

            if(line_length == 1){continue;} //if its one of the blank lines, we dont need to read anything or do any checks

            if(j < 8 && line_length != 20){ //if it isn't the last line, it should have a length of 20
                printf("Error.");
                return 1;
            }

            if(j == 8 && line_length != 19){ //the last line should have a length of 19 as it doesn't end with "\n"
                printf("Error.");
                return 1;
            }

            if(j > 8){ //if fgets() is not NULL and returns something when j is greater than 8, it has extra lines and so not correctly formatted
                printf("Error.");
                return 1;
            }

            token = strtok(line, " "); //token points to an array containing the 

            int i = 0;

            while (token != NULL && i < 9) {

                if(strlen(token) != 1){ //we should only be getting 1 character, if there is more than 1, its not formatted correctly
                    printf("Error.");
                    return 1;
                }

                map[j][i] = token[0]; //add to map and get next token
                token = strtok(NULL, " ");

                i++;
            }

            j++;
        }
    }
    else{ //if fptr is NULL, the file could not be found/opened
        printf("unable to locate or open file");
    }

    fclose(fptr);

    for(int i = 0; i < 9; i++){ //displaying the map
        for(int j = 0; j < 9; j++){
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}