# Trial III — *The Encounter* — Notes

*Warden of the Foundations · Midterm 1 · 60 %*

This file is the grader's map of your battle code. Help us find each piece. Be specific — file and line numbers are encouraged.

---

## AI declaration for Trial III

(One or two sentences. *Which* tool, *what* you asked it for, *what* you did with the result. "Did not use" is fine — but the line must be there.)
*Trial 3 - asked Claude what to put into a cin.ignore(___, "\n") to ignore the string input. std::numeric_limits<std::streamsize>::max() was it's answer.
	I researched it some more, and it seemed like the normal way to do it, I had just forgotten. I used it on line 145.*

---

## Two functions I wrote without AI assistance

These are the functions Friday's quiz can ask me to modify on paper. I wrote each of these by hand, with no autocomplete on the body. Pick functions you know cold — three of the four quiz questions pull from these.

1. `void attackSequence(int& pHP, int& wHP)` in `Battle.cpp:179-188`
2. `void itemChoice(std::string name, const Item*& it, int& pHP, int& wHP)` in `Battle.cpp:236-278`
I'm not sure if these are what you're looking for, but I didn't use AI for any of my functions. There were a couple where I looked at our old code though.

---

## Floor 0–3 ties — where to find them in my code

Help the grader find each of the four required ties.

**Floor 0 (ADT).** The available menu actions are stored in:

- Container type: `std::vector<std::string>`
- Declared at: `battle/Battle.cpp:116`
- ADT name + one-sentence defence: menuItems
     //F0 (ADT): a vector fits better than something like a dictionary (no key lookup needed, 
     //just sequential display) or a priority queue (no priority, just a fixed order) since I 
     //only need ordered iteration to print the four options. It's also helpful because I can 
     //use it to check if the input is valid with .size().

**Floor 1 (search).** `findByName<Item>` is called at:

- `battle/Battle.cpp:212` (Use-item branch)

**Floor 2 (sort).** The at-display sort (`std::sort` with a comparator, or your Floor 2 `sortInventory`) is called at:

- `battle/Battle.cpp:232` (before displaying the items menu)
- Sort criterion: `ascending value` (e.g., descending value — the healing-power stand-in — or ascending weight)
- One-sentence reason: (why this criterion?) -> the value is the most important criterion for this battle, as the healing
                                                power is the only useful detail for the hero (only thing that affects the battle).

**Floor 3 (templates + exceptions).** `BattleException` (or `BagException` where a bad index is the fault) is:

- Thrown at: `battle/Battle.cpp:137` on `Shouldn't throw unless something goes very wrong` --> BattleException
- Thrown at: `battle/Battle.cpp:141` on `if (menuChoice > menuItems.size())` --> BagException
- Thrown at: `battle/Battle.cpp:146` on `if menu choice is not an int` --> BattleException
- Caught at: `battle/Battle.cpp:150` (must be **inside** the battle loop, not in main)

---

## Reflection  *( ≤ 200 words )*

Which Floor's tie was hardest to wire in, and why? Was anything obvious in hindsight that wasn't obvious when you started?

I think that Floor 0's ADT was the hardest to tie in. It wasn't extremely difficult, but I just felt like the menu
and decisions could have been written just fine without it. Maybe if the menu was bigger, then it would be better, but
with something this simple I think it would have been okay. I didn't realize how many of the topics we've been learning
about are actually helpful when building a simple game like this. (Also I had so much fun with this!!!)

---

## Tuning notes (optional)

If you changed any of the tunables (`kPlayerStartHP`, `kWardenStartHP`, `kPlayerAttackDmg`, `kWardenAttackDmg`), or added new ones (item healing amounts, etc.), list them and their values here so the grader can play through your battle without surprise.
    I changed kPlayerAttackDmg to 4 and kWardenAttackDmg to 6.
    I also just used the inventory value of the items for the healing power and extra damage.