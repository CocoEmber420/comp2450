// COMP 2450 — The Descent
// Floor 0: The Antechamber
//
// You will grow this program every week. Today it does almost nothing.
// Your only job: make it compile, make it run, and change one line.

#include <iostream>
#include <string>

int main() {
    std::cout << "\n=== THE ANTECHAMBER ===\n\n";
    std::cout << "A torch sputters. The air smells of iron.\n";
    std::cout << "What is your name, adventurer? ";

    std::string hero_name;
    std::getline(std::cin, hero_name);

    if (hero_name.empty()) {
        hero_name = "Nameless One";
    }

    const std::string flavor = "Autobots... ROLL OUT!!!";

    std::cout << "\nWelcome, " << hero_name << ".\n";
    std::cout << flavor << "\n\n";
    std::cout << "The stair to Floor 1 awaits. Press Enter to rest.\n";

    std::string _;
    std::getline(std::cin, _);

    return 0;
}
