1.
=== THE HALL OF ECHOES ===

What is your name, adventurer? Court

Welcome, Court.
Cantor Resh stands at the lectern at the centre of the hall, eyes half-closed.
He repeats whatever you say last. Speak carefully; the hall remembers in stacks.

(commands:
   search <name>                 ΓÇö look up by name in bestiary, inventory, OR event log
   list                          ΓÇö list the bestiary
   inventory                     ΓÇö list your inventory
   inspect <n>                   ΓÇö show the nth item in your inventory
   take <name>                   ΓÇö add a small item by that name to your inventory
   sort inventory by <key> [asc|desc]
                                 ΓÇö key is name, weight, or value
   undo                          ΓÇö reverse the most recent mutating command
   lint <text>                   ΓÇö check that brackets/parens/braces in <text> balance
   log [n]                       ΓÇö show the last n events, newest first
   log --oldest [n]              ΓÇö show the first n events, oldest first
   clone hero                    ΓÇö deep-copy the hero, print both logs, let the copy die
   selftest chain                ΓÇö Chain<T> leak + deep-copy harness
   selftest iterator             ΓÇö Chain<T>::iterator harness
   selftest stack                ΓÇö Stack<T> push/pop/top/LIFO harness
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   benchmark log [N]             ΓÇö race Chain::push_front vs vector insert(begin)
   battle warden                 ΓÇö face the Warden of the Foundations
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> selftest stack
  empty Stack<int>: size==0 && empty(): OK
  push(7): size==1 && top()==7: OK
  push 1,2,3: size==3 && top()==3 (LIFO): OK
  after pop(): size==2 && top()==2: OK
  drain to empty: size==0 && empty(): OK
  all phases OK
> lint ({a} (b) [c])
  balanced
> lint ({)}
  not balanced
> lint hello (world
  not balanced
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> take Lantern
  Taken: Lantern  (wt 0.1, val 1)
> sort inventory by weight
   1.  Iron key          (wt 0.1, val 0)
   2.  Loaf of bread     (wt 0.1, val 1)
   3.  Lantern           (wt 0.1, val 1)
   4.  Healing potion    (wt 0.5, val 12)
   5.  Cloak of shadows  (wt 1.5, val 80)
   6.  Rusty sword       (wt 4.0, val 5)
> undo
Undid: sort inventory by weight
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
   6.  Lantern           (wt 0.1, val 1)
> undo
Undid: take Lantern
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> undo
Nothing to undo.
> quit
The cantor falls silent. The last echo decays. The hall is quiet.

2.
A data structure is a way of changing and storing data in your code. Some examples of 
these are arrays, linked lists, binary trees, heaps, and graphs. An ADT (Abstract Data
Type) is predefined, a way to hide operations from the coder. It has underlying data
structures, but the programmer doesn't need to know how they work to use the ADT. Stack
is definitely an ADT, since it always does the same thing (we only use push and pop, 
although it really means push_front and pop_front) without the programmer having to 
explicitly state what to do. Chain is a data structure, since it is a basic arrangement
of linked nodes that we have to manipulate ourselves. It's just basic (chain) vs hidden
(stack). The base chain is covered by the stack functions, but the functions come from chain.

3.
WITH BAG:
> selftest stack
  empty Stack<int>: size==0 && empty(): OK
  push(7): size==1 && top()==7: OK
  push 1,2,3: size==3 && top()==3 (LIFO): OK
  after pop(): size==2 && top()==2: OK
  drain to empty: size==0 && empty(): OK
  all phases OK
> benchmark log
  (linked O(1) per insert vs vector O(n) per insert)
  N=   1000   Chain::push_front =     2.33 ms   Bag::insert(begin) =    67.99 ms
  N=  10000   Chain::push_front =    28.54 ms   Bag::insert(begin) =  4071.25 ms
  N= 100000   Chain::push_front =   104.38 ms   Bag::insert(begin) = 415595.94 ms

  WITH NORMAL:
  > selftest stack
  empty Stack<int>: size==0 && empty(): OK
  push(7): size==1 && top()==7: OK
  push 1,2,3: size==3 && top()==3 (LIFO): OK
  after pop(): size==2 && top()==2: OK
  drain to empty: size==0 && empty(): OK
  all phases OK
  > benchmark log
  (linked O(1) per insert vs vector O(n) per insert)
  N=   1000   Chain::push_front =     1.80 ms   Bag::insert(begin) =    78.95 ms
  N=  10000   Chain::push_front =    11.82 ms   Bag::insert(begin) =  3741.80 ms
  N= 100000   Chain::push_front =    97.66 ms   Bag::insert(begin) = 411341.99 ms

The benchmark log gets longer and less efficient. Chain is O(1) on both push and pop
on both ends, but Bag would be O(n) on pop_front.

4.
It stops the program and says:
    Exception thrown: read access violation.
    dungeon::Stack<char>::top(...) returned nullptr.

It doesn't promise reference or iterator stability (the nodes or references can be deleted
or reallocated by other functions). In addition, it doesn't have any built-in safety checks,
so you have to throw and catch your own exceptions (or stop them from happening like with
checking if it's empty) or it will crash/stop.


5.
RECURSIVE:
namespace {
    const Monster* binSearchRec(const std::vector<Monster>& bestiary,
                                const std::string&         name,
                                std::size_t                low,
                                std::size_t                high) {
        if (low >= high) return nullptr;
        std::size_t mid = low + (high - low) / 2;
        const std::string& here = bestiary[mid].name;
        if (here == name) return &bestiary[mid];
        if (here <  name) return binSearchRec(bestiary, name, mid + 1, high);
        return                   binSearchRec(bestiary, name, low,     mid);
    }
}  // namespace
const Monster* binarySearchRecursive(const std::vector<Monster>& bestiary,
                                     const std::string&         name) {
    return binSearchRec(bestiary, name, 0, bestiary.size());
}

EXPLICIT:
struct Range { std::size_t lo, hi; };   // half-open [lo, hi), same as the recursive version

const Monster* binarySearchIterative(const std::vector<Monster>& bestiary,
                                     const std::string&         name) {
    dungeon::Stack<Range> p;
    p.push({0, bestiary.size()});
    while (!p.empty()) {
        Range r = p.top();
        p.pop();
        if (r.lo >= r.hi) continue;
        std::size_t mid = r.lo + (r.hi - r.lo) / 2;
        const std::string& here = bestiary[mid].name;
        if (here == name) return &bestiary[mid];
        if (here <  name) p.push({mid + 1, r.hi});
        else              p.push({r.lo, mid}); 
    }
    return nullptr;
}

The explicit-stack version has a physical representation of the range that we have to edit. We can
push and pop stuff from this list. In the recursive version, it hides the range within the recursive
calls.

6.
We spent the rest of the time using the stack (like in lint and undo). We spent a while trying
to code these ourselves, as well as answering worksheet questions about the code and how it works.
I think that this was very important, since we should know why our code works, not just that it works.
I feel like this week was a little simpler from last week, but what we larned this week built upon the
in-depth explanation of chains from last week.