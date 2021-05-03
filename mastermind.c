/**
 * @author Jaeger17 (Jaeger17@protonmail.com)
 * @brief
 * @date 2021-04-28
 */

#include "mastermind.h"

int main(int argc, char *argv[])
{
        arg_check(argc, argv);
        srand(time(NULL));
        int rand_num[4];
        int rand_max = 10;
        int *rand_ptr = rand_num;

        for(int i = 0; i < 4; i++) {
                rand_num[i] = rand() % rand_max;  // Range = [0, 9]
        }

        file_check(rand_ptr);

        if((arg_check(argc, argv)) ==  1)
                autoplay(rand_ptr);
        guess_console(rand_ptr);
}

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

void file_check(int *rand_ptr) {
       FILE *fp;
       int *tmp = rand_ptr;
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

void guess_console(int *rand_ptr)
{
       time_t start;
       time_t end;
       time_t diff;
       char line[MAX] = {0};
       char rand_line[MAX]= {0};
       long times[100] = {0};
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

void calc_avg(int guess, long *timer, double *avg)
{
       int sum = 0;
       int i = 0;

       for(; i < guess; ++i) {
               sum += *--timer;
       }
       *avg = (double)sum / guess;
}

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