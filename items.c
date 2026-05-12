#include <stdbool.h>

typedef struct
{
    char * name;
    int value;
    bool equipped;
    bool armor;
    bool trinket;
    int defense;
    bool weapon;
    int damage;
    int rarity;
    int count;
}
item;


item item_data[16];

void load_items(void)
{

item_data[0].name = "leather armor";
item_data[0].value = 25;
item_data[0].equipped = 0;
item_data[0].armor = 1;
item_data[0].trinket = 0;
item_data[0].defense = 3;
item_data[0].weapon = 0;
item_data[0].rarity = 0;
item_data[0].count = 0;

item_data[1].name = "wooden pike";
item_data[1].value = 15;
item_data[1].equipped = 0;
item_data[1].armor = 0;
item_data[1].trinket = 0;
item_data[1].weapon = 1;
item_data[1].damage = 3;
item_data[1].rarity = 0;
item_data[1].count = 0;

item_data[2].name = "copper ring";
item_data[2].value = 20;
item_data[2].equipped = 0;
item_data[2].armor = 0;
item_data[2].trinket = 1;
item_data[2].defense = 1;
item_data[2].weapon = 0;
item_data[2].rarity = 0;
item_data[2].count = 0;


item_data[3].name = "pearl";
item_data[3].value = 33;
item_data[3].armor = 0;
item_data[3].trinket = 0;
item_data[3].weapon = 0;
item_data[3].rarity = 1;
item_data[3].count = 0;

item_data[4].name = "slime gel";
item_data[4].value = 8;
item_data[4].armor = 0;
item_data[4].trinket = 0;
item_data[4].weapon = 0;
item_data[4].rarity = 0;
item_data[4].count = 0;

item_data[5].name = "bat wing";
item_data[5].value = 4;
item_data[5].armor = 0;
item_data[5].trinket = 0;
item_data[5].weapon = 0;
item_data[5].rarity = 0;
item_data[5].count = 0;

item_data[6].name = "blow dart";
item_data[6].value = 10;
item_data[6].equipped = 0;
item_data[6].armor = 0;
item_data[6].trinket = 0;
item_data[6].weapon = 1;
item_data[6].damage = 4;
item_data[6].rarity = 1;
item_data[6].count = 0;

item_data[7].name = "hermit shell";
item_data[7].value = 41;
item_data[7].equipped = 0;
item_data[7].armor = 0;
item_data[7].trinket = 2;
item_data[7].defense = 1;
item_data[7].weapon = 0;
item_data[7].rarity = 2;
item_data[7].count = 0;

item_data[8].name = "gold nugget";
item_data[8].value = 210;
item_data[8].equipped = 0;
item_data[8].armor = 0;
item_data[8].trinket = 0;
item_data[8].weapon = 0;
item_data[8].rarity = 2;
item_data[8].count = 0;

item_data[9].name = "worn axe";
item_data[9].value = 140;
item_data[9].equipped = 0;
item_data[9].armor = 0;
item_data[9].trinket = 0;
item_data[9].weapon = 1;
item_data[9].damage = 5;
item_data[9].rarity = 2;

item_data[10].name = "elven earrings";
item_data[10].value = 342;
item_data[10].equipped = 0;
item_data[10].armor = 0;
item_data[10].trinket = 1;
item_data[10].defense = 3;
item_data[10].weapon = 0;
item_data[10].damage = 0;
item_data[10].rarity = 3;
item_data[10].count = 0;



}










int equip(char target_item[])
{
    return 0;
}



