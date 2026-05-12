// swordless, a turn-based auto-battler RPG
// By Anthony Lugo

#include "pretty.c"
#include "dialogue.c"
#include "enemies.c"
#include "items.c"
#include "overworld.c"
#include "shop.c"
#include "map.c"
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_status(void);
player mc;
int main(void)
{
    mc.level = 1;
    mc.purse = 50;
    mc.experience = 0;
    mc.location = 0;
    mc.maxhp = 10;
    mc.currenthp = 10;
    mc.dmg = 1;
    mc.def = 0;

    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        mc.inventory[i] = -1;
    }

    load_items();
    load_locations();
    load_enemies();

    CLEAR
    ENDFX
    printf("Welcome to SWORDLESS\n");
    PAUSE
    printf("What is your NAME? (Input and press ENTER)\n> ");
    scanf("%s", mc.name);
    CLEAR
    char *greetings = (char *) malloc(100);
    sprintf(greetings, "Welcome to SWORDLESS, %s!", mc.name);
    printf("%s", greetings);
    free(greetings);
    NEWLINE
    NEWLINE
    PAUSE
    speak(INTRODUCTION);
    PAUSE
    NEWLINE
    speak(KING_INTRODUCTION);
    NEWLINE
    PAUSE
    PAUSE
    PAUSE
    PAUSE
    CLEAR

    int destination_ID;

    speak("Input the number of the target location/option and press ENTER to select it.\n");
    int last_inventory_index = -1;
    while (true)
    {
        print_status();
        speak(locations[mc.location].flavor);
        destination_ID = prompt_location(mc.location);

        if (destination_ID == -1)
        {
            CLEAR
            printf("Equip/Unequip Item:\n\n");
            for (int i = 0; i < 10; i++)
            {

                if (mc.inventory[i] == -1)
                {
                    break;
                }

                printf("%d. ", i + 1);

                if (item_data[mc.inventory[i]].equipped == 1)
                {
                    BOLD
                }

                printf("%s", rarities[item_data[mc.inventory[i]].rarity]);

                printf("%s", item_data[mc.inventory[i]].name);

                ENDFX

                if (item_data[mc.inventory[i]].count > 1)
                {
                    printf(" x%d", item_data[mc.inventory[i]].count);
                }

                if (item_data[mc.inventory[i]].weapon)
                {
                    printf(" DMG:%d", item_data[mc.inventory[i]].damage);
                }
                if (item_data[mc.inventory[i]].armor || item_data[mc.inventory[i]].trinket)
                {
                    printf(" DEF:%d", item_data[mc.inventory[i]].defense);
                }
                if (item_data[mc.inventory[i]].equipped)
                {
                    printf(" (EQUIPPED)");
                }

                last_inventory_index = i;
                printf("\n");
            }
            if (mc.inventory[0] == -1)
            {
                printf("1. Done\n");
            }
            else
            {
                printf("%d. Done\n", last_inventory_index + 2);
            }

            int equip_choice;
            printf("\n> ");
            scanf("%d", &equip_choice);
            if (mc.inventory[0] == -1)
            {
                if (equip_choice == 1)
                {
                    CLEAR
                    continue;
                }
                else
                {
                    printf("Invalid choice.\n");
                    PAUSE
                    CLEAR
                    continue;
                }
            }
            else if (equip_choice < last_inventory_index + 3 && equip_choice > 0)
            {

                if (!item_data[mc.inventory[equip_choice - 1]].equipped &&
                    (item_data[mc.inventory[equip_choice - 1]].weapon ||
                     item_data[mc.inventory[equip_choice - 1]].trinket ||
                     item_data[mc.inventory[equip_choice - 1]].armor))
                {
                    item_data[mc.inventory[equip_choice - 1]].equipped = 1;

                    printf("\n%s equipped", item_data[mc.inventory[equip_choice - 1]].name);
                    if (item_data[mc.inventory[equip_choice - 1]].weapon)
                    {
                        mc.dmg += item_data[mc.inventory[equip_choice - 1]].damage;
                        for (int i = 0; i < 16; i++)
                        {
                            if (i == mc.inventory[equip_choice - 1])
                            {
                                continue;
                            }
                            if (item_data[i].weapon)
                            {
                                if (item_data[i].equipped)
                                {
                                    mc.dmg -= item_data[i].damage;
                                }

                                item_data[i].equipped = 0;
                            }
                        }
                    }
                    if (item_data[mc.inventory[equip_choice - 1]].armor)
                    {
                        mc.def += item_data[mc.inventory[equip_choice - 1]].defense;
                        for (int i = 0; i < 16; i++)
                        {
                            if (i == mc.inventory[equip_choice - 1])
                            {
                                continue;
                            }
                            if (item_data[i].armor)
                            {
                                if (item_data[i].equipped)
                                {
                                    mc.def -= item_data[i].defense;
                                }
                                item_data[i].equipped = 0;
                            }
                        }
                    }
                    if (item_data[mc.inventory[equip_choice - 1]].trinket)
                    {
                        mc.def += item_data[mc.inventory[equip_choice - 1]].defense;
                        for (int i = 0; i < 16; i++)
                        {
                            if (i == mc.inventory[equip_choice - 1])
                            {
                                continue;
                            }
                            if (item_data[i].trinket)
                            {

                                if (item_data[i].equipped)
                                {
                                    mc.def -= item_data[i].defense;
                                }
                                item_data[i].equipped = 0;
                            }
                        }
                    }
                }
                else
                {
                    item_data[mc.inventory[equip_choice - 1]].equipped = 0;
                    printf("\n%s unequipped", item_data[mc.inventory[equip_choice - 1]].name);
                }
                NEWLINE
                PAUSE
                PAUSE
            }
            CLEAR
        }
        else
        {
            mc.location = travel(mc.location, destination_ID);
        }

        if (mc.currenthp <= 0)
        {
            NEWLINE
            speak("Your soul takes a pitiful rest.");
            NEWLINE
            PAUSE
            printf("YOU DIED");
            NEWLINE
            return 0;
        };

        if (mc.experience >= mc.level * 10)
        {
            speak("You leveled up! You feel a little stronger.");
            mc.experience -= mc.level * 10;
            mc.level++;
            mc.maxhp += 10;
            mc.currenthp = mc.maxhp;
            mc.dmg += 1;
            BOLD printf("+10 HP\n+1 DMG\n");
            if (mc.level % 2 == 0)
            {
                printf("+1 DEF\n");
                mc.def += 1;
            }
            ENDFX
            PAUSE
            PAUSE
        }
    };

    if (mc.currenthp > mc.maxhp)
    {
        mc.currenthp = mc.maxhp;
    }
}

void print_status(void)
{
    printf("  ");
    BOLD printf("%s ", mc.name);
    ENDFX
    printf("\n  DMG: ");
    BOLD printf("%d ", mc.dmg);
    ENDFX
    printf("DEF: ");
    BOLD printf("%d", mc.def);
    ENDFX
    printf("\n  LVL: ");
    BOLD printf("%d ", mc.level);
    ENDFX
    printf("EXP: ");
    BOLD printf("%d/%d ", mc.experience, mc.level * 10);
    ENDFX
    printf("GOLD: ");
    BOLD YELLOW printf("%d", mc.purse);
    ENDFX
    printf("\n  HP: ");
    BOLD printf("%d/%d ", mc.currenthp, mc.maxhp);
    ENDFX

    printf("[");
    for (int i = 1; i < mc.maxhp + 1; i++)
    {
        if (mc.currenthp <= mc.maxhp * 0.5)
        {
            YELLOW
        }
        else
        {
            GREEN
        }
        if (i > mc.currenthp)
        {
            RED
        }
        printf("▆");
        ENDFX
    }
    printf("]  \n  ");

    printf("inventory: \n  ");

    for (int i = 0; i < 10; i++)
    {

        if (mc.inventory[i] == -1)
        {
            break;
        }

        printf("[%d] ", i + 1);

        if (item_data[mc.inventory[i]].equipped == 1)
        {
            BOLD
        }

        printf("%s", rarities[item_data[mc.inventory[i]].rarity]);

        printf("%s", item_data[mc.inventory[i]].name);

        ENDFX

        if (item_data[mc.inventory[i]].count > 1)
        {
            printf(" x%d", item_data[mc.inventory[i]].count);
        }

        if (item_data[mc.inventory[i]].weapon)
        {
            printf(" DMG:%d", item_data[mc.inventory[i]].damage);
        }
        if (item_data[mc.inventory[i]].armor || item_data[mc.inventory[i]].trinket)
        {
            printf(" DEF:%d", item_data[mc.inventory[i]].defense);
        }
        if (item_data[mc.inventory[i]].equipped)
        {
            printf(" (EQUIPPED)");
        }

        printf("\n  ");
    }

    NEWLINE
}
