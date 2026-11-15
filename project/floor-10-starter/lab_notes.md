1.

=== THE HALL OF NAMES ===

What is your name, adventurer? Court

Welcome, Court.
Scrivener McCown stands, for once, at rest ΓÇö no chart to straighten.
Behind him a wall of name-plates, each with its meaning engraved
beside it, and a smaller shelf listing every KIND of weakness once.
"On the last two floors I taught you to build the shelf and to keep
it level," he says. "I will not make you build this one. It is
already built ΓÇö better than I could, and it never leans. I only have
to know the name." He speaks a name to the shelf, and the plate answers.

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
   provoke <name>                ΓÇö enqueue an enemy action onto the line
   simulate                      ΓÇö drain the enemy line in FIFO order
   potato <name>... <k>          ΓÇö classical hot-potato survivor (FIFO elimination)
   taxonomy                      ΓÇö print McCown's classification tree as an outline
   taxonomy --dfs                ΓÇö list every entry depth-first (pre-order)
   taxonomy --bfs                ΓÇö list every entry breadth-first (level-order)
   lineage <name>                ΓÇö show the root-to-creature classification path
   catalogue                     ΓÇö list the bestiary in name order (BST in-order)
   recall <name>                 ΓÇö look up a monster fast in the BST
   forget <name>                 ΓÇö remove a monster from the BST
   balance                       ΓÇö is McCown's catalogue tree balanced? (height + factor)
   knows <name>                  ΓÇö does the Registry (std::map) know this name?
   lookup <name>                 ΓÇö look up a monster in the Registry (one std::map::find)
   strike <name>                 ΓÇö remove a monster from the Registry (keeps the maps consistent)
   names                         ΓÇö list the bestiary in name order (std::map + structured bindings)
   weaknesses                    ΓÇö the distinct weaknesses (std::set), each with its count
   weakness <w>                  ΓÇö how many monsters fear <w>? (set membership + map count)
   log [n]                       ΓÇö show the last n events, newest first
   log --oldest [n]              ΓÇö show the first n events, oldest first
   clone hero                    ΓÇö deep-copy the hero, print both logs, let the copy die
   selftest chain                ΓÇö Chain<T> leak + deep-copy harness
   selftest iterator             ΓÇö Chain<T>::iterator harness
   selftest stack                ΓÇö Stack<T> push/pop/top/LIFO harness
   selftest queue                ΓÇö Queue<T> enqueue/dequeue/front/FIFO harness
   selftest tree                 ΓÇö Tree<T> addChild/size/height/traversal/lineage harness
   selftest bst                  ΓÇö BST<T> insert/find/inorder/remove harness
   selftest balance              ΓÇö BST<T> balance factor / rotation harness
   selftest registry             ΓÇö Registry std::set/std::map/std::pair harness
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   benchmark log [N]             ΓÇö race Chain::push_front vs vector insert(begin)
   benchmark bst [N]             ΓÇö race linear scan vs BST lookup over the bestiary
   benchmark balance [N]         ΓÇö same sorted input: plain BST (stick) vs std::set
   benchmark names [N]           ΓÇö std::map::find vs BST::find vs linear scan
   battle warden                 ΓÇö face the Warden of the Foundations
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> selftest registry
  index: size==5, distinct weaknesses==3, count[holy]==3: OK
  knows: Lich present, Drake absent: OK
  recall: Wraith->hp==14, Drake==nullptr: OK
  hasWeakness: holy present, water absent: OK
  countWeakness: holy==3, water==0: OK
  forget: drop a shared weakness (count--), drop a last weakness (erased), absent==false: OK
  all phases OK
> knows Lich
  McCown knows 'Lich'.
> knows Drake
  McCown does not know 'Drake'.
> weaknesses
  blunt  (2 monsters)
  fire  (6 monsters)
  holy  (3 monsters)
  light  (2 monsters)
  slashing  (1 monsters)
  water  (1 monsters)
  (6 distinct weaknesses)
> lookup Lich
Lich   HP 35   ATK 6   weakness: holy
  (looked up in the Registry)
> weakness fire
  6 monsters fear fire.
> names
Bone Spider   HP 6   ATK 2   weakness: fire
Cave Troll   HP 28   ATK 7   weakness: fire
Cinder Bat   HP 4   ATK 1   weakness: water
Frostmaw   HP 22   ATK 6   weakness: fire
Goblin   HP 8   ATK 2   weakness: fire
Ironclaw Bear   HP 24   ATK 5   weakness: slashing
Lich   HP 35   ATK 6   weakness: holy
Marsh Lurker   HP 18   ATK 3   weakness: fire
Necrothrall   HP 16   ATK 4   weakness: light
Ratking   HP 9   ATK 2   weakness: fire
Shadow Hound   HP 12   ATK 4   weakness: light
Skeleton   HP 10   ATK 3   weakness: blunt
Stone Sentinel   HP 30   ATK 5   weakness: blunt
Wisp   HP 3   ATK 1   weakness: holy
Wraith   HP 14   ATK 4   weakness: holy
  (15 names, alphabetical ΓÇö std::map keeps them ordered)
> strike Goblin
  Struck 'Goblin' from the Hall of Names. (14 remain.)
> weakness fire
  5 monsters fear fire.
> recall Goblin
Goblin   HP 8   ATK 2   weakness: fire
  (recalled from the tree)
> benchmark names

-- The Hall of Names: linear scan vs BST vs std::map (1000 iterations per cell) --
  N=    100  query=last    linear=     3.520 us  BST=   0.353 us  std::map=   1.223 us  (tree height 13)
  N=    100  query=absent  linear=     3.774 us  BST=   0.520 us  std::map=   1.943 us  (tree height 13)
  N=   1000  query=last    linear=    36.338 us  BST=   1.015 us  std::map=   2.003 us  (tree height 22)
  N=   1000  query=absent  linear=    27.493 us  BST=   1.002 us  std::map=   1.975 us  (tree height 22)
  N=  10000  query=last    linear=   266.097 us  BST=   0.923 us  std::map=   2.144 us  (tree height 30)
  N=  10000  query=absent  linear=   223.107 us  BST=   0.885 us  std::map=   1.980 us  (tree height 30)
  N= 100000  query=last    linear=  3054.197 us  BST=   0.723 us  std::map=   2.868 us  (tree height 40)
  N= 100000  query=absent  linear=  2760.915 us  BST=   0.787 us  std::map=   2.967 us  (tree height 40)

std::map::find tracks the BST ΓÇö both grow with log N, both crush
the linear scan. The difference is the code: the BST was a class you
wrote across a whole floor; std::map was one declaration. And unlike
your plain BST, std::map is balanced (a red-black tree), so it NEVER
degenerates into a stick ΓÇö the library gives you the balanced tree of
Floor 9┬╜ and a key->value index on top of it, for free.

> quit
McCown notes your departure. "You leave in order."

2.
(a) byName_.count("Wisp") > 0;
(b) byName_.at("Wisp").attack; (after checking for Wisp above)
(c) weaknesses_.count("light") > 0;
(d) auto it = weaknessCounts_.find("holy");
    return it == weaknessCounts_.end() ? 0 : it->second;
std::set is for just a key, std:: map is for if you need a value assigned to that key.


3.
Just back in floor 9 and 9h, we built a BST by hand. This uses a self-sorting/balanced BST (black and red).
On the left side, find() would go to the right to find 'Z', a letter later in the alphabet. It wouldn't find
it over there, so it would just return null or false (which isn't true).

4.
It's shorter and quicker (and you don't have to write it yourself), but we lose the ability
to modify or change the insides ourselves. map::find is set and can't be edited.

5.
E0349 no operator "[]" matches these operands
C2678 binary'[': no operator found which takes a left-hand operand of type 'const
    std::map<std::string,int,std::less<std::string>,std::allocator<std::pair<const
    std::string,int>>>' (or there is no acceptable conversion)
(a) it inserts a new key with a zero and then returns a reference to it. (it messes
    up the map -> count would return a 1).
(b) countWeaknesses is a const function, but [] could modify the input. This means that
    the compiler doesn't even allow it to be used.

6.
Each view has its own container. strike removes the Goblin from our map, but it doesn't update
the floor 9 tree. It's just the same data stored in different places.

7.
The names command uses it (but it's technically not even IN registry). Nothing else does. The 
rest call for a key from the map, they don't actually go searching for the first letter of 
the string. It wouldn't be worth it, there's no need for it to be sorted.