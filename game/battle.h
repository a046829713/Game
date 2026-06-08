#ifndef BATTLE_H
#define BATTLE_H

//! @file battle.h
//! @brief Defines structures and functions for the battle system.

// Forward declaration for the Combatant struct
struct Combatant;

/**
 * @enum CombatantType
 * @brief Defines the type of a combatant.
 */
typedef enum {
    PLAYER,
    ENEMY
} CombatantType;

/**
 * @enum BattleStatus
 * @brief Represents the current state or outcome of a battle.
 */
typedef enum {
    BATTLE_ONGOING,
    BATTLE_VICTORY,
    BATTLE_DEFEAT,
} BattleStatus;

/**
 * @struct Combatant
 * @brief Represents a single participant in a battle (player or enemy).
 */
typedef struct Combatant {
    char name[50];
    CombatantType type;
    int max_hp;
    int current_hp;
    int defense;
    int attack;    
    // --- Integrating stats from BODYINFO ---
    int power;
    int agile;
    int intelligence;
    int job_type; // 0: Warrior, 1: Rogue, 2: Mage
} Combatant;



typedef struct Enemy {
    char name[50];
    CombatantType type;
    int max_hp;
    int current_hp;
    int defense;
    int attack;    
    // --- Integrating stats from BODYINFO ---
    int power;
    int agile;
    int intelligence;
    int exp_fall;
} Enemy;

// --- Function Prototypes ---

void start_battle(Combatant *player, Enemy *enemy);


BattleStatus battle_loop(Combatant *player, Enemy *enemy);
void display_battle_status(const Combatant *player, const Enemy *enemy);

/**
 * @brief Calculates the damage dealt by an attacker to a defender.
 */
int calculate_damage(const Combatant *attacker, const Enemy *defender);

#endif