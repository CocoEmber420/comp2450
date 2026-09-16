# Trial I — *The Foundations Brief*

*Warden of the Foundations · Midterm 1 · 15 %*

Four short answers, one from each floor above. **50–100 words per answer.** No code on this trial (except the lambdas in Q3); just clear thinking.

AI is welcome to *check* your answers; it is not welcome to *write your sentences*. These answers are short enough that an LLM voice is recognisable.

---

## 1. Floor 0 — ADT

> Your battle's "Use item" menu shows the *currently usable* items in your hero's inventory on this turn. Name the right ADT for that menu. Defend the choice against its closest neighbour (e.g., why `bag` instead of `set`, or `list` instead of `bag`).

I would (and we DID) use a bag for my hero's inventory. I choose to defend the bag against a set, since it does seem like the closest ADT. In both a bag
and a set, the items are unordered. The difference comes in when you look at duplicates. Sets do NOT allow duplicates, while bags do. If I am trying to
make an inventory for my hero, I feel like it is necessary to make it possible to obtain multiple of one item (like health potions or bread). If you 
run out of your many versions of that item, then it should be no longer usable on that turn.

---

## 2. Floor 1 — search & Big-O

> Your inventory is kept sorted by healing power (in this codebase an item's `value` measures its potency, so `value` plays the healing-power role). The player types `use Healing potion`. Linear or binary search to find it by name? Justify, and give the Big-O for each.

Normally, I would use binary search. It isn't much of a problem or difference when the inventory is small, but once it gets large enough, the runtime for
linear search can increase A LOT. Linear has an average and worst-case Big-O of O(n), while binary has an average and worst-case Big-O of O(logn). log(n)
grows WAY slower than n, which you can really see when you look at their graphs. Unfortunately, in this example the inventory is sorted by value, not by 
name. Binary search needs the list to be sorted by the right key, otherwise it may not work at all. So my answer is Linear search (unless the user sorts
the inventory differently), but there should be a cap on the size of the inventory so it doesn't get out of hand.

---

## 3. Floor 2 — sort & comparators

> Your "Use item" menu must be displayable sorted *either* by healing power (meaning `value`) *or* by weight. Show a one-line comparator (lambda) for each. One sentence on what language feature makes one `std::sort` call serve both orders.

*Note: `Item` has no healing field — an item's `value` measures its potency, so `value` plays the healing-power role here and in your battle.*

```cpp
// by healing power — i.e. by value
auto byValue  = [] (const Item& a, const Item& b) {return a.value < b.value;};

// by weight
auto byWeight = [] (const Item& a, const Item& b) {return a.weight < b.weight;};
```

std::sort is a template (begin, end, comparator), and the third input can take a lambda function as the cmp (so you can plug either byValue or byWeight
into the same std::sort function).

---

## 4. Floor 3 — templates & exceptions

> Why does `Bag<T>` live in `Bag.h` instead of `Bag.cpp`? And: when the player types `9` for a 4-option menu, where in your code should the validation **throw**, and where should it **catch**?

If it was in the .cpp file, the template would only compile for the data types inside. It wouldn't be a usable container outside of the .cpp file. If
Bag<T> is in the header file, though, it can be #include-d into other .cpp files as well. The code calls the .at() function in Bag.h, which throws an 
exception if the index is larger than or equal to the size of the bag. The call for .at() is in main.cpp, nested inside a try{}. Underneath/outside 
the try{}, we catch the BagException and display the error message.
