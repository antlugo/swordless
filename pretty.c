#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#if !defined(_POSIX_C_SOURCE)

    #define usleep(s)

#endif

#define CLEAR printf("\n\e[1;1H\e[2J");

#define NEWLINE printf("\n");

#define BOLD printf("\033[1m");
#define BLINK printf("\033[5m");
#define RED printf("\033[91m");
#define GREEN printf("\033[92m");
#define YELLOW printf("\033[93m");
#define BLUE printf("\033[94m");
#define PURPLE printf("\033[95m");
#define CYAN printf("\033[96m");
#define GRAY1 printf("\033[90m");
#define GRAY2 printf("\033[37m");
#define ENDFX printf("\033[0m");
#define PAUSE sleep(1);


char * rarities[] = {"\033[38;5;248m", "\033[38;5;112m", "\033[38;5;39m", "\033[38;5;90m", "\033[38;5;220m", "\033[38;5;160m"};

int speed = 5000;

void speak(char * passage)
{
    int n = strlen(passage);

    int lcc = 0;

    int mll = 100;


    if (passage[0] == '\n')
    {
        mll = 10000;
    }


    for (int i = 0; i < n; i++)
    {
        if (passage[i] == '\n')
        {
            NEWLINE
            continue;
        }
        if (lcc > mll && passage[i] == ' ')
        {
            NEWLINE
            printf(" ");
            lcc = 0;
            continue;
        }

        printf("%c", passage[i]);
        fflush(stdout);
        usleep(speed);
        printf("\b");
        GRAY2
        printf("%c", passage[i]);
        fflush(stdout);
        usleep(speed);
        printf("\b");
        ENDFX
        printf("%c", passage[i]);
        fflush(stdout);
        lcc++;



    }
    NEWLINE
}

