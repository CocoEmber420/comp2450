1. 
> benchmark sort

-- Race the Sorts (random input) --
  N=     10  mergeSort=   0.078 ms  quicksort=    0.025 ms  std::sort=   0.016 ms
  N=    100  mergeSort=   1.493 ms  quicksort=    0.389 ms  std::sort=   0.269 ms
  N=   1000  mergeSort=  23.096 ms  quicksort=    5.399 ms  std::sort=   4.810 ms
  N=  10000  mergeSort= 276.076 ms  quicksort=   79.103 ms  std::sort=  57.014 ms
  N= 100000  mergeSort=3344.547 ms  quicksort=  925.754 ms  std::sort= 827.834 ms

2. std::sort is DEFINITELY ahead at 10000.

3. quicksort and std::sort sped up, but merge sort slowed down. The others just
   compare numbers next to each other, but merge sort has to still split apart
   the whole list.

4. It is 0.014 with a bad pivot but 0.021 with the middle pivot.

5. I would choose std::sort to use if I had to choose one of the three. It is the quickest,
   it always has O(nlog(n)) for average and worst case. Quicksort can be O(n^2) in worst case,
   so that could be very bad. Merge sort never adapts, so it always takes the same time, even if
   the list is already nicely sorted. The std::sort is also already proofed and simple to use,
   so it should be optimized and debugged already.