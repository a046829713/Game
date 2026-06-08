#include "function.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

static bool is_seeded = false; // 只有 function.c 看得到這個變數


// 根據選擇的職業，初始化角色屬性
void GetBodyInfo(BODYINFO *info, int profession)
{
    switch (profession)
    {
    case 1: // Warrior
        info->power = 10;
        info->agile = 5;
        info->intelligence = 3;
        break;
    case 2: // Mage
        info->power = 3;
        info->agile = 5;
        info->intelligence = 10;
        break;
    case 3: // Archer
        info->power = 5;
        info->agile = 10;
        info->intelligence = 3;
        break;
    default: // Default case
        info->power = 5;
        info->agile = 5;
        info->intelligence = 5;
        break;
    }

    info->job_type = profession;
    info->hp = 100;
    info->level = 1;
    info->exp = 0;
    info->exp_scale = 1;
}



int GetRandom(int number_ceiling) {
    // srand 全名為 :Seed Random 
    if (!is_seeded) {
        // 在整個運行環境中只要運行一次就好
        srand((unsigned int)time(NULL));
        is_seeded = true;
    }
    
    return rand() % number_ceiling;
}

void GetMonsterBodyInfo(MONSTERBODYINFO *info, int kind)
{
    switch (kind)
    {
    case 1: //
        info->power = 10;
        info->agile = 2;
        info->intelligence = 3;
        info->defense = 2;
        break;
    case 2: // Boss
        info->power = 20;
        info->agile = 4;
        info->intelligence = 6;
        info->defense = 4;
        break;
    default: // Default case
        info->power = 5;
        info->agile = 5;
        info->intelligence = 5;
        break;
    }

    info->job_type = kind;
    info->hp = 200;
    info->level = 1;

    if ((*info).level < 10)
    {
        char *MonsterName = monster_10_names[GetRandom(5)];
        UpdateString(info->name, sizeof(info->name), MonsterName);
    }

    
    info->exp = 5;
}

void UpdateString(char *buffer, int size, char *inputSoure){
    // to safety update the string.
    snprintf(buffer, size, inputSoure);

}





void Gethero(Combatant *hero, BODYINFO info)
{
    hero->power = info.power * info.level;
    hero->agile = info.agile * info.level;
    hero->intelligence = info.intelligence * info.level;
    hero->job_type = info.job_type;
    hero->max_hp = info.hp * info.level;
    hero->current_hp = hero->max_hp;
    strcpy(hero->name, info.name);
    
}

void GetMonster(Enemy *monster, MONSTERBODYINFO info)
{
    monster->power = info.power * info.level;
    monster->agile = info.agile * info.level;
    monster->intelligence = info.intelligence * info.level;
    monster->max_hp = info.hp * info.level;
    monster->current_hp = monster-> max_hp;
    strcpy(monster->name, info.name);
    monster->defense = info.defense *info.level;
    monster->exp_fall = info.exp * info.level;

}

void updateheroInfo(BODYINFO *hero_info , int exp){
    hero_info->exp = hero_info-> exp + exp;

    if (hero_info->exp > hero_info->exp_scale){
        hero_info->exp_scale = hero_info->exp_scale * 1.2;
        hero_info->level = hero_info->level +1;
    }


}


void UpdateMonsterName(MONSTERBODYINFO *monsterBodyInfo){
    char *MonsterName;

    if (monsterBodyInfo->level < 10){
        MonsterName = monster_10_names[GetRandom(5)];
    }else if (monsterBodyInfo->level >= 10 && monsterBodyInfo->level < 20)
    {
        MonsterName = monster_20_names[GetRandom(5)];
    }else if (monsterBodyInfo->level >= 20 && monsterBodyInfo->level < 30)
    {
        MonsterName = monster_30_names[GetRandom(5)];
    }else if (monsterBodyInfo->level >= 30 && monsterBodyInfo->level < 40)
    {
        MonsterName = monster_40_names[GetRandom(5)];
    };
    
    UpdateString(monsterBodyInfo->name, sizeof(monsterBodyInfo->name), MonsterName);

}



void updateMonsterInfo(
    MONSTERBODYINFO *monsterBodyInfo, BODYINFO *heroBodyInfo
)
{
    // change the monster level
    printf("current hero level is %d : \n", heroBodyInfo->level);
    printf("current monster level is %d : \n", monsterBodyInfo->level);

    monsterBodyInfo->level =  heroBodyInfo->level + GetRandom(3);



    // change the monster name
    UpdateMonsterName(monsterBodyInfo);
}