#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double map_prob(int position[2], char map[9][9], double *avg_steps, double *success_perc, double *std_dev){
    srand(123456);
    int moves[8][2] = {{-1,0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; //moves go clockwise from north round to north west
    int total_steps = 0;
    int successful_runs = 0.0;
    int run_steps[1000]; //this will be used to calculate standard deviation

    for(int i = 0; i < 1000; i++){ //1000 random paths

        int current_position[2] = {position[0], position[1]}; //the start of the path
        
        for(int steps = 0; steps < 10; steps++){ //10 steps, with the 11th loop for the case where it ran out of steps

            char current_letter = map[current_position[0]][current_position[1]];

            if(current_letter != 'L' || steps == 9){ //if one of these is satisfied, the run has ended
                if(current_letter == 'B'){ //if it ends successfully
                    run_steps[successful_runs] = steps;
                    successful_runs += 1;
                    total_steps += steps;
                }
                break; //drop out of the 10 step for loop and start next run
            }
            int move_val = rand() % 8; //if the run has not ended, make the next random move
            int move[2] = {moves[move_val][0], moves[move_val][1]};
            current_position[0] = current_position[0] + move[0];
            current_position[1] = current_position[1] + move[1];
        }
        
    }
    if(successful_runs != 0){
        *avg_steps = total_steps/(successful_runs*1.0);
        double tot = 0.0;
        for(int i = 0; i < successful_runs; i++){
            double temp = run_steps[i] - *avg_steps;
            temp *= temp;
            tot += temp;
        }

        tot = tot/(successful_runs-1);
        *std_dev = sqrt(tot);
    }
    else{
        *avg_steps = 0;
        *std_dev = 0;
    }
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

        while(fgets(line, 30, fptr) != NULL && j <= 9){ //if fgets is NULL, the end of the file has been reached. j should equal 8 when this while loop finishes

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

                if(token[0] != 'B' && token[0] != 'W' && token[0] != 'L' && token[0] != 'D' && token[0] != 'V'){
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
            if (j == 8){
                printf("%c", map[i][j]);
                continue;
            }
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n");

    double perc[9][9];
    double steps_avg[9][9];
    double standard_deviation[9][9];
    int position[2];

    for(int i = 0; i < 9; i++){ //calculating percentage success, average steps, and standard deviation
        for(int j = 0; j < 9; j++){
            position[0] = i;
            position[1] = j;
            double percentage, average_steps, stand_dev;
            map_prob(position, map, &average_steps, &percentage, &stand_dev); //for each location in the map, calculate 1000 random walks
            perc[i][j] = percentage;
            steps_avg[i][j] = average_steps;
            standard_deviation[i][j] = stand_dev;
        }
    }

    printf("Probability of escape:\n");
    for(int i = 0; i < 9; i++){ //displaying the percentage map
        for(int j = 0; j < 9; j++){
            if (j == 8){
                printf("%5.2lf", perc[i][j]);
                continue;
            }
            printf("%5.2lf ", perc[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Mean path length:\n");
    for(int i = 0; i < 9; i++){ //displaying the average step map
        for(int j = 0; j < 9; j++){
            if (j == 8){
                printf("%5.2lf", steps_avg[i][j]);
                continue;
            }
            printf("%5.2lf ", steps_avg[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Standard deviation of path length:\n");
    for(int i = 0; i < 9; i++){ //displaying the standard div map
        for(int j = 0; j < 9; j++){
            if (j == 8){
                printf("%5.2lf", standard_deviation[i][j]);
                continue;
            }
            printf("%5.2lf ", standard_deviation[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}