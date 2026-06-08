#ifndef FUNCTION_H
#define FUNCTION_H

#include "battle.h"

// 定義角色屬性結構
typedef struct BODYINFO{
    char name[50];
    int power;
    int agile;
    int intelligence;
    int job_type;
    int hp;
    int level;
    int exp;
    int exp_scale;
} BODYINFO;


typedef struct MONSTERBODYINFO{
    char name[50];
    int power;
    int agile;
    int intelligence;
    int job_type;
    int hp;
    int level;
    int defense;
    int exp;
} MONSTERBODYINFO;


void UpdateString(char *buffer, int size, char *inputSoure);
void GetBodyInfo(BODYINFO *info, int profession);
void Gethero(Combatant *Role, BODYINFO info);
void GetMonsterBodyInfo(MONSTERBODYINFO *info, int kind);
void GetMonster(Enemy *monster, MONSTERBODYINFO info );
void updateheroInfo(BODYINFO *info , int exp);
void updateMonsterInfo(MONSTERBODYINFO *monsterBodyInfo, BODYINFO *heroBodyInfo);

#endif //FUNCTION_H