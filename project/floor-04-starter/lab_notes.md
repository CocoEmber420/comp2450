1.
> search Goblin
Goblin   HP 8   ATK 2   weakness: fire
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> sort inventory by value desc
   1.  Cloak of shadows  (wt 1.5, val 80)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Rusty sword       (wt 4.0, val 5)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Iron key          (wt 0.1, val 0)
> inspect 99
No such item. (index 98 out of bounds for size 5)
> log 8
   1.  error: index 98 out of bounds for size 5
   2.  sort inventory by value desc
   3.  inventory ΓÇö listed 5 items
   4.  search Goblin ΓÇö found in bestiary
   5.  began session as "Nameless One"
  (newest first; chain length 5)
> benchmark log 100000
  N= 100000   Chain::push_front =    70.05 ms   Bag::insert(begin) = 302493.53 ms
> selftest chain
  Chain<int> allocations:  1000   deallocations:  1000   leaked:     0   OK
> quit
The forge cools. The chain dissolves link by link.

2.
> selftest chain
  Chain<int> allocations:  1000   deallocations:     0   leaked:  1000   LEAK ΓÇö implement ~Chain() / clear()
  -> Leaked all of them, but once it's back it doesn't leak any

3.
>------ Build started: Project: CMakeLists, Configuration: Debug ------
  [1/2] Building CXX object CMakeFiles\the_descent.dir\main.cpp.obj
  FAILED: [code=2] CMakeFiles/the_descent.dir/main.cpp.obj 
  C:\PROGRA~1\MICROS~4\18\COMMUN~1\VC\Tools\MSVC\1451~1.362\bin\Hostx64\x64\cl.exe  /nologo /TP   /DWIN32 /D_WINDOWS /GR /EHsc /Zi /Ob0 /Od /RTC1 -std:c++17 -MDd /W4 /showIncludes /FoCMakeFiles\the_descent.dir\main.cpp.obj /FdCMakeFiles\the_descent.dir\ /FS -c C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-04-starter\main.cpp
C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-04-starter\main.cpp(263): error C2280: 'dungeon::Chain<int>::Chain(const dungeon::Chain<int> &)': attempting to reference a deleted function
  C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-04-starter\hero\Chain.h(106): note: see declaration of 'dungeon::Chain<int>::Chain'
  C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-04-starter\hero\Chain.h(106): note: 'dungeon::Chain<int>::Chain(const dungeon::Chain<int> &)': function was explicitly deleted
  ninja: build stopped: subcommand failed.

  It is pointing at the third line (Chain<int> b = a;), saying that it cannot be referenced because it is a deleted function (the copy contructor). It would attempt to double delete the same memory, which would crash the program.

4.
benchmark log 100000
  N= 100000   Chain::push_front =    70.05 ms   Bag::insert(begin) = 302493.53 ms
Inserting something into the front of a vector makes the machine reallocate every other vector element in order to make space, but push_front just has to change some of the nodes' pointers.

5.
One-paragraph reflection. Mavren keeps the bestiary in a Bag<Monster> but the event log in a Chain<std::string>. 
Defend her choice for each container — what access pattern does each face, and what would go wrong if you swapped them?

The bestiary needs to be able to access a set number of things by index or name randomly, based on the user's needs.
The event log is always read sequentially and grows by adding an event to the end/beginning of the list. Because of these
things, the Bag is the best for the bestiary and the Chain is best for the event log. If you switched them, the bestiary
wouldn't be able to look up an index (the pointers are all over the place in a chain) and every new event in the log
would cause all the old events to shift over. It would use too much data and time when the original choices were data-
efficient and quick.