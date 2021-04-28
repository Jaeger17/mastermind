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
 * @param red (int): Red score.
 * @param white (int): White score.
 * @param guess (int): Number of guesses.
 * @param timer (long): Number of seconds for a guess.
 */ 
void game_result(int red, int white, int guess, long *timer);

/**
 * @brief Calculate guessing time average.
 * 
 * @param guess (int): Number of guesses.
 * @param timer (long *): Pointer to array of times.
 * @param avg (double *): Pointer to Average time.
 */
void calc_avg(int guess, long *timer, double *avg);

/**
 * @brief Chekck to see if answer file exits and validate data.
 * 
 * @param rand_ptr (int *): Pointer to random number integer.
 */
void file_check(int *rand_ptr);

/**
 * @brief Autoplay option feature. Plays the game automatically CPU vs. CPU.
 * 
 * @param rand_ptr (int *): Pointer to random number integer.
 */
void autoplay(int *rand_ptr);
