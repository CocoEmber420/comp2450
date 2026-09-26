1. 
> search Goblin
Goblin   HP 8   ATK 2   weakness: fire
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> inspect 99
No such item. (index 98 out of bounds for size 5)
> log --oldest 5
  1. began session as "Nameless One"
  2. search Goblin ΓÇö found in bestiary
  3. inventory ΓÇö listed 5 items
  4. error: index 98 out of bounds for size 5
oldest first; chain length 4.
> clone hero
  -- original log (newest first) --
   1.  error: index 98 out of bounds for size 5
   2.  inventory ΓÇö listed 5 items
   3.  search Goblin ΓÇö found in bestiary
   4.  began session as "Nameless One"
  (newest first; chain length 4)
  -- cloned log (newest first) --
   1.  error: index 98 out of bounds for size 5
   2.  inventory ΓÇö listed 5 items
   3.  search Goblin ΓÇö found in bestiary
   4.  began session as "Nameless One"
  (newest first; chain length 4)
  (clone is being destroyed now)
  (clone destroyed; original event log still has 4 entries ΓÇö try `log 3`)
> log 3
   1.  clone hero ΓÇö copy lived and died
   2.  error: index 98 out of bounds for size 5
   3.  inventory ΓÇö listed 5 items
  (newest first; chain length 5)
> selftest chain
  Phase 1 (single chain)
    allocations:  1000   deallocations:  1000   leaked:     0   OK
  Phase 2 (deep copy)
    original after copy died ΓÇö forward walk:  1000   backward walk:  1000
    copy before death        ΓÇö forward walk:  1000   backward walk:  1000
    allocations:  2000   deallocations:  2000   leaked:     0   OK
> quit
The forge cools. Two chains dissolve, each by its own hand.

2.
Well, the code that you want us to switch isn't actually there, but I assume that the log --oldest 5 would only print one line.
The previous node wouldn't be read, since you didn't assign it to the new node, and I assume it would be assigned a nullptr instead,
which would make the program believe that it had already reached the head.

3.
Exception thrown: read access violation.
p was 0xFFFFFFFFFFFFFFEF.
line 44 of ChainTests.cpp in the walkForward function.

4.
Chain& operator=(const Chain& other) {
    Chain tmp(other);
    swap(tmp);
    return *this;
}

Chain& operator=(const Chain& other) {
    if (this == &other) return *this;
    clear();
    for (const Node* p = other.head_; p; p = p->next) {
        push_back(p->data);
    }
    return *this;
}

I think once I study and look deeper into the first one, it will be easier to do. Unfortunately, right now off the top of my
head, it would probably be easier for me to write the longer one, since everything makes explicit sense.

5.
A singly-linked list doesn't have any previous pointers, so in order to assign nullptr to the new tail, you have to walk the
whole entire list to find the new tail. This gives you more than O(1).

6.
You need a destructor, copy constructor (deep copies), and a copy assignment operator (operator=) in order to avoid memory leaks
or double-free errors (deleting the same pointer twice). The rule of zero doesn't need any of those things because the parts all
already have their own set constructors and behavior. Chain<T> doesn't qualify because it deals with raw memory points that aren't
all in order like they are for a vector.