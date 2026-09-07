// COMP 2450 — Floor 3 starter
// bestiary/Search.h — Monster-specific searches from Floor 1 (kept as
// reference) PLUS the new function template you write this week.
//
// Floor 1's three searches are still here. The `search` command still
// calls them. The `benchmark` harness still times them. You are not
// editing them this week.
//
// What's NEW on Floor 3 is a function template that generalizes the
// linear-search pattern: ONE source body, the compiler stamps a fresh
// copy for every T you instantiate it with. Monday's lesson, in code.
//
// Notice that findByName<T>'s body lives in THIS header. Template bodies
// must be visible to every caller so the compiler can stamp the right
// version for each T. A .cpp file would only build it for the types it
// happened to name inside itself — useless. Function templates in .h.
// That's a language rule, not a style choice.

#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include "Monster.h"

namespace dungeon {

// ---- Floor 1 reference: Monster-specific searches ---------------------
//
// Linear scan. Works on any order.    O(n).
const Monster* linearSearch(const std::vector<Monster>& bestiary,
                            const std::string&         name);

// Iterative binary search.            O(log n). Pre: sorted.
const Monster* binarySearch(const std::vector<Monster>& bestiary,
                            const std::string&         name);

// Recursive binary search.            O(log n). Pre: sorted.
const Monster* binarySearchRecursive(const std::vector<Monster>& bestiary,
                                     const std::string&         name);

// The seam Floor 1 introduced: one place the rest of the game calls.
const Monster* findMonster(const std::vector<Monster>& bestiary,
                           const std::string&         name);


// ---- Floor 3 (Mon): function template ---------------------------------
template <typename T>
const T* findByName(const std::vector<T>& items, const std::string& name) {
    //walk through list
    for (const auto& it : items) {
        if (it.name == name) {
            return &it;
        }
    }

    //if no match
    return nullptr;
}

}  // namespace dungeon
