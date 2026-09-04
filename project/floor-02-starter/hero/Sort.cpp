// COMP 2450 — Floor 2 starter
// hero/Sort.cpp — YOU implement this file.
//
// Three functions to write. Read Sort.h for their contracts.
//
// The big idea this week: sorting is not one algorithm, it is a family
// of tradeoffs. Merge sort is predictable but copies. Quicksort is fast
// on average but betrays you on bad inputs. std::sort is what you
// actually ship. You will write the first two, race all three in
// `benchmark sort`, and argue — in a commit message — which one the
// game should call.
//
// Tips for the Pivot Wraith:
//   * If you pick the FIRST element as your quicksort pivot, a sorted
//     input becomes O(n^2). The `benchmark sort --bad-pivot --sorted`
//     harness exists to show you exactly that.
//   * The middle element is the cheapest defense. Good enough for this
//     week. Real production code (std::sort) does median-of-three and
//     switches algorithms on bad recursion depth.
//
// Submit when:  `sort inventory by weight` produces ascending weight,
//               `sort inventory by name desc` produces reverse alphabetical,
//               and `benchmark sort` gives three timing columns on every row.

#include "Sort.h"
#include <algorithm>  // you will want std::sort in sortInventory
#include <sstream>

namespace dungeon {

// ---- 1. Merge sort ------------------------------------------------------

namespace {
    //merge sort
    static void merge(std::vector<Item>& v, std::size_t lo, std::size_t mid, std::size_t hi, const Comparator& cmp) {
        std::vector<Item> scratch;
        std::size_t i = lo, j = mid;

        //sort first half
        while (i < mid && j < hi) {
            if (!cmp(v[j], v[i])) {
                scratch.push_back(v[i++]);
            }
            else {
                scratch.push_back(v[j++]);
            }
        }

        //other half
        while (i < mid) {
            scratch.push_back(v[i++]);
        }
        while (j < hi) {
            scratch.push_back(v[j++]);
        }

        //copy back to v
        for (std::size_t k = 0; k < scratch.size(); ++k) {
            v[lo + k] = std::move(scratch[k]);
        }
    }

    static void mergeSortImpl(std::vector<Item>& v, std::size_t lo, std::size_t hi, const Comparator& cmp) {
        //base case
        if (hi - lo < 2) {
            return;
        }
        
        //recursion
        std::size_t mid = lo + (hi - lo) / 2;
        mergeSortImpl(v, lo, mid, cmp);
        mergeSortImpl(v, mid, hi, cmp);
        merge(v, lo, mid, hi, cmp);
    }

    //quicksort
    static std::size_t partition(std::vector<Item>& v, std::size_t lo, std::size_t hi, const Comparator& cmp) {
        std::size_t mid = lo + (hi - lo) / 2;
        std::swap(v[mid], v[hi]);
        const Item pivot = v[hi];
        //lomuto assumes the pivot lives at high, so by moving our pivot there we can follow classic lomuto

        //lomuto scan
        std::size_t store = lo;
        //[low, store) --> strictly LESS than the pivot
        //[store, high) --> >= pivot
        for (std::size_t i = lo; i < hi; ++i) {
            if (cmp(v[i], pivot)) {
                std::swap(v[store], v[i]);
                ++store;
            }
        }

        std::swap(v[store], v[hi]);
        return store;
    }

    static void quicksortImpl(std::vector<Item>& v, std::size_t lo, std::size_t hi, const Comparator& cmp) {
        //base case
        if (lo >= hi) {
            return;
        }

        //recursive
        std::size_t p = partition(v, lo, hi, cmp);
        if (p > lo) {
            quicksortImpl(v, lo, p - 1, cmp);
        }
        quicksortImpl(v, p + 1, hi, cmp);
    }

    //sort
    Comparator makeComparator(const std::string& key, bool descending) {
        //std::function<bool(const Item&, const Item&)>
        Comparator cmp;
        if (key == "name") {
            cmp = [](const Item& a, const Item& b) {
                return a.name < b.name;
                };
        }
        else if (key == "weight") {
            cmp = [](const Item& a, const Item& b) {
                return a.weight < b.weight;
                };
        }
        else if (key == "value") {
            cmp = [](const Item& a, const Item& b) {
                return a.value < b.value;
                };
        }
        else {
            return nullptr;
        }

        //descending sort
        if (descending) {
            Comparator asc = cmp;
            cmp = [asc](const Item& a, const Item& b) {
                return asc(b, a);
                };
        }

        return cmp;
    }
}

void mergeSort(std::vector<Item>& inventory, const Comparator& cmp) {
    //call helper function
    mergeSortImpl(inventory, 0, inventory.size(), cmp);
}

// ---- 2. Quicksort -------------------------------------------------------

void quicksort(std::vector<Item>& inventory, const Comparator& cmp) {
    if (inventory.size() < 2) {
        return;
    }
    quicksortImpl(inventory, 0, inventory.size() - 1, cmp);
}

// ---- 3. sortInventory (the seam) ----------------------------------------

bool sortInventory(Hero& hero, const std::string& criterion) {
    std::istringstream in(criterion);
    std::string key, dir;
    in >> key >> dir;

    bool descending = (dir == "desc");
    Comparator cmp = makeComparator(key, descending);
    if (!cmp) {
        return false;
    }
    std::sort(hero.inventory.begin(), hero.inventory.end(), cmp);
    return true;
}

}  // namespace dungeon
