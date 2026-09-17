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
constexpr int kPlayerAttackDmg = 6;   // damage per Attack action
constexpr int kWardenAttackDmg = 4;   // warden's retaliation damage

}  // anonymous namespace

void printStats(int pHP, int wHP);
void printBattleMenu();
void attackSequence(int& pHP, int& wHP);
void inspectWarden(int wHP, const int maxWHP);
void itemUse();

BattleOutcome runWardenBattle(Hero& hero) {
    // TODO — write the boss battle. Suggested outline (yours to refactor):
    //
    //   int playerHP = kPlayerStartHP;
    //   int wardenHP = kWardenStartHP;
    //
    //   while (playerHP > 0 && wardenHP > 0) {
    //       print state (HPs, last action — your choice).
    //
    //       try {
    //           show menu (using your F0 container of actions).
    //           read input.
    //           if invalid → throw BattleException(...) [F3 — throw].
    //           dispatch on the action:
    //               Attack:    wardenHP -= kPlayerAttackDmg;
    //                          if wardenHP > 0, playerHP -= kWardenAttackDmg.
    //               Use item:  std::sort(hero.inventory.begin(),
    //                                    hero.inventory.end(),
    //                                    yourComparator)             [F2].
    //                          show sorted menu, read item name.
    //                          const Item* it = findByName<Item>(
    //                              hero.inventory, name);             [F1]
    //                          if (!it) throw BattleException(...);   [F3]
    //                          apply effect (heal? buff next attack? …).
    //                          end turn.
    //               Inspect:   print warden state. FREE — do NOT end turn.
    //               Flee:      return BattleOutcome::Fled.
    //       }
    //       catch (const std::exception& e) {                        [F3 — catch]
    //           std::cout << "  " << e.what() << "  Try again.\n";
    //           continue;   // re-prompt; turn does NOT advance
    //       }
    //   }
    //
    //   return wardenHP <= 0 ? BattleOutcome::Victory
    //                        : BattleOutcome::Defeat;
    //
    // Decompose into helpers however you want. The contract main.cpp
    // depends on is just runWardenBattle(Hero&).
    //
    // Replace the placeholder body below.

    int playerHP = kPlayerStartHP;
    int wardenHP = kWardenStartHP;

    while (playerHP > 0 && wardenHP > 0) {
        //print turn and HP
        printStats(playerHP, wardenHP);
        
        //exception catcher
        try {
            int menuChoice;
            
            //print menu
            printBattleMenu();

            //get user choice
            std::cout << "> ";
            std::cin >> menuChoice;
            switch (menuChoice) {
                case 1:
                    attackSequence(playerHP, wardenHP);
                    break;
                case 2:
                    itemUse();
                    break;
                case 3:
                    inspectWarden(wardenHP, kWardenStartHP);
                    break;
                case 4:
                    return BattleOutcome::Fled;
                    break;
                default:
                    throw BattleException("Wrong input, must be 1-4");
            }
        }
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
void printBattleMenu() {
    std::cout << "\n1. Attack\n2. Use item\n3. Inspect Warden\n4. Flee\n";
}

//Menu choice 1 - attack
void attackSequence(int& pHP, int& wHP) {
    wHP -= kPlayerAttackDmg;
    std::cout << "You strike for 6.  Warden HP -> " << wHP << "\n";
        
    if (wHP > 0) {
        pHP -= kWardenAttackDmg;
        std::cout << "The Warden retaliates for 4.  Your HP -> " << pHP << "\n";
    }
}

//menu choice 2 - item
void itemUse() {
    std::cout << "You would like to use an item but have currently forgotten how... :)\n";
}

//menu choice 3 - inspect
void inspectWarden(int wHP, const int maxWHP) {
    std::cout << "Warden of the Foundations.\nHP " << wHP << " / " << maxWHP << ".\nNo visible weakness.\n(free action)\n";
}

}  // namespace dungeon
