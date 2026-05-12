#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "player_struct.c"






location locations[16];
int edges[16][16] =
{
    {2, 5, 1, 3, -1},
    {0, 4, 10, 3, -1},
    {-1},
    {0, 9, 1, -1},
    {1, 6, -1},
    {-1},
    {4, 7, -1},
    {6, 8, -1},
    {7, -1},
    {3, -1},
    {1, 11, -1},
    {10, 12, -1},
    {11, 13, -1},
    {12, 14, -1},
    {13, 15, -1},
    {0, -1}
};

extern player mc;

int travel(int origin, int destination)
{
    int  n = 0;
    while (edges[origin][n] != -1)
    {
        if (edges[origin][n] == destination)
        {

            if (locations[destination].recovery == 1)
            {
                speak(locations[destination].flavor);
                printf("\n");
                if (prompt_recovery(destination, mc.purse))
                {
                    if (mc.purse < locations[destination].recovery_cost)
                    {
                        speak("I'm afraid your purse is a tad too light to stay tonight.\n");
                        PAUSE
                    }
                    else
                    {
                        mc.purse -= locations[destination].recovery_cost;
                        mc.currenthp = mc.maxhp;
                        if (mc.currenthp < mc.maxhp / 4)
                        {
                            speak("You take a much-needed rest\n");
                        }
                        else
                        {
                            speak("You take a moment to catch your breath\n");
                        }

                        PAUSE
                        PAUSE
                    }
                }
                CLEAR
                return origin;
            }
            if (locations[destination].shop_ID != -1)
            {
                speak(locations[destination].flavor);
                printf("\n");
                int * shop_results = open_shop(locations[destination].shop_ID, mc.purse, mc.inventory);
                if (shop_results[0] == -1 && shop_results[1] == -1 && shop_results[2] == -1)
                {
                    goto skip_results;
                }
                mc.purse += *shop_results;
                if (*shop_results > 0)
                {
                    mc.inventory[*(shop_results + 1)] = -1;
                }
                for (int i = 0; i < 10; i++)
                {
                 if (mc.inventory[i] == *(shop_results + 2))
                 {
                    goto skip_results;
                 }
                }
                mc.inventory[*(shop_results + 1)] = *(shop_results + 2);

                skip_results:
                free(shop_results);
                for (int bub = 0; bub < 10; bub++)
                {
                for (int i = 0; i < 9; i++)
                {
                    if (mc.inventory[i] == -1 && mc.inventory[i + 1 ] != -1)
                    {
                        mc.inventory[i] = mc.inventory[i + 1];
                        mc.inventory[i + 1] = -1;

                    }
                }
            }
                return origin;
            }
            if (locations[destination].boss_ID != -1)
            {

                mc.currenthp = battle(mc.currenthp, mc.maxhp, mc.dmg, mc.def, locations[destination].boss_ID, mc.level, mc.name);
                mc.experience += enemies[locations[destination].boss_ID].experience;

                if (mc.currenthp <= 0)
                {
                    goto skip_treasure;
                }



                int rng = (rand() % 99) + 1;


                if (rng < enemies[locations[destination].boss_ID].drop_chance)
                {
                BOLD
                printf("What a surprise!\n");
                ENDFX
                printf("The %s dropped a %s!\n", enemies[locations[destination].boss_ID].name, item_data[enemies[locations[destination].boss_ID].drop_ID].name);
                PAUSE
                PAUSE



                if (item_data[enemies[locations[destination].boss_ID].drop_ID].count == 0)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (mc.inventory[i] == -1)
                        {
                            mc.inventory[i] = enemies[locations[destination].boss_ID].drop_ID;
                            item_data[enemies[locations[destination].boss_ID].drop_ID].count++;
                            break;
                        }
                        if (i == 9)
                        {
                            printf("Inventory full. Loot placed back down.\n");
                        }
                    }

                }
                else
                {
                    item_data[enemies[locations[destination].boss_ID].drop_ID].count++;
                }


            }


                if (!locations[destination].boss_respawn)
                {
                    locations[destination].boss_ID = -1;
                }




            }
            if (locations[destination].treasure_ID != -1)
            {
                BOLD
                printf("What a surprise!\n");
                ENDFX
                printf("You found a %s!\n", item_data[locations[destination].treasure_ID].name);
                PAUSE

                if (item_data[locations[destination].treasure_ID].count == 0)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (mc.inventory[i] == -1)
                        {
                            mc.inventory[i] = locations[destination].treasure_ID;
                            item_data[locations[destination].treasure_ID].count++;
                            locations[destination].treasure_ID = -1;
                            break;
                        }
                        if (i == 9)
                        {
                            printf("Inventory full. Treasure placed back down.\n");
                            PAUSE
                        }
                    }

                }
                else
                {
                    item_data[locations[destination].treasure_ID].count++;
                    locations[destination].treasure_ID = -1;
                }




              locations[destination].treasure_ID = -1;
            }
            skip_treasure:
            return destination;
        }
        n++;
    }
    return origin;
}

void load_locations(void)
{

    locations[0].name = "capital";
    locations[0].recovery = 0;
    locations[0].boss_ID = -1;
    locations[0].shop_ID = -1;
    locations[0].treasure_ID = -1;
    locations[0].flavor = "Where your journey starts.";

    locations[1].name = "forest";
    locations[1].recovery = 0;
    locations[1].boss_ID = 0;
    locations[1].boss_respawn = 1;
    locations[1].shop_ID = -1;
    locations[1].treasure_ID = -1;
    locations[1].flavor = "Mellow green leaves bounce with the wind.";

    locations[2].name = "capital inn";
    locations[2].recovery = 1;
    locations[2].recovery_cost = 15;
    locations[2].shop_ID = -1;
    locations[2].flavor = "The capital inn is aged, but has a homely quality to it.";

    locations[3].name = "beach";
    locations[3].recovery = 0;
    locations[3].boss_ID = 3;
    locations[3].boss_respawn = 1;
    locations[3].shop_ID = -1;
    locations[3].treasure_ID = -1;
    locations[3].flavor = "The beach is clean. Too clean.";

    locations[4].name = "cave entrance";
    locations[4].recovery = 0;
    locations[4].boss_ID = 2;
    locations[4].boss_respawn = 1;
    locations[4].shop_ID = -1;
    locations[4].treasure_ID = -1;
    locations[4].flavor = "Bats squeak from within.";


    locations[5].name = "capital general store";
    locations[5].recovery = 0;
    locations[5].boss_ID = -1;
    locations[5].shop_ID = 0;
    locations[5].treasure_ID = -1;
    locations[5].flavor = "VENDOR: Welcome! We've got the basics, just enough to get you started.";


    locations[6].name = "cave floor one";
    locations[6].recovery = 0;
    locations[6].boss_ID = 1;
    locations[6].boss_respawn = 1;
    locations[6].shop_ID = -1;
    locations[6].treasure_ID = -1;
    locations[6].flavor = "The echo of your foot steps go on for miles.";

    locations[7].name = "cave floor two";
    locations[7].recovery = 0;
    locations[7].boss_ID = 1;
    locations[7].boss_respawn = 1;
    locations[7].shop_ID = -1;
    locations[7].treasure_ID = -1;
    locations[7].flavor = "If the floor was made of gold, you wouldn't know.";


    locations[8].name = "cave floor end";
    locations[8].recovery = 0;
    locations[8].boss_ID = 4;
    locations[7].shop_ID = -1;
    locations[7].treasure_ID = -1;
    locations[8].boss_respawn = 0;
    locations[8].shop_ID = -1;
    locations[8].treasure_ID = 8;
    locations[8].flavor = "A comfy place for a dwarf";

    locations[9].name = "shoreline";
    locations[9].recovery = 0;
    locations[9].boss_ID = -1;
    locations[9].shop_ID = -1;
    locations[9].treasure_ID = 3;
    locations[9].flavor = "The sealine almost taunts you";

    locations[10].name = "elven forest";
    locations[10].recovery = 0;
    locations[10].boss_ID = 5;
    locations[10].boss_respawn = 1;
    locations[10].shop_ID = -1;
    locations[10].treasure_ID = -1;
    locations[10].flavor = "Things feel ever so slightly magical in this elvish forest.";

    locations[11].name = "abandoned elven capital";
    locations[11].recovery = 0;
    locations[11].boss_ID = -1;
    locations[11].boss_respawn = 0;
    locations[11].shop_ID = -1;
    locations[11].treasure_ID = 10;
    locations[11].flavor = "The wreckage is everywhere";

    locations[12].name = "tundra";
    locations[12].recovery = 0;
    locations[12].boss_ID = 6;
    locations[12].boss_respawn = 1;
    locations[12].shop_ID = -1;
    locations[12].treasure_ID = -1;
    locations[12].flavor = "Colder than anything you've ever felt";

    locations[13].name = "great mountain path";
    locations[13].recovery = 0;
    locations[13].boss_ID = 7;
    locations[13].boss_respawn = 0;
    locations[13].shop_ID = -1;
    locations[13].treasure_ID = 8;
    locations[13].flavor = "A purple hue illuminates the peak. You're not far.";

    locations[14].name = "purple portal";
    locations[14].recovery = 0;
    locations[14].boss_ID = -1;
    locations[14].boss_respawn = 0;
    locations[14].shop_ID = -1;
    locations[14].treasure_ID = -1;
    locations[14].flavor = "The portal leads into a dark abyss.";

    locations[15].name = "archwizard";
    locations[15].recovery = 0;
    locations[15].boss_ID = 15;
    locations[15].boss_respawn = 0;
    locations[15].shop_ID = -1;
    locations[15].treasure_ID = -1;
    locations[15].flavor = "Is it over?";




}
