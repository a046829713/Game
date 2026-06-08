#include "battle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Note: srand(time(NULL)) should be called once in main.c

/**
 * @brief Calculates the damage dealt by an attacker to a defender.
 * @param attacker The combatant who is attacking.
 * @param defender The combatant who is defending.
 * @return The final damage value.
 */
int calculate_damage(const Combatant *attacker, const Enemy *defender) {
    float base_damage = 0.0f;
    float final_damage = 0.0f;

    // 根據職業類型來決定主要屬性
    switch (attacker->job_type) {
        case 1: // 戰士 (Warrior) - 主要看力量
            base_damage = attacker->power * 1.5f + attacker->agile * 0.5f + attacker->attack;
            break;
        case 3: // 弓箭手 (Archer) - 主要看敏捷
            base_damage = attacker->agile * 1.8f + attacker->power * 0.7f + attacker->attack;
            break;
        case 2: // 法師 (Mage) - 主要看智力
            base_damage = attacker->intelligence * 2.5f + attacker->attack * 0.2f;
            break;
        default: // 如果沒有設定職業，就用一個通用公式
            base_damage = attacker->power * 1.2f + attacker->agile * 0.8f + attacker->intelligence * 0.5f + attacker->attack;
            break;
    }

    // --- 暴擊計算 (由敏捷決定) ---
    // 敏捷越高，暴擊機率越大。假設每 10 點敏捷增加 5% 暴擊率
    int crit_chance = (attacker->agile / 10) * 5;
    if ((rand() % 100) < crit_chance) {
        base_damage *= 1.5f; // 暴擊造成 1.5 倍傷害
    } else {
        // No change for non-crit
    }
    
    // --- 加入最終的隨機浮動 ---
    // 讓傷害在 90% ~ 110% 之間浮動
    float random_factor = (90 + rand() % 21) / 100.0f; // 產生 0.90 ~ 1.10 的浮點數
    base_damage *= random_factor;

    // --- 防禦減傷 ---
    // 簡單的減法公式
    final_damage = base_damage - defender->defense;

    // 確保傷害不會是負數
    if (final_damage < 1) {
        final_damage = 1; // 至少造成 1 點傷害
    }



    return (int)final_damage; // 回傳整數傷害
}

void start_battle(Combatant *player, Enemy *enemy) {
    printf("\n--- Start Fight! ---\n");
    printf("%s met %s!\n\n", player->name, enemy->name);
    display_battle_status(player, enemy);
    
}

BattleStatus battle_loop(Combatant *player, Enemy *enemy) {
    // 這裡將會是戰鬥的主要迴圈邏輯
    // 為了範例，我們先簡單實作一回合的攻擊
    // printf("\nIt is %s turn.\n", player->name);
    int damage_dealt = calculate_damage(player, enemy);
    printf("you hit the damage is %d:\n",damage_dealt);
    Sleep(1000);
    
    enemy->current_hp -= damage_dealt;
    // printf("%s to %s caused %d damage!\n", player->name, enemy->name, damage_dealt);

    if (enemy->current_hp <= 0) {
        enemy->current_hp = 0;
        // display_battle_status(player, enemy);
        return BATTLE_VICTORY;
    }

    // 之後可以加入敵人的回合...
    // display_battle_status(player, enemy);
    return BATTLE_ONGOING; // 假設戰鬥還在繼續
}

void display_battle_status(const Combatant *player, const Enemy *enemy) {
    printf("----------------------------------\n");
    printf("%s: HP %d/%d\n", player->name, player->current_hp, player->max_hp);
    printf("%s: HP %d/%d\n", enemy->name, enemy->current_hp, enemy->max_hp);
    printf("----------------------------------\n");
}





