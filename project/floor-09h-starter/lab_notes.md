1. 

=== THE BALANCED HALL ===

What is your name, adventurer? Court

Welcome, Court.
Scrivener McCown stands before the chart you filed for him last
floor, and it leans. He keeps reaching up to straighten a branch that
will not stay straight. "Every name is on the correct side," he says,
"and still it is slow. Order is not enough. Measure the lean with me,
then learn the one move that sets a branch level without moving a
single name out of its place."

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
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   benchmark log [N]             ΓÇö race Chain::push_front vs vector insert(begin)
   benchmark bst [N]             ΓÇö race linear scan vs BST lookup over the bestiary
   benchmark balance [N]         ΓÇö same sorted input: plain BST (stick) vs std::set
   battle warden                 ΓÇö face the Warden of the Foundations
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> selftest balance
  balanceFactor: empty==0, bushy==0, left-leaning==1: OK
  isBalanced: bushy {5,3,8,2,4,7,9} balanced (true): OK
  degenerate: sorted stick {1..6} is NOT balanced (height 5): OK
  rotate: rotateRootLeft on {1,2,3} -> root 2, height 1, order kept: OK
  balanceRoot: right- and left-heavy sticks both rebalance (order kept): OK
  all phases OK
> balance
  McCown's catalogue: 15 names, height 6, root balance factor -3 ΓÇö NOT balanced (lopsided).
> benchmark balance

-- Same sorted input: your plain BST vs std::set (1000 iterations per cell) --
  N=     10  plain BST: height=     9  find=    0.705 us    std::set: find=   0.917 us
  N=    100  plain BST: height=    99  find=    7.245 us    std::set: find=   1.371 us
  N=   1000  plain BST: height=   999  find=   83.308 us    std::set: find=   1.919 us

Same data, same order. Inserted in sorted order, your plain BST
degenerated into a stick of height N-1 ΓÇö lookup is back to O(n).
std::set saw the identical input and stayed shallow: it is a
balanced tree (a red-black tree) that rotates on every insert to
hold its height near log2 N. You do not hand-write that balancing ΓÇö
you reach for std::set / std::map. That is the next floor, the
Hall of Names.

> quit
McCown notes your departure. "You leave in order."

2. 
The height on the first tree is 6, but the height for the second tree is only 2.
This greatly decreases the search time in half, since every comparison removes half
of the tree from consideration.

3.
An in-order walk shows that the values are in correct BST order. As long as the in-order
matches the original, the rotation didn't break the BST (ie. it's still balanced).

4.
a) right rotation
b) left rotation
c) it is NOT balanced -> AVL tree would rotate twice (line and then root)

5.
> benchmark balance

-- Same sorted input: your plain BST vs std::set (1000 iterations per cell) --
  N=     10  plain BST: height=     9  find=    1.421 us    std::set: find=   1.197 us
  N=    100  plain BST: height=    99  find=   13.666 us    std::set: find=   3.693 us
  N=   1000  plain BST: height=   999  find=   98.433 us    std::set: find=   1.561 us

std::set balanced/rotated the tree with every insert, plain just kept adding them to the right side.

6.
I mean, it's just learning how the self-balancing tree works, we wouldn't have to code this
ourselves (the standard library has one of those I believe -> std::set??). I'd probably hand 
rotate it if was super important to have a different order or move extra data with the main 
nodes. Also, if I wasn't using the standard library (I think). Well we gain not having to write 
or debug our own code -> we just get to simply use the functions that are there. We lose some 
control over how it does things (even though the already written ones are probably optimized to
be fast). Also, it would feel strange to use something with no understanding on how it works.