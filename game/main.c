#include <stdio.h>
#include "function.h"
#include "battle.h"
// 建議：定義一個最大名稱長度，避免緩衝區溢位
#define MAX_NAME_LENGTH 49

int main()
{

    // record the role value
    BODYINFO hero_info;
    printf("Hello warriors, please enter your name:");
    // 修正：使用 fgets 或 scanf_s 來避免緩衝區溢位。
    // 這裡使用一個安全的 scanf 格式，限制讀取的字元數。
    // %49s 表示最多讀取 49 個字元，留下一個空間給結尾的 '\0'。
    scanf("%49s", hero_info.name);

    int profession_choose;
    printf("choose your profession.[1] is warrior ,[2] is Mage [3] is Archer:");
    scanf("%d", &profession_choose);

    // 修正：GetBodyInfo 應該要接收 hero_info 的指標，才能修改它的內容。
    // 並且，您需要實作這個函式。
    GetBodyInfo(&hero_info, profession_choose);

    // 修正：在 GetBodyInfo 函式修改 hero_info 的值之後再印出。
    printf("Welcome, %s!\n", hero_info.name);
    printf("your power = %d, aglie = %d, intelligence = %d\n, job_type = %d\n", hero_info.power, hero_info.agile, hero_info.intelligence, hero_info.job_type);

    // 產生英雄
    Combatant hero;
    Gethero(&hero, hero_info);

    MONSTERBODYINFO monster_body_info;
    GetMonsterBodyInfo(&monster_body_info, 1);

    // 產生怪物;
    Enemy monster;
    GetMonster(&monster, monster_body_info);
    printf("Game start!\n");

    while (1)
    {
        start_battle(&hero, &monster);
        GetMonster(&monster, monster_body_info);

        
        while (1)
        {

            BattleStatus result = battle_loop(&hero, &monster);

            if (result == 1)
            {

                printf("current monster exp fall is %d : \n", monster.exp_fall);
                updateheroInfo(&hero_info, monster.exp_fall);                
                Gethero(&hero, hero_info);
                
                updateMonsterInfo(&monster_body_info, &hero_info);

                printf("Fighted is done.");
                break;
            }
        }
    }

    printf("Game over.\n");
    // 遊戲主迴圈...
    // 為了讓程式可以結束，我們先在這裡加入一個離開的機制
    printf("Enter 'q' to quit.\n");
    char command;
    // 注意：scanf("%c", &command) 前需要一個空格來消耗掉之前的換行符
    scanf(" %c", &command);
    return 0;
}