#ifndef CONFIG_H
#define CONFIG_H

// static 代表這份變數只在引用它的那個檔案內有效
static char *monster_10_names[] = {
    "Slime", "Goblin", "Kobold", "Giant Rat", "Skeleton"
};

// 20級 (進階怪物：比基礎怪物更具威脅性)
static char *monster_20_names[] = {
    "Orc Warrior", "Dire Wolf", "Harpy", "Ghoul", "Giant Spider"
};

// 30級 (精英怪物：具有特殊能力或強大體能)
static char *monster_30_names[] = {
    "Troll", "Gargoyle", "Minotaur", "Wraith", "Manticore"
};

// 40級 (首領級/高階怪物：具有毀滅性的力量)
static char *monster_40_names[] = {
    "Fire Drake", "Iron Golem", "Vampire Lord", "Lich", "Chimera"
};
#endif //FUNCTION_H