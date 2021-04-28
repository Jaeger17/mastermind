/**
 * @file mastermind.h
 * @author Jaeger17 (jaeger17@protonmail.com)
 * @date 2021-04-28
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

/**
 * @brief User guessing console.
 * 
 * @param rand_num (int *): Pointer to an array of 4 random numbers.
 */
void guess_console(int *rand_num);

/**
 * @brief Check command-line arguments. The only valid argument is "autoplay".
 * 
 * @param argc (int): Number of command-line arguments.
 * @param argv (char *): Array of command-line arguments.
 * @return (int): Status code. 0 for default execution, 1 for autoplay.  
 */
int arg_check(int argc, char *argv[]);

/**
 * @brief Print the ongoing or finished game results to the terminal.
 * 
 * @param red (int): Number
 * @param white 
 * @param guess 
 * @param timer 
 */
void game_result(int red, int white, int guess, long *timer); // print results
void calc_avg(int guess, long *timer, double *avg);  // Guess time average
void file_check(int *rand_ptr);  // check for the existence of .mm file
void autoplay(int *rand_ptr); // autoplay the game
