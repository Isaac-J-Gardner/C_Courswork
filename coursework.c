#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double map_prob(int position[2], char map[9][9], double *avg_steps, double *success_perc){
    srand(144);
    int moves[8][2] = {{1,0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    int total_steps = 0;
    int successful_runs = 0;

    for(int i = 0; i < 1000; i++){

        int current_position[2] = {position[0], position[1]};
        
        for(int steps = 0; steps <= 10; steps++){
            char current_letter = map[current_position[0]][current_position[1]];
            if(current_letter == 'B'){
                successful_runs += 1;
                total_steps += steps;
                break;
            }
            else if(current_letter != 'L'){
                total_steps += steps;
                break;
            }
            else if(steps == 10){
                total_steps += steps;
                break;
            }
            int move_val = rand() % 8;
            int move[2] = {moves[move_val][0], moves[move_val][1]};
            int temp1 = current_position[0] + move[0];
            int temp2 = current_position[1] + move[1];
            current_position[0] = temp1;
            current_position[1] = temp2;
        }
        
    }
    *avg_steps = total_steps/1000.0;
    *success_perc = successful_runs/10.0;
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

            if(j < 8 && line_length != 18){ //if it isn't the last line, it should have a length of 20
                printf("Error.");
                return 1;
            }

            if(j == 8 && line_length != 17){ //the last line should have a length of 19 as it doesn't end with "\n"
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
                    if(token[1] != '\n'){
                        printf("Error.");
                        return 1;
                    }
                    
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

    printf("\n\n\n");

    double perc[9][9];
    double steps_avg[9][9];
    int position[2];

    for(int i = 0; i < 9; i++){ //displaying the map
        for(int j = 0; j < 9; j++){
            position[0] = i;
            position[1] = j;
            double percentage, average_steps;
            map_prob(position, map, &percentage, &average_steps);
            perc[i][j] = percentage;
            steps_avg[i][j] = average_steps;
        }
    }

    for(int i = 0; i < 9; i++){ //displaying the map
        for(int j = 0; j < 9; j++){
            printf("%7.2lf ", perc[i][j]);
        }
        printf("\n\n");
    }
    printf("\n\n\n");

    for(int i = 0; i < 9; i++){ //displaying the map
        for(int j = 0; j < 9; j++){
            printf("%7.2lf ", steps_avg[i][j]);
        }
        printf("\n\n");
    }
    printf("\n\n\n");

    return 0;
}