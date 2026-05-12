#include <stdbool.h>

typedef struct location
{
    char * name;
    bool recovery;
    int recovery_cost;
    int boss_ID;
    bool boss_respawn;
    int shop_ID;
    int treasure_ID;
    char * flavor;

}
location;



