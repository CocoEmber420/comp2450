1.
=== THE CISTERNS ===

What is your name, adventurer? Court

Welcome, Court.
Steward Quill sits behind a low ironwood desk in a soaked grey robe.
He does not look up. "Take your number. I will see you in order."
The line behind you stretches further than you can see.

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
   log [n]                       ΓÇö show the last n events, newest first
   log --oldest [n]              ΓÇö show the first n events, oldest first
   clone hero                    ΓÇö deep-copy the hero, print both logs, let the copy die
   selftest chain                ΓÇö Chain<T> leak + deep-copy harness
   selftest iterator             ΓÇö Chain<T>::iterator harness
   selftest stack                ΓÇö Stack<T> push/pop/top/LIFO harness
   selftest queue                ΓÇö Queue<T> enqueue/dequeue/front/FIFO harness
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   benchmark log [N]             ΓÇö race Chain::push_front vs vector insert(begin)
   battle warden                 ΓÇö face the Warden of the Foundations
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> selftest queue
  empty Queue<int>: size==0 && empty(): OK
  enqueue(7): size==1 && front()==7: OK
  enqueue 1,2,3: size==3 && front()==1 (FIFO): OK
  after dequeue(): size==2 && front()==2: OK
  drain to empty: size==0 && empty(): OK
  all phases OK
> potato A B C D E 3
  Survivor: D
> potato Grix Skrit Quill Vael Resh 2
  Survivor: Quill
> potato OnlyOne 7
  Survivor: OnlyOne
> provoke Wraith
  Wraith takes a number and joins the line.
> provoke Skeleton
  Skeleton takes a number and joins the line.
> provoke Witch
  Witch takes a number and joins the line.
> simulate
  Turn 1: Wraith stirs in the dark.
  Turn 2: Skeleton stirs in the dark.
  Turn 3: Witch stirs in the dark.
All enemies have acted; the line is empty.
> simulate
No enemies are in line.Use `provoke <name>` first.
> quit
Quill stamps your ticket. The line shuffles forward by one.

2.
Job	                                    Stack<T> calls…	        Queue<T> calls…
add an item (push / enqueue)	 	    push_front()            push_back()
remove an item (pop / dequeue)	 	    pop_front()             pop_front()
read the next item out (top / front)	head()->data            head()->data

A stack and a queue are different because a stack is LIFO, but a queue is FIFO
Queue uses a Chain<T> instead of a Bag<T> because Chain<T> has a better O for its worst case - O(1) vs O(n).
We don't want to have to shift everything in the Bag every time we push_front.

3.
> selftest queue
  empty Queue<int>: size==0 && empty(): OK
  enqueue(7): size==1 && front()==7: OK
  enqueue 1,2,3: size==3 && front()==1 (FIFO): FAIL ΓÇö front() did not return the FIRST enqueued value ΓÇö enqueue/front are on the same end (that's a stack, not a queue)
  after dequeue(): size==2 && front()==2: OK
  drain to empty: size==0 && empty(): OK
  (see FAILs above)
> potato A B C D E 3
  Survivor: A

We actually built a stack (LIFO) instead of a queue (FIFO). It enqueues 3 items (3, 2, 1 is the queue with Grix's 
shortcut), so when it dequeues the front, it still returns 2 with front().

4.
start:               A B C D
rotate (A to back):  B C D A
eliminate B:         C D A
rotate (C to back):  D A C
eliminate D:         A C
rotate (A to back):  C A
eliminate C:         A
SURVIVOR -> A

> potato A B C D 2
  Survivor: A

MATCHED!!!

5.
This time, I actually understood what we were doing by making functions using the chain functions as the base. It was
cool to see the different things we can do by overlaying queue or stack on something that already has functions for
us to use, since it can make it super simple when we are calling the specific queue and stack functions. It removed
the chance of a lot of errors with front and back.