1.

=== THE HALVING HALL ===

What is your name, adventurer? Court

Welcome, Court.
Scrivener McCown stands before a tall, narrow chart where every name
forks just twice ΓÇö smaller to the left, larger to the right. "On the
last floor my tree remembered where things belonged," he says. "This
one remembers where they ARE. Ask it for a beast by name; watch it
throw away half the chart with every question."

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
   log [n]                       ΓÇö show the last n events, newest first
   log --oldest [n]              ΓÇö show the first n events, oldest first
   clone hero                    ΓÇö deep-copy the hero, print both logs, let the copy die
   selftest chain                ΓÇö Chain<T> leak + deep-copy harness
   selftest iterator             ΓÇö Chain<T>::iterator harness
   selftest stack                ΓÇö Stack<T> push/pop/top/LIFO harness
   selftest queue                ΓÇö Queue<T> enqueue/dequeue/front/FIFO harness
   selftest tree                 ΓÇö Tree<T> addChild/size/height/traversal/lineage harness
   selftest bst                  ΓÇö BST<T> insert/find/inorder/remove harness
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   benchmark log [N]             ΓÇö race Chain::push_front vs vector insert(begin)
   benchmark bst [N]             ΓÇö race linear scan vs BST lookup over the bestiary
   battle warden                 ΓÇö face the Warden of the Foundations
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> selftest bst
  empty BST<int>: empty() && size==0 && height==0: OK
  insert: root==5 and size==7 over the sample: OK
  contains: 7 and 2 present, 6 and 404 absent: OK
  inOrder == {2,3,4,5,7,8,9} (ascending): OK
  degenerate: sorted inserts give height==5, not balanced: OK
  deep copy: mutating the original leaves the copy unchanged: OK
  remove: leaf(2), one-child(3), two-children(5) all correct: OK
  all phases OK
> catalogue
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
  (15 creatures, alphabetical; tree height 6)
> recall Lich
Lich   HP 35   ATK 6   weakness: holy
  (recalled from the tree)
> recall Drake
  'Drake' is not in McCown's catalogue.
> forget Goblin
  McCown strikes 'Goblin' from the tree. (14 remain.)
> benchmark bst

-- Bestiary: linear scan vs BST lookup (1000 iterations per cell) --
  N=    100  query=last    linear=     2.846 us  BST=     0.362 us  (tree height 13)
  N=    100  query=absent  linear=     3.681 us  BST=     0.595 us  (tree height 13)
  N=   1000  query=last    linear=    31.735 us  BST=     0.819 us  (tree height 22)
  N=   1000  query=absent  linear=    22.637 us  BST=     0.874 us  (tree height 22)
  N=  10000  query=last    linear=   272.929 us  BST=     1.106 us  (tree height 30)
  N=  10000  query=absent  linear=   230.486 us  BST=     0.895 us  (tree height 30)
  N= 100000  query=last    linear=  3356.707 us  BST=     0.734 us  (tree height 40)
  N= 100000  query=absent  linear=  2417.756 us  BST=     0.733 us  (tree height 40)

Linear scan grows with N; BST lookup grows with log N ΓÇö the same
win binary search gave you on Floor 1, but now the structure STAYS
searchable as you insert and remove, with no re-sort step.
One catch: this tree was built from SHUFFLED data. Insert the
monsters already sorted and the BST degenerates into a stick
(height ~N), and lookup drops right back to linear ΓÇö the problem
the next floor's self-balancing tree exists to solve.

> quit
McCown notes your departure. "You leave in order."

2.
Find(7): 8 L 3 R 6 R 7 *FOUND*
Never looked at: 10, 14, 13, 1, 4
The number of nodes visited is at most (height + 1), so the find function is bounded by the height, not the number of nodes.

3.
1, 3, 4, 6, 7, 8, 10, 13, 14 -> ascending
Visiting the entire left subtree first, then the node, then the entire right subtree outputs all the smaller keys, then the node, then all the larger keys (in that order).
Recursively doing this inside each subtree means it's all sorted too.

4.
- delete 1 (leaf case)
- delete 10 (single-child case)
- delete 8 (two-child case) -> replace with seven (it's bigger than everything on the left and smaller than everything on the right).

5.
> benchmark bst

-- Bestiary: linear scan vs BST lookup (1000 iterations per cell) --
  N=    100  query=last    linear=     2.846 us  BST=     0.362 us  (tree height 13)
  N=    100  query=absent  linear=     3.681 us  BST=     0.595 us  (tree height 13)
  N=   1000  query=last    linear=    31.735 us  BST=     0.819 us  (tree height 22)
  N=   1000  query=absent  linear=    22.637 us  BST=     0.874 us  (tree height 22)
  N=  10000  query=last    linear=   272.929 us  BST=     1.106 us  (tree height 30)
  N=  10000  query=absent  linear=   230.486 us  BST=     0.895 us  (tree height 30)
  N= 100000  query=last    linear=  3356.707 us  BST=     0.734 us  (tree height 40)
  N= 100000  query=absent  linear=  2417.756 us  BST=     0.733 us  (tree height 40)

The height would be 13. Recall would slow down A LOT (especially if the key was later in the alphabet) -> O(logN) to O(N).

6.
In a normal Tree, a node’s position says nothing about its contents, so finding a key means visiting everything. In the BST, every comparison discards an entire subtree, which really
speeds it up. Remove stopped being a simple pointer splice. Deleting a node with two children means finding the successor, copying its key up, and then removing that node from its old 
spot. You also really have to pay attention to the sorted order. Second, the speed depends on the shape, not just the rule. Inserting in sorted order would turn the tree into a chain 
of height N-1 and make lookups O(N) (Like in the problem above). It felt way more complicated to write than it did when I just looked at it. I mean, it makes sense, but I thought it would
be more simple. I guess that is the point though: it makes it simple to just call the function of the BST than having to rewrite the code every time.