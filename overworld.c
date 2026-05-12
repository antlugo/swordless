#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "location_struct.c"



extern int edges[16][16];
extern location locations[16];

int prompt_location(int location_ID)
{
    int choice;
    int n;
    char passage[256];
    int *edge_ptr = &edges[location_ID][0];
    try_again:
    n = 1;
    edge_ptr = &edges[location_ID][0];
    while (*edge_ptr != -1)
    {
        sprintf(passage, "%d. travel to %s", n, locations[*edge_ptr].name);
        speak(passage);
        edge_ptr++;
        n++;
    }
    sprintf(passage, "%d. equip/unequip item", n);
    speak(passage);
    printf("\n> ");

    scanf("%d", &choice);

    if (choice > n || choice < 1)
    {
        printf("\nInvalid choice.\n");
        sleep(2);
        CLEAR
        goto try_again;
    }
    CLEAR

    if (choice == n)
    {
        return -1;
    }

    edge_ptr = &edges[location_ID][0];
    int destination = *(edge_ptr + (choice - 1));
    return destination;
}

int prompt_recovery(int recovery_ID, int purse)
{
    int choice;
    printf("Pay %d gold to rest here? (%d)\n\n", locations[recovery_ID].recovery_cost, purse);
    printf("1. Pay %d gold\n", locations[recovery_ID].recovery_cost);
    printf("2. Decline\n");
    printf("\n> ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        return 1;
    }

    return 0;

}
