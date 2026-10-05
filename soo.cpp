#include "raylib.h"
#include <string>
#include <cstdlib>
#include <ctime>

struct Arian {
    int maxHealth = 100;
    int health = 100;
    int attack = 10;
    int armor = 5;
    int level = 1;
    int xp = 0;          
};

struct mutantPig {
    int health = 50;
    int attack = 5;
};

struct Skeleton {
    int health = 65;
    int attack = 8;
};

struct Ghatu {
    int health = 120;
    int attack = 15;
};

enum GameState {
    MENU,
    STORY_INTRO,
    FIGHT_PIG,
    PATH_CHOICE,
    STORY_CAVE,
    FIGHT_SKELETON,
    STORY_CAVE_END,
    STORY_WOODS,
    FIGHT_GHATU,
    GAME_OVER,
    VICTORY
};

int diceRoll() {
    return (rand() % 20) + 1;
}

int main() {
    srand(time(0));

    InitWindow(1100, 750, "The Shadow of Oakhaven");
    SetTargetFPS(60);

    GameState currentState = MENU; 

    Arian arian; 
    mutantPig pig;
    Skeleton skel;
    Ghatu bossGhatu;

    std::string battleLog = "To roll a dice for fight press 'R': ";

    const char* storyIntro = 
        "Once upon a time in the Land of Oakhaven, there was a small village surrounded\n"
        "by souleaters and demonic creatures. The villagers lived in fear, and many had\n"
        "lost their lives to defend their village.\n\n"
        "The villagers were desperate for a hero to save them from the darkness that had\n"
        "taken over their home. There was a young adventurer named Arian, who had heard\n"
        "of the appeal of the villagers and decided to make those villagers live in peace again.\n\n"
        "Arian was a skilled warrior, and he had trained for years to become a great warrior\n"
        "to beat the evil that had taken over Oakhaven. He set out on a journey to defeat\n"
        "the souleaters and demonic creatures.\n\n"
        "But the dark military was too strong and their conqueror Ghatu was too powerful.\n"
        "Arian knew that he needed to find a way to defeat Ghatu and his army. He set out\n"
        "on a quest to defeat Ghatu and save the villagers of Oakhaven...\n\n"
        "--------------------------------------------------------------------------------\n\n"
        "Arian's journey was long and formidable. He faced many challenges in the past\n"
        "like killing mutant pigs, lions and other creatures.\n\n"
        "One day he started to explore the forest to find the source of the evil that\n"
        "had taken over Oakhaven.\n\n"
        "Then suddenly a creature appeared from the shadows...";

    const char* storyCaveText = 
        "You enter the dark cave... Bones rattle in the dark!\n"
        "!!! A SKELETON APPEARS !!!";

    const char* storyCaveEndText = 
        "*** YOU CRUSHED THE SKELETON TO DUST! ***\n"
        "Arian defeated the ancient skeleton and gained the power to beat The Lord of the Darkness Ghatu.\n"
        "Arian continued to search the cave and saw some ancient drawings on the cave walls.\n\n"
        "The drawings told a tragic story of a man once known as Commander Ghatu.\n"
        "Years ago, he was a noble and fearless leader who swore to protect the realm of Oakhaven.\n"
        "However, the drawings revealed a dark betrayal. The very people and kings he protected turned their backs on him, leaving him to die in the shadows.\n"
        "Consumed by sorrow and an unquenchable thirst for revenge, Ghatu surrendered his broken soul to the darkness.\n\n"
        "As Arian traced the final drawing with his hand, the cave began to tremble violently.\n"
        "The stone wall shattered into pieces, revealing a massive, blood-red throne room.\n"
        "Sitting on a throne of bones was Ghatu himself. His eyes burned with hatred as he looked at Arian.\n\n"
        "\"Another fool from Oakhaven comes to die...\" Ghatu's demonic voice echoed through the chamber.\n"
        "He drew his colossal dark blade and leaped forward. Arian tightened his grip, the newly gained power surging through his veins.\n"
        "The final battle begins!";

    const char* storyWoodsText = 
        "You walk into the dead woods. It is eerily quiet. You find a safe spot and rest for the night.\n\n"
        "However, the Dead Woods offer no true rest. In the middle of the night, a chilling wind suddenly extinguishes your campfire.\n"
        "The unnatural silence is broken by the sound of heavy, armored footsteps crushing the withered leaves.\n"
        "You open your eyes and grab your weapon. The twisted trees part, and a colossal figure emerges from the pitch-black shadows.\n\n"
        "It is Ghatu. He has tracked your scent. He slowly drags his demonic greatsword across the dead soil, sending sparks into the dark.\n"
        "\"Did you really think you could hide from the dark in my own woods?\" his voice rasps, shaking the dead branches above.\n\n"
        "There is nowhere left to run. You stand your ground, feeling the power you gained pulsing through you.\n"
        "The final battle under the blood moon begins!";

    const char* victoryText = 
        "*** YOU DEFEATED THE LORD OF THE DARKNESS! ***\n\n"
        "Ghatu drops his massive blade, falling heavily to his knees.\n"
        "\"Perhaps... peace... at last...\" he whispers, his demonic form crumbling into ash.\n"
        "The heavy darkness lifts from the land. You have saved Oakhaven!\n\n"
        "After Arian The Great Warrior defeated Ghatu, he took a long journey to his home village of Oakhaven.\n"
        "As he approached the wooden gates, the anxious silence of the villagers turned into a roaring cheer.\n"
        "A grand feast began. Lanterns lit up the night sky, and joyful music echoed through the valley.\n"
        "Children danced around him, waving wooden swords, while the elders raised their beers to their savior.\n"
        "Sitting by the warm bonfire, surrounded by the laughter of his people, Arian finally smiled.\n"
        "The realm was safe at last, and the great warrior had finally found his peace.\n\n"
        "--- THE END ---";

    while (!WindowShouldClose()) {

        if (currentState == MENU) {
            if (IsKeyPressed(KEY_X)) {
                currentState = STORY_INTRO;
            }
        }
        else if (currentState == STORY_INTRO) {
            if (IsKeyPressed(KEY_SPACE)) {
                currentState = FIGHT_PIG;
                battleLog = " !!! MUTANT PIG APPEARED !!! \nTo roll a dice for fight press 'R': ";
            }
        }
        else if (currentState == FIGHT_PIG) {
            if (IsKeyPressed(KEY_R) && arian.health > 0 && pig.health > 0) {
                int roll = diceRoll();
                if (roll >= 10) {
                    pig.health -= arian.attack;
                    battleLog = "You rolled a [" + std::to_string(roll) + "] -> You hit the mutant pig!\n";
                } else {
                    battleLog = "You rolled a [" + std::to_string(roll) + "] -> You missed!\n";
                }

                if (pig.health > 0) {
                    int damageTaken = pig.attack - (arian.armor / 2);
                    if (damageTaken < 1) damageTaken = 1;
                    arian.health -= damageTaken;
                    battleLog += "Mutant pig attacks! You took " + std::to_string(damageTaken) + " damage!";
                } else {
                    arian.xp += 100;
                    if (arian.xp >= 100) {
                        arian.level++;
                        arian.maxHealth += 20;
                        arian.health = arian.maxHealth;
                        arian.attack += 5;
                        arian.xp -= 100;
                    }
                    currentState = PATH_CHOICE;
                }

                if (arian.health <= 0) {
                    currentState = GAME_OVER;
                }
            }
        }
        else if (currentState == PATH_CHOICE) {
            if (IsKeyPressed(KEY_ONE)) {
                currentState = STORY_CAVE;
            }
            else if (IsKeyPressed(KEY_TWO)) {
                currentState = STORY_WOODS;
            }
        }
        else if (currentState == STORY_CAVE) {
            if (IsKeyPressed(KEY_SPACE)) {
                currentState = FIGHT_SKELETON;
                battleLog = "Press 'R' to attack: ";
            }
        }
        else if (currentState == FIGHT_SKELETON) {
            if (IsKeyPressed(KEY_R) && arian.health > 0 && skel.health > 0) {
                int roll = diceRoll();
                if (roll >= 9) {
                    skel.health -= arian.attack;
                    battleLog = "You rolled a [" + std::to_string(roll) + "] -> Your blade shatters some skeleton bones!\n";
                } else {
                    battleLog = "You rolled a [" + std::to_string(roll) + "] -> The Skeleton blocks!\n";
                }

                if (skel.health > 0) {
                    int damageTaken = skel.attack - (arian.armor / 2);
                    if (damageTaken < 1) damageTaken = 1;
                    arian.health -= damageTaken;
                    battleLog += "Skeleton attacks! You took " + std::to_string(damageTaken) + " damage!";
                } else {
                    currentState = STORY_CAVE_END;
                }

                if (arian.health <= 0) {
                    currentState = GAME_OVER;
                }
            }
        }
        else if (currentState == STORY_CAVE_END) {
            if (IsKeyPressed(KEY_SPACE)) {
                arian.health = arian.maxHealth;
                currentState = FIGHT_GHATU;
                battleLog = "!!! FINAL BOSS: COMMANDER GHATU !!!\nPress 'R' to attack:";
            }
        }
        else if (currentState == STORY_WOODS) {
            if (IsKeyPressed(KEY_SPACE)) {
                arian.health = arian.maxHealth;
                currentState = FIGHT_GHATU;
                battleLog = "!!! FINAL BOSS: COMMANDER GHATU !!!\nPress 'R' to attack:";
            }
        }
        else if (currentState == FIGHT_GHATU) {
            if (IsKeyPressed(KEY_R) && arian.health > 0 && bossGhatu.health > 0) {
                int roll = diceRoll();
                if (roll >= 13) {
                    bossGhatu.health -= arian.attack;
                    battleLog = "You rolled a [" + std::to_string(roll) + "] -> A fierce strike pierces Ghatu's armor!\n";
                } else {
                    battleLog = "You rolled a [" + std::to_string(roll) + "] -> Ghatu parries your attack!\n";
                }

                if (bossGhatu.health > 0) {
                    int damageTaken = bossGhatu.attack - (arian.armor / 2);
                    if (damageTaken < 1) damageTaken = 1;
                    arian.health -= damageTaken;
                    battleLog += "Ghatu attacks! You took " + std::to_string(damageTaken) + " damage!";
                } else {
                    currentState = VICTORY;
                }

                if (arian.health <= 0) {
                    currentState = GAME_OVER;
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (currentState == MENU) {
            DrawText("------ The Shadow of Oakhaven ------", 240, 280, 26, RAYWHITE);
            DrawText("Press 'X' to start the game", 410, 350, 18, RAYWHITE);
        }
        else if (currentState == STORY_INTRO) {
            DrawText(storyIntro, 40, 30, 14, RAYWHITE);
            DrawText("Press 'SPACE' to continue...", 40, 710, 16, GRAY);
        }
        else if (currentState == FIGHT_PIG) {
            DrawText(TextFormat("--- ARIAN'S STATS ---\nLevel:  %d\nHP:     %d / %d\nAttack: %d\nArmor:  %d\nXP:     %d / 100", 
                     arian.level, arian.health, arian.maxHealth, arian.attack, arian.armor, arian.xp), 40, 40, 16, YELLOW);

            DrawText(TextFormat("Your HP: %d | Pig HP: %d", arian.health, pig.health), 400, 40, 18, RAYWHITE);
            DrawText(battleLog.c_str(), 400, 100, 16, RAYWHITE);
            DrawText("Press 'R' to attack", 400, 200, 16, LIGHTGRAY);
        }
        else if (currentState == PATH_CHOICE) {
            DrawText("*** YOU DEFEATED THE MUTANT PIG! ***\nYou gained 100 XP!", 50, 50, 18, GREEN);
            DrawText(TextFormat("LEVEL UP! You are now Level %d!\nYour stats increased and your health is fully restored.", arian.level), 50, 100, 18, GREEN);
            
            DrawText("Choose your path to hunt down Ghatu:\nPress [1] -> Dark Cave\nPress [2] -> Dead Woods", 50, 200, 18, YELLOW);
        }
        else if (currentState == STORY_CAVE) {
            DrawText(storyCaveText, 50, 100, 18, RAYWHITE);
            DrawText("Press 'SPACE' to continue...", 50, 650, 16, GRAY);
        }
        else if (currentState == FIGHT_SKELETON) {
            DrawText(TextFormat("--- ARIAN'S STATS ---\nLevel:  %d\nHP:     %d / %d\nAttack: %d\nArmor:  %d\nXP:     %d / 100", 
                     arian.level, arian.health, arian.maxHealth, arian.attack, arian.armor, arian.xp), 40, 40, 16, YELLOW);

            DrawText(TextFormat("Your HP: %d | Skeleton HP: %d", arian.health, skel.health), 400, 40, 18, RAYWHITE);
            DrawText(battleLog.c_str(), 400, 100, 16, RAYWHITE);
            DrawText("Press 'R' to attack", 400, 200, 16, LIGHTGRAY);
        }
        else if (currentState == STORY_CAVE_END) {
            DrawText(storyCaveEndText, 40, 25, 14, RAYWHITE);
            DrawText("Press 'SPACE' to continue...", 40, 710, 16, GRAY);
        }
        else if (currentState == STORY_WOODS) {
            DrawText(storyWoodsText, 40, 40, 14, RAYWHITE);
            DrawText("Press 'SPACE' to continue...", 40, 710, 16, GRAY);
        }
        else if (currentState == FIGHT_GHATU) {
            DrawText(TextFormat("--- ARIAN'S STATS ---\nLevel:  %d\nHP:     %d / %d\nAttack: %d\nArmor:  %d\nXP:     %d / 100", 
                     arian.level, arian.health, arian.maxHealth, arian.attack, arian.armor, arian.xp), 40, 40, 16, YELLOW);

            DrawText(TextFormat("Your HP: %d | Ghatu HP: %d", arian.health, bossGhatu.health), 400, 40, 18, RAYWHITE);
            DrawText(battleLog.c_str(), 400, 100, 16, RAYWHITE);
            DrawText("Press 'R' to attack Ghatu", 400, 200, 16, LIGHTGRAY);
        }
        else if (currentState == GAME_OVER) {
            DrawText("*** YOU DIED! Oakhaven is doomed... ***", 320, 300, 24, RED);
            DrawText("GAME OVER", 480, 360, 20, RED);
        }
        else if (currentState == VICTORY) {
            DrawText(victoryText, 40, 30, 14, RAYWHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}