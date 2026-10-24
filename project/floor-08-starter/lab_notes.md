1.

=== THE HALL OF LINEAGES ===

What is your name, adventurer? Court

Welcome, Court.
Scrivener McCown looks up from a great branching chart that climbs the
wall like roots. "You found the Cisterns in order. Good. Order down
there was a line. Up here it branches." He taps the root of the chart.
"Every creature in the Hold hangs somewhere on this. Ask it questions."

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
   log [n]                       ΓÇö show the last n events, newest first
   log --oldest [n]              ΓÇö show the first n events, oldest first
   clone hero                    ΓÇö deep-copy the hero, print both logs, let the copy die
   selftest chain                ΓÇö Chain<T> leak + deep-copy harness
   selftest iterator             ΓÇö Chain<T>::iterator harness
   selftest stack                ΓÇö Stack<T> push/pop/top/LIFO harness
   selftest queue                ΓÇö Queue<T> enqueue/dequeue/front/FIFO harness
   selftest tree                 ΓÇö Tree<T> addChild/size/height/traversal/lineage harness
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   benchmark log [N]             ΓÇö race Chain::push_front vs vector insert(begin)
   battle warden                 ΓÇö face the Warden of the Foundations
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> selftest tree
  empty Tree<int>: empty() && size==0 && height==0: OK
  addChild: root==1 with 3 children: OK
  size()==7 over the sample tree: OK
  height()==2 (longest path 1->2->5): OK
  preOrder == {1,2,5,6,3,4,7} (depth-first): OK
  levelOrder == {1,2,3,4,5,6,7} (breadth-first): OK
  lineage(6)=={1,2,6} and lineage(404) empty: OK
  all phases OK
> taxonomy
Creatures of the Hold
    - Undead
        - Corporeal
            - Skeleton
            - Necrothrall
            - Lich
        - Incorporeal
            - Wraith
            - Wisp
    - Beasts
        - Mammals
            - Shadow Hound
            - Ironclaw Bear
            - Cinder Bat
        - Giants
            - Cave Troll
            - Frostmaw
    - Vermin
        - Bone Spider
        - Ratking
        - Marsh Lurker
    - Constructs
        - Stone Sentinel
  (23 creatures and categories; height 3)
> taxonomy --bfs
  breadth-first (level-order):
    Creatures of the Hold
    Undead
    Beasts
    Vermin
    Constructs
    Corporeal
    Incorporeal
    Mammals
    Giants
    Bone Spider
    Ratking
    Marsh Lurker
    Stone Sentinel
    Skeleton
    Necrothrall
    Lich
    Wraith
    Wisp
    Shadow Hound
    Ironclaw Bear
    Cinder Bat
    Cave Troll
    Frostmaw
> lineage Lich
  Creatures of the Hold > Undead > Corporeal > Lich
> lineage Wraith
  Creatures of the Hold > Undead > Incorporeal > Wraith
> lineage Cave Troll
  Creatures of the Hold > Beasts > Giants > Cave Troll
> lineage Beast
  'Beast' is not in McCown's catalogue.
> lineage Beasts
  Creatures of the Hold > Beasts
> quit
McCown notes your departure on the chart. "You leave classified."

2.
static void preOrderInto(const Node* n, std::vector<T>& out) {
        if (n == nullptr) {
            return;
        }
        out.push_back(n->data);
        for (std::size_t i = 0; i < n->children.size(); ++i) {
            preOrderInto(n->children[i], out);
        }
    }

static std::size_t heightFrom(const Node* n) {
        if (n == nullptr || n->children.size() == 0) {
            return 0;
        }
        std::size_t best = 0;
        for (std::size_t i = 0; i < n->children.size(); ++i) {
            best = std::max(best, heightFrom(n->children[i]));
        }
        return (1 + best);
    }

static std::size_t countFrom(const Node* n) {
        if (n == nullptr) {
            return 0;
        }
        std::size_t total = 1;
        for (std::size_t i = 0; i < n->children.size(); ++i) {
            total += countFrom(n->children[i]);
        }
        return total;
    }

The only thing that changed was what was returned at the end of the function. CountFrom sums 
them and adds 1, heightFrom takes the max and adds 1, and preOrderInto doesn’t combine return 
values at all, it just appends n->data to out before recursing.

3.
The node that moved the most between the two orders was 'Constructs'. It is at the bottom of the
--dfs, but it's at the top of the --bfs.

4.
I had to recompile/rebuild the whole project instead of just editing it. The error could easily 
stay there no matter how many times you edit it if you forget to recompile/build the project.

5.
> taxonomy --dfs
  depth-first (pre-order):
    Skeleton
    Necrothrall
    Lich
    Corporeal
    Wraith
    Wisp
    Incorporeal
    Undead
    Shadow Hound
    Ironclaw Bear
    Cinder Bat
    Mammals
    Cave Troll
    Frostmaw
    Giants
    Goblin
    Minions
    Beasts
    Bone Spider
    Ratking
    Marsh Lurker
    Vermin
    Stone Sentinel
    Constructs
    Creatures of the Hold

Because it pushes the node after the loop, it reverses the order of the list.
Instead of adding the new node as it is called, it adds it AFTER it goes through
all of the node's branches.

6.
25 nodes were visted to get to Stone Sentinel. You still have to search every node
in between the root and the leaf. It would need every node to have a max of two leaves
and for the whole tree to be sorted.

7.
It felt like we were actually building the tree from scratch instead of just renaming
the functions in Chain<> or Bag<>. Otherwise, it was pretty much the same -> creating
a data type in a .h file and then implementing the simpler functions in a .cpp. Also,
We created destructors and constructors like we did for the other containers.