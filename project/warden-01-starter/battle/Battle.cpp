// COMP 2450 — Warden of the Foundations (Midterm 1)
// battle/Battle.cpp — YOU build the body.
//
// =====================================================================
// REQUIRED MECHANICS
// =====================================================================
// Re-read the public midterm page if anything below is unclear.
//
// MENU (at minimum, four options):
//   1. Attack          — damage the warden; warden retaliates that turn
//   2. Use item        — pick from inventory; effect; turn ends
//   3. Inspect Warden  — print warden's state; FREE action — turn does
//                        NOT end
//   4. Flee            — leave; gate stays closed
//
// END:
//   Victory  when wardenHP <= 0
//   Defeat   when playerHP <= 0
//   Fled     when the player chose Flee
//
// =====================================================================
// FLOOR-TIED REQUIREMENTS — ALL FOUR MUST APPEAR IN YOUR CODE
// =====================================================================
//
//   F0 (ADT)         — the available actions on a turn must live in a
//                      container of your choice. ABOVE the declaration,
//                      in a comment, name the ADT and defend it in one
//                      sentence (the same kind of defence Trial I Q1
//                      practiced — but this is a different collection
//                      than Q1's items menu; the right ADT may differ).
//
//   F1 (search)      — the Use-item branch MUST call findByName<Item>
//                      against hero.inventory to look up the item the
//                      player typed.
//
//   F2 (sort)        — when the items menu is displayed, sort the
//                      inventory at display time with a comparator
//                      (std::sort or your Floor 2 sortInventory). Pick
//                      a criterion (value — the healing-power stand-in
//                      — weight, or name) and document it in a comment.
//
//   F3 (templates +  — invalid menu input must `throw BattleException`
//      exceptions)     (ready skeleton in Battle.h) — or BagException
//                      where a genuinely bad index is the fault —
//                      caught INSIDE the battle loop so the player gets
//                      another prompt — not a crash, not an exit.
//
// =====================================================================
// WHAT THE GRADER WILL DO
// =====================================================================
//   1. cmake --build the project. If it does not compile, the Warden
//      has won by default.
//   2. Type `battle warden`, play through to BOTH a victory and a
//      defeat (or attempt to — items + RNG permitting).
//   3. Type a deliberately invalid menu choice (e.g., "9" for a
//      4-option menu). The game must NOT crash; it must re-prompt.
//   4. Open this file and find each of the four Floor ties. They must
//      be REAL — i.e., the menu actually runs through your container,
//      Use-item actually goes through findByName, the items menu is
//      actually sorted, the throw actually fires on bad input.

#include "Battle.h"

#include <iostream>
#include <string>
#include <limits>
#include <algorithm>

#include "../hero/Bag.h"
#include "../hero/BagException.h"
#include "../hero/Item.h"
#include "../bestiary/Search.h"
#include "../hero/Sort.h"

namespace dungeon {

namespace {

// =====================================================================
// Tunable battle parameters. Edit to taste; document any tuning in
// encounter-notes.md so the grader knows what to expect.
// =====================================================================
constexpr int kPlayerStartHP   = 30;
constexpr int kWardenStartHP   = 50;
constexpr int kPlayerAttackDmg = 4;   // damage per Attack action
constexpr int kWardenAttackDmg = 6;   // warden's retaliation damage

}  // anonymous namespace

void printStats(int pHP, int wHP);
void printBattleMenu(const std::vector<std::string>& menuItems);
void attackSequence(int& pHP, int& wHP);
void itemUse(Hero& hero, int& pHP, int& wHP);
bool sortInventory(Hero& hero);
void itemChoice(std::string name, const Item*& it, int& pHP, int& wHP);
void inspectWarden(int wHP, const int maxWHP);

BattleOutcome runWardenBattle(Hero& hero) {
    int playerHP = kPlayerStartHP;
    int wardenHP = kWardenStartHP;
    bool sorted = false;

    while (playerHP > 0 && wardenHP > 0) {
        //print turn and HP
        printStats(playerHP, wardenHP);
        
        //exception catcher
        try {
            size_t menuChoice = 0;
            
            //print menu
            //F0 (ADT): a vector fits better than something like a dictionary (no key lookup needed, 
            //just sequential display) or a priority queue (no priority, just a fixed order) since I 
            //only need ordered iteration to print the four options. It's also helpful because I can 
            //use it to check if the input is valid with .size().
            std::vector<std::string> menuItems = { "Attack", "Use item", "Inspect Warden", "Flee" };
            printBattleMenu(menuItems);

            //get user choice
            std::cout << "> ";
            std::cin >> menuChoice;
            if (menuChoice > 0 && menuChoice <= menuItems.size()) {
                switch (menuChoice) {
                case 1:
                    attackSequence(playerHP, wardenHP);
                    break;
                case 2:
                    itemUse(hero, playerHP, wardenHP);
                    break;
                case 3:
                    inspectWarden(wardenHP, kWardenStartHP);
                    break;
                case 4:
                    return BattleOutcome::Fled;
                    break;
                default:
                    throw BattleException("Invalid input, must be 1-4.");
                }
            }
            else if (menuChoice > menuItems.size()) {
                throw BagException(menuChoice, menuItems.size());
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw BattleException("Invalid input, must be a number between 1-4.");
            }
        }
        //F3 (exceptions): catches the battle exception (actually all exceptions)
        catch (const std::exception& excp) {
            std::cout << "  " << excp.what() << "  Try again.\n";
            continue;
        }
    }


    if (wardenHP <= 0) {
        std::cout << "Your HP : " << playerHP << "\nWarden's HP: " << wardenHP << "\n";
        return BattleOutcome::Victory;
    }
    else {
        std::cout << "Your HP : " << playerHP << "\nWarden's HP: " << wardenHP << "\n";
        return BattleOutcome::Defeat;
    }
}

//prints turn and HP stats
void printStats(int pHP, int wHP) {
    std::cout << "\n-- Your turn --\nYour HP: " << pHP << "\nWarden's HP: " << wHP;
}

//prints menu
void printBattleMenu(const std::vector<std::string>& menuItems) {
    std::cout << "\n";
    for (size_t i = 0; i < menuItems.size(); i++) {
        std::cout << (i + 1) << ". " << menuItems[i] << "\n";
    }
}

//Menu choice 1 - attack
void attackSequence(int& pHP, int& wHP) {
    wHP -= kPlayerAttackDmg;
    std::cout << "You strike for " << kPlayerAttackDmg << ". Warden HP -> " << wHP << "\n";
        
    if (wHP > 0) {
        pHP -= kWardenAttackDmg;
        std::cout << "The Warden retaliates for " << kWardenAttackDmg << ". Your HP -> " << pHP << "\n";
    }
}

//menu choice 2 - item
void itemUse(Hero& hero, int& pHP, int& wHP) {
    //sort and display
    sortInventory(hero);
    std::cout << "Type the name of the item you would like to use: \n";
    printInventory(hero);
    std::cout << "> ";

    //get user input and find item
    bool input = false;
    const Item* it = nullptr;
    std::string name;
    std::cin.ignore();
    
    while (!input) {
        std::getline(std::cin, name);
        if (name.empty()) {
            std::cout << "What Item would you like to use?\n> ";
        }
        else {
            //F1 (search): uses findByName<Item> against hero.inventory
            it = findByName<Item>(hero.inventory, name);
            if (!it) {
                std::cout << "Invalid choice, type the name of one of your items.\n> ";
            }
            else {
                input = true;
            }
        }
    }

    //display based on choice
    itemChoice(name, it, pHP, wHP); 
    std::cout << "[ENTER]";
    std::cin.get();
}

//menu choice 2b - item sort by value
bool sortInventory(Hero& hero) {
    //F2 (sort): I sorted by value with std::sort
    Comparator cmp = [](const Item& a, const Item& b) { return a.value < b.value; };
    std::sort(hero.inventory.begin(), hero.inventory.end(), cmp);
    return true;
}

//menu choice 2c - item choice print
void itemChoice(std::string name, const Item*& it, int& pHP, int& wHP) {
    if (name == "Rusty sword") {
        std::cout << "The sword is coated in rust. You must swing carefully so you don't cut yourself.\n";
        wHP -= kPlayerAttackDmg + it->value;
        std::cout << "You strike for " << (kPlayerAttackDmg + it->value) << ". Warden HP -> " << wHP << "\n";
        if (wHP > 0) {
            pHP -= kWardenAttackDmg;
            std::cout << "The Warden retaliates for " << kWardenAttackDmg << ". Your HP -> " << pHP << "\n";
        }
    }
    else if (name == "Healing potion") {
        std::cout << "\nHmm, something actually useful.\n";
        pHP += it->value;
        std::cout << "You have healed " << it->value << " HP. Your HP -> " << pHP << "\n";
        pHP -= kWardenAttackDmg;
        std::cout << "You throw the empty bottle at the Warden, but he doesn't flinch.\n"
            << "The Warden retaliates for " << kWardenAttackDmg << ". Your HP -> " << pHP << "\n";
    }
    else if (name == "Iron key") {
        std::cout << "\nBro, what's the key going to do for you?\n";
        pHP -= kWardenAttackDmg;
        std::cout << "While you were trying to think of options, the Warden prepared his next attack.\n"
            << "The Warden laughs at you for " << kWardenAttackDmg << " (emotional damage). Your HP -> " << pHP << "\n";
    }
    else if (name == "Loaf of bread") {
        std::cout << "\nThe bread is a little old, but you can eat it if you wish.\n";
        pHP += it->value;
        std::cout << "You have healed " << it->value << " HP. Your HP -> " << pHP << "\n";
        pHP -= kWardenAttackDmg;
        std::cout << "In the time it took you to eat the whole loaf, the Warden has readied his next attack.\n"
            << "The Warden pounces for " << kWardenAttackDmg << ". Your HP -> " << pHP << "\n";
    }
    else if (name == "Cloak of shadows") {
        std::cout << "\nThe room is still warm from the fires of the forge. Your cloak will be of no use here.\n";
        pHP -= kWardenAttackDmg;
        std::cout << "While you've been digging around in your satchel, the Warden has been readying his next attack.\n"
            << "The Warden lashes out for " << kWardenAttackDmg << ". Your HP -> " << pHP << "\n";
    }
    else {
        std::cout << "You have managed to hallucinate an object...\n";
    }
}

//menu choice 3 - inspect
void inspectWarden(int wHP, const int maxWHP) {
    std::cout << "Warden of the Foundations.\nHP " << wHP << " / " << maxWHP << ".\nNo visible weakness.\n(free action)\n";
}

}  // namespace dungeon
