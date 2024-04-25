#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
double map_calc(int position[2], char map[9][9], double *avg_steps, double *success_perc, double *std_dev){
    int moves[8][2] = {{-1,0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; //moves go clockwise from north round to north west
    int total_steps = 0;
    int successful_runs = 0.0;
    int run_steps[1000]; //this will be used to calculate standard deviation, 
                         //since we cant know the mean until after all the runs, i have to store all individual runs
                         //then use that to calculate S.D later
    for(int i = 0; i < 1000; i++){ //1000 random paths
        int current_position[2] = {position[0], position[1]}; //the start of the path
        for(int steps = 0; steps <= 10; steps++){ //10 steps, with the 11th loop for the case where it ran out of steps
            char current_letter = map[current_position[0]][current_position[1]];
            if(current_letter != 'L' || steps == 10){ //if one of these is satisfied, the run has ended
                if(current_letter == 'B'){ //if it ends successfully
                    run_steps[successful_runs] = steps;
                    successful_runs += 1;
                    total_steps += steps;
                }
                break; //drop out of the 10 step for loop and start next run
            }
            int move_val = rand() % 8; //if the run has not ended, make the next random move
            int move[2] = {moves[move_val][0], moves[move_val][1]};
            int next_postion[2] = {current_position[0] + move[0], current_position[1] + move[1]};
            if(!(next_postion[0] > 8) && !(next_postion[0] < 0)){
                current_position[0] = next_postion[0];
            }
            if(!(next_postion[1] > 8) && !(next_postion[1] < 0)){ //if the next move doesn't take the player off the map
                current_position[1] = next_postion[1];
            }
        }
    }
    if(successful_runs != 0){ //calculating average steps and standard deviation
        *avg_steps = total_steps/(successful_runs*1.0);
        double tot = 0.0;
        for(int i = 0; i < successful_runs; i++){ //for each successful run that was recorded
            double temp = run_steps[i] - *avg_steps; //steps - mean
            temp *= temp; //square the result
            tot += temp; //sum of the squares
        }
        tot = tot/(successful_runs); //divide by n
        *std_dev = sqrt(tot); //square root
    }
    else{
        *avg_steps = 0; //if successful runs was equal to 0, these will be as well
        *std_dev = 0;
    }
    *success_perc = successful_runs/10.0; //divide by 1000, times by 100
    return 0;
}
int main(){
    srand(123456);
    char map[9][9]; //this will hold the 9x9 grid of characters read from the .txt file
    FILE *fptr; 
    fptr = fopen("island_map.txt", "r");
    char temp;
    if(fptr != NULL){ //if the file could be found/opened
        for (int row = 0; row < 9; row++){
            for (int col = 0; col < 9; col++){
                fscanf(fptr, "%c ", &temp);
                if(temp != 'B' && temp != 'L' && temp != 'V' && temp != 'D' && temp != 'W'){
                    printf("Error!");
                    return 1;
                }
                map[row][col] = temp;
            }
        }
        if(fscanf(fptr, "%c ", &temp) != EOF){
            printf("Error!");
            return 1;
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
            map_calc(position, map, &average_steps, &percentage, &stand_dev); //for each location in the map, calculate 1000 random walks
            perc[i][j] = percentage;
            steps_avg[i][j] = average_steps;
            standard_deviation[i][j] = stand_dev;
        }
    }
    
    printf("Probability of escape:\n");
    for(int i = 0; i < 9; i++){ //displaying the percentage map
        for(int j = 0; j < 9; j++){
            if (j == 8){
                printf("%7.2lf", perc[i][j]);
                continue;
            }
            printf("%7.2lf ", perc[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Mean path length:\n");
    for(int i = 0; i < 9; i++){ //displaying the average step map
        for(int j = 0; j < 9; j++){
            if (j == 8){
                printf("%4.2lf", steps_avg[i][j]);
                continue;
            }
            printf("%4.2lf ", steps_avg[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Standard deviation of path length:\n");
    for(int i = 0; i < 9; i++){ //displaying the standard div map
        for(int j = 0; j < 9; j++){
            if (j == 8){
                printf("%4.2lf", standard_deviation[i][j]);
                continue;
            }
            printf("%4.2lf ", standard_deviation[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}