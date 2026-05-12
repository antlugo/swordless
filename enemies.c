#include <stdbool.h>
typedef struct
{
    char * name;
    int level;
    int maxhp;
    int defense;
    int damage;
    int actions;
    int idle_chance;
    int drop_chance;
    int drop_ID;
    int experience;
}
enemy;

enemy enemies[16];





int battle(int hp, int maxhp, int dmg, int def, int enemy, int lvl, char * name)
{
    BOLD
    printf("You came across %s!\n", enemies[enemy].name);

    ENDFX
    NEWLINE
  int enemy_maxhp = enemies[enemy].maxhp;
  int enemy_hp = enemies[enemy].maxhp;

  char passage[256];

  int turn_counter = 1;
  if (enemy == 15)
  {
    speak("The archwizard makes a bolt for your heart!\n");
    PAUSE
    goto skip_turn;
  }

  while (hp > 0 && enemy_hp > 0)
  {



    printf("Turn %d\n\n", turn_counter);
    turn_counter++;

    GREEN
    BOLD
    printf("LVL %d ｢", lvl);
    ENDFX
    BOLD
    printf("%s", name);
    GREEN
    printf("｣\nHP: %d/%d\n", hp, maxhp);
    printf("DMG: %d DEF: %d\n", dmg, def);
    ENDFX

    printf("[");
    for (int i = 1; i < maxhp + 1; i++)
    {
        if (hp <= maxhp * 0.5)
        {
            YELLOW
        }
        else
        {
            GREEN
        }
        if (i > hp)
        {
            RED
        }
        printf("▆");
        ENDFX
    }
    printf("]  \n\n");




    BOLD
    PURPLE
    printf("LVL %d ｢", enemies[enemy].level);
    ENDFX
    BOLD
    printf("%s", enemies[enemy].name);
    ENDFX
    BOLD
    PURPLE
    printf("｣\n");
    printf("HP: %.0f%%\n", (float)enemy_hp * 100 / (float)enemy_maxhp);
    ENDFX

    printf("[");
    for (int i = 1; i < enemy_maxhp + 1; i++)
    {
        if (enemy_hp <= enemy_maxhp * 0.5)
        {
            CYAN
        }
        else
        {
            PURPLE
        }
        if (i > enemy_hp)
        {
            RED
        }
        printf("▆");
        ENDFX
    }
    printf("]  \n\n");



    PAUSE

    printf("You attack %s!\n", enemies[enemy].name);
    PAUSE
    int damage_dealt = dmg + (rand() % ((((dmg) / 5) + 1) + 1));
    if (rand() % 100 < lvl * 10)
    {
      BOLD
      GREEN
      printf("Critical Strike!\n");
      ENDFX
      PAUSE
      damage_dealt *= 2;
    }
    damage_dealt -= enemies[enemy].defense;
    if (damage_dealt < 1)
    {
      damage_dealt = 1;
    }
    enemy_hp -= damage_dealt;
    printf("You deal %d damage\n", damage_dealt);


    if (enemy_hp <= 0)
    {
      break;
    }
    PAUSE
    NEWLINE


    skip_turn:

    for (int i = 0; i < enemies[enemy].actions; i++)
    {
      int rng = (rand() % 99) + 1;

      if (rng <= enemies[enemy].idle_chance)
      {
        printf("%s is idling about\n", enemies[enemy].name);
        PAUSE
      }
      else
      {
        int damage = enemies[enemy].damage + (rand() % ((((enemies[enemy].damage) / 5) + 1) + 1));
        printf("%s attacks!\n", enemies[enemy].name);
        PAUSE
        if (rng > 95)
        {
          BOLD
          PURPLE
          printf("Desperate Strike!\n");
          ENDFX
          PAUSE
          damage *= 2;
        }
        damage -= def;
        if (damage < 1)
        {
          damage = 1;
        }
        printf("You take %d damage\n", damage);
        PAUSE
        hp -= damage;
      }
    }
    PAUSE


    CLEAR

  }

  if (hp <= 0)
  {
    PAUSE
    PAUSE
    return 0;
  }


  BOLD
  printf("%s defeated!\n", enemies[enemy].name);
  PAUSE
  ENDFX
    printf("You gain %d experience points from the ordeal.\n", enemies[enemy].experience);

  if (enemy == 15)
  {
        PAUSE
        PAUSE
        CLEAR
        speak(ARCHWIZARD_DEFEAT);

        PAUSE
        speak(
            "\n\n"
            "                                  ..',;::cc:;,..\n"
            "                           ....';:ccc::::cclodddlccc:,'..       ....,;::::;.\n"
            "                        .,:c:,..                ...';lx00Odc;;ldl,..     .dx'\n"
            "                     .,;;:'.                           .;o0NWWWKo::::::cok0o.\n"
            "                   .ldc.                                 :0WKddkKXNNWNNKko,\n"
            "                .;od:.                                .ckK0l'   ..',,,'.\n"
            "               .lKk'                                .cKWXo.\n"
            "              'x0l.                              ':o0XKo,           ..\n"
            "             'OWd.                             .oXWWNx,.        .'cxOx,\n"
            "            .xWWl                            ,xKWMMN0o:;'       lXNKo.\n"
            "            .OMWl                       .,;:dXWN0xdoc,.        .,c;.               "
            "...\n"
            "            .xWWx.                  .,lxOXWMMXx,.           ,dd,          "
            ",oxdcclooodOO:\n"
            "             'kNNk:..           ...;ccclxXWNk,           .:x0x,        "
            ".:xKKOxl;'...lKXl.\n"
            "               ,d0K0ko:,.      ...   .dXWXx,           .:0Xk,        .cOXkc.      "
            ";kXk,\n"
            "                 ..'...            'lOWXk;           .cOKk;.       .lOKd,.     "
            ".;okx:.\n"
            "                                 .oXMNx,            'kN0:.       .c0Kd'       :OKx'\n"
            "                               'lONKx;           ,ldKO:.       .c0Kd'      'lxkl,.   "
            ".\n"
            "             ....            .cKWXd'            ;0WNk'        ,kKx,      .c0Xx'  "
            ".';,.\n"
            "           ':'.            ,d0Kkc'             ;0NXd.       ,x0O:.      ;ONXd;:lc;'.\n"
            "          :kc           .;d00k:.               :0KKx:;,.   .:;'.       .lKXKOko,.\n"
            "         .xXo.     ..;okOko,.                   ......                   ....\n"
            "          ;dxlc:::ccodo:.\n"
            "            ..'''..\n");
        NEWLINE
        abort();
  }

  PAUSE
  PAUSE
  CLEAR
  return hp;
}

void load_enemies(void)
{
    enemies[0].name = "blue slime";
    enemies[0].level = 1;
    enemies[0].maxhp = 5;
    enemies[0].defense = 0;
    enemies[0].damage = 2;
    enemies[0].actions = 1;
    enemies[0].idle_chance = 20;
    enemies[0].drop_chance = 50;
    enemies[0].drop_ID = 4;
    enemies[0].experience = 3;

    enemies[1].name = "horned bat";
    enemies[1].level = 1;
    enemies[1].maxhp = 5;
    enemies[1].defense = 1;
    enemies[1].damage = 1;
    enemies[1].actions = 2;
    enemies[1].idle_chance = 10;
    enemies[1].drop_chance = 32;
    enemies[1].drop_ID = 5;
    enemies[1].experience = 8;

    enemies[2].name = "goblin scout";
    enemies[2].level = 2;
    enemies[2].maxhp = 20;
    enemies[2].defense = 1;
    enemies[2].damage = 1;
    enemies[2].actions = 2;
    enemies[2].idle_chance = 30;
    enemies[2].drop_chance = 15;
    enemies[2].drop_ID = 6;
    enemies[2].experience = 5;

    enemies[3].name = "hermit slime";
    enemies[3].level = 3;
    enemies[3].maxhp = 5;
    enemies[3].defense = 3;
    enemies[3].damage = 2;
    enemies[3].actions = 1;
    enemies[3].idle_chance = 50;
    enemies[3].drop_chance = 30;
    enemies[3].drop_ID = 7;
    enemies[3].experience = 12;

    enemies[4].name = "rocky mole";
    enemies[4].level = 4;
    enemies[4].maxhp = 30;
    enemies[4].defense = 1;
    enemies[4].damage = 3;
    enemies[4].actions = 3;
    enemies[4].idle_chance = 30;
    enemies[4].drop_chance = 90;
    enemies[4].drop_ID = 3;
    enemies[4].experience = 24;

    enemies[5].name = "winged slime";
    enemies[5].level = 4;
    enemies[5].maxhp = 50;
    enemies[5].defense = 0;
    enemies[5].damage = 7;
    enemies[5].actions = 3;
    enemies[5].idle_chance = 65;
    enemies[5].drop_chance = 50;
    enemies[5].drop_ID = 3;
    enemies[5].experience = 18;

    enemies[6].name = "frosty slime";
    enemies[6].level = 5;
    enemies[6].maxhp = 30;
    enemies[6].defense = 2;
    enemies[6].damage = 5;
    enemies[6].actions = 1;
    enemies[6].idle_chance = 10;
    enemies[6].drop_chance = 30;
    enemies[6].drop_ID = 8;
    enemies[6].experience = 52;

    enemies[7].name = "mad axeman";
    enemies[7].level = 6;
    enemies[7].maxhp = 50;
    enemies[7].defense = 0;
    enemies[7].damage = 8;
    enemies[7].actions = 2;
    enemies[7].idle_chance = 30;
    enemies[7].drop_chance = 100;
    enemies[7].drop_ID = 9;
    enemies[7].experience = 80;

    enemies[15].name = "Archwizard";
    enemies[15].level = 10;
    enemies[15].maxhp = 200;
    enemies[15].defense = 0;
    enemies[15].damage = 10;
    enemies[15].actions = 2;
    enemies[15].idle_chance = 1;
    enemies[15].drop_chance = 0;
    enemies[15].drop_ID = 10;
    enemies[15].experience = 0;



}
