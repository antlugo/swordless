#include <stdio.h>





/* IDS
0 capital inn
1 capital general store






*/

int shops[16][5] =
{
    {0, 1, 2, -1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1},
    {-1}
};


int * open_shop(int shop_ID, int purse, int inventory[10])
{
    while (true)
    {
        int * results = (int *)malloc(sizeof(int) * 3);
        results[0] = -1;
        results[1] = -1;
        results[2] = -1;
        int choice;
        int choice2;
        int n;
        char passage[256];
        int * item_ptr = &shops[shop_ID][0];
        try_again:
        item_ptr = &shops[shop_ID][0];

        n = 1;
        while (*item_ptr != -1)
        {
            sprintf(passage, "%d. %s for %d gold", n, item_data[*item_ptr].name, item_data[*item_ptr].value);
            speak(passage);
            item_ptr++;
            n++;
        }
        sprintf(passage, "%d. sell item", n);
        speak(passage);
        int sell_option = n;
        n++;
        sprintf(passage, "%d. leave shop", n);
        speak(passage);
        int leave_option  = n;

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

        if (choice == leave_option)
        {
            *results = -1;
            *(results + 1)  = -1;
            *(results + 2) = -1;
            return results;
        }
        if (choice == sell_option)
        {
            goto selling;
        }

        sprintf(passage, "Buy %s for %d gold?", item_data[shops[shop_ID][choice - 1]].name, item_data[shops[shop_ID][choice - 1]].value);
        speak(passage);
        NEWLINE
        speak("1. Accept");
        speak("2. Decline");
        printf("\n> ");
        scanf("%d", &choice2);
        if (choice2 != 1)
        {
            CLEAR
            goto try_again;
        }
        if (purse >= item_data[shops[shop_ID][choice - 1]].value)
        {
            for (int i = 0; i < 10; i++)
            {
                if (inventory[i] == -1)
                {
                    *(results + 1) = i;
                    break;

                }
                if (i == 9 && inventory[i] != -1)
                {
                    printf("Inventory full\n");
                    PAUSE
                    *results = -1;
                    *(results + 1)  = -1;
                    *(results + 2) = -1;

                    return results;
                }
            }
            *results = -item_data[shops[shop_ID][choice - 1]].value;
            *(results + 2) = shops[shop_ID][choice - 1];
            printf("\nPurchase successful\n");
            printf("%s acquired for %d gold\n", item_data[shops[shop_ID][choice - 1]].name, item_data[shops[shop_ID][choice - 1]].value);
            item_data[shops[shop_ID][choice - 1]].count++;
            PAUSE
            PAUSE

            CLEAR
            return results;
        }
        else
        {
            speak("You don't have enough gold.");
            PAUSE
            CLEAR
            *results = -1;
            *(results + 1)  = -1;
            *(results + 2) = -1;
            return results;
        }




        selling:

        *results = -1;
        *(results + 1)  = -1;
        *(results + 2) = -1;

        speak("Which item would you like to sell?");
        NEWLINE

        int * inv_ptr = &inventory[0];
        n = 1;
        while (*inv_ptr != -1)
        {
            sprintf(passage, "%d. sell %s for %d gold", n, item_data[*inv_ptr].name, item_data[*inv_ptr].value / 2);
            speak(passage);
            inv_ptr++;
            n++;
        }

        sprintf(passage, "%d. buy item", n);
        speak(passage);
        int buy_option = n;
        n++;

        sprintf(passage, "%d. leave shop", n);
        speak(passage);
        int leave_option2 = n;

        printf("\n> ");
        scanf("%d", &choice);

        if (choice > n || choice < 1)
        {
            printf("\nInvalid choice.\n");
            sleep(2);
            CLEAR
            goto selling;
        }

        if (choice == leave_option2)
        {
            return results;
        }
        if (choice == buy_option)
        {
            CLEAR
            goto try_again;
        }

        CLEAR


        sprintf(passage, "sell %s for %d gold?", item_data[inventory[choice - 1]].name, item_data[inventory[choice - 1]].value / 2);
        speak(passage);
        NEWLINE
        speak("1. Accept");
        speak("2. Decline");
        printf("\n> ");
        scanf("%d", &choice2);
        if (choice2 != 1)
        {
            CLEAR
            goto selling;
        }

        *results = item_data[inventory[choice - 1]].value / 2;
        *(results + 1)  = choice - 1;
        *(results + 2) = -1;
        item_data[inventory[choice - 1]].count--;
        item_data[inventory[choice - 1]].equipped = 0;
        if (item_data[inventory[choice - 1]].count > 0)
        {
            *(results + 2) = inventory[choice - 1];
        }
        NEWLINE

        printf("Sale successful\n");
        printf("%s sold for %d gold\n", item_data[inventory[choice - 1]].name, item_data[inventory[choice - 1]].value / 2);
        PAUSE
        PAUSE
        CLEAR


        return results;

    }
}

