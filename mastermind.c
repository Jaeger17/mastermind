/**
 * @author Jaeger17 (Jaeger17@protonmail.com)
 * @brief 
 * @date 2021-04-28
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

_Noreturn void guess_console(int *rand_num);  // user guessing console
int arg_check(int argc, char *argv[]);  // command-line argument checker
void game_result(int red, int white, int guess, long *timer); // print results
void calc_avg(int guess, long *timer, double *avg);  // Guess time average
void file_check(int *rand_ptr);  // check for the existence of .mm file
void autoplay(int *rand_ptr); // autoplay the game

// Main function that executes first.
// Takes argc and *argv[] as arguments.
int main(int argc, char *argv[])
{
        arg_check(argc, argv);
        srand(time(NULL));
        int rand_num[4];
        int rand_max = 10;
        int *rand_ptr = rand_num;

        // Loops 4 times assigning a random number between 1-9 to each index in
        // int rand_num[]
        for(int i = 0; i < 4; i++) {
                rand_num[i] = rand() % rand_max;  // Range = [0, 9]
        }
        file_check(rand_ptr);
        if((arg_check(argc, argv)) ==  1)
                autoplay(rand_ptr);
        guess_console(rand_ptr);
}

// Check the command-line arguments. The only valid argument is "autoplay".
// Takes argc and *argv[] as arguments.
int arg_check(int argc, char *argv[])
{
        if(argc == 2 && strcmp(argv[1], "autoplay") == 0) {
                return 1;
        } else if (argc == 1) {
                return 0;
        } else {
                printf("Invalid arguments.\n");
                exit(1);
        }
}

/*
 * Check to see if an answer file exists. If the file exists and the data is.
 * valid, assign file number to the game's random number using pointers.
 * int *rand_ptr - the random number integer pointer.
 */
void file_check(int *rand_ptr) {
       FILE *fp;
       int *tmp = rand_ptr;  // temp pointer to rand_num
       char line[MAX];
       if ((fp = fopen(".mm", "r")) != NULL) {
               fgets(line, sizeof(line), fp);
               if ((strlen(line)) != 4) {
                       puts("Invalid file input");
                       exit(1);
               }
               for (int i = 0; i < 4; i++) {
                       if(isdigit(line[i]) == 0) {
                               puts("Invalid file input");
                               exit(1);
                       }
               }
               for (int i = 0; i < 4; i++) {
                       *tmp = line[i] - '0';
                       tmp++;
               }
               fclose(fp);
       }
}

// Initiate the guessing console. Loops until game is won.
// int *rand_ptr - the random number integer pointer.
_Noreturn void guess_console(int *rand_ptr)
{
       time_t start;
       time_t end;
       time_t diff;
       char line[MAX];
       char rand_line[MAX];
       long times[100];
       int red, white;
       int guess = 0;
       char consumed_listr[5] = "xxxx";
       char consumed_listw[5] = "xxxx";
       long *timer = times;

       for(int i = 0; i < 4; i++) {
               rand_line[i] = *rand_ptr + '0';
               rand_ptr++;
       }
       while(true) {
               red = 0;
               white = 0;

               start = time(&start);
               printf("Guess a number: ");

               fgets(line, sizeof(line), stdin);

               if((strlen(line)) != 5) {
                       puts("Invalid guess");
                       continue;
               }
               if(! strtol(line, NULL, 10) && !(strcmp(line, "0000"))) {
                       puts("Invalid guess");
                       continue;
               }
               for(int i = 0; i < 4; i++) {
                       if(line[i] == rand_line[i]) {
                               consumed_listr[i] = line[i];
                               red++;
                       }
               }
               for(int i = 0; i < 4; i++) {
                       if((line[i] != rand_line[i]) &&
                                        !(strchr(consumed_listr, line[i])) &&
                                        (strchr(rand_line, line[i])) &&
                                        !(strchr(consumed_listw, line[i]))){
                               consumed_listw[i] = line[i];
                               white++;
                       }
               }

               // resets the consumed variable each loop
               for(int i = 0; i < 4; i++) {
                       consumed_listr[i] = 'x';
                       consumed_listw[i] = 'x';
               }
               guess++;
               end = time(&end);
               diff = end - start;
               *timer = diff;
               timer++;
               game_result(red, white, guess, timer);
       }
}

/*
 * Print the ongoing or completed game results to the screen.
 * int red - number of correct digits in the correct index.
 * int white - number of correct digits in the incorrect index.
 * int guess - number of valid guesses.
 * long *timer - a pointer to an array of stored guess times.
 */
void game_result(int red, int white, int guess, long *timer)
{
       double avg;
       double *avg_ptr = &avg;
       calc_avg(guess, timer, &avg);
       if(red == 4) {
               printf("\n%d red\nYou win! it took %d guess(es)\n"
                      "Average valid guess took: %.2fs\n"
                      ,red, guess, *avg_ptr);
               exit(0);
       } else if(white > 0 && red > 0) {
               printf("%d red, %d white\n", red, white);
       } else if(white > 0) {
               printf("%d white\n", white);
       } else if(red > 0){
               printf("%d red\n", red);
       } else{
               puts("No matches\n");
       }
}

/*
 * Calculate the average guess time and add to the times[] array
 * int guess - number of valid guesses.
 * long *timer - a pointer to an array of stored guess times.
 * double *avg - a pointer to the avg double
 */
void calc_avg(int guess, long *timer, double *avg)
{
       int sum = 0;
       int i = 0;

       for(; i < guess; ++i) {
               sum += *--timer;
       }
       *avg = (double)sum / guess;
}

// Play the game automatically with another random int array. Guess until win
// int *rand_ptr - the random number integer pointer.
void autoplay(int *rand_ptr) {
        int rand_max = 10;
        int comp_guess[4];
        int score, guess;
        guess = 0;

        puts("");
        while (1) {
                // temporary pointer to avoid direct incrementing of rand_ptr
                int *tmp = rand_ptr;
                score = 0;
                for (int i = 0; i < 4; i++) {
                        comp_guess[i] = rand() % rand_max;  // Range = [0, 9]
                        printf("%d", comp_guess[i]);
                }
                for (int i = 0; i < 4; i++) {
                        if (comp_guess[i] == *tmp) {
                                tmp++;
                                score++;
                        }
                }
                guess++;
                puts("");
                if(score == 4) {
                        printf("Computer wins in %d Guesses!\n", guess);
                        exit(0);
                }
        }
}