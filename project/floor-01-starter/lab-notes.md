1. Benchmark Output
-- Race the Bestiary (1000 iterations per cell) --
  N=     10  query=last    linear=     0.307 us  binary=   0.224 us  recursive=   0.172 us
  N=     10  query=absent  linear=     0.243 us  binary=   0.175 us  recursive=   0.182 us
  N=    100  query=last    linear=     2.888 us  binary=   0.366 us  recursive=   0.378 us
  N=    100  query=absent  linear=     3.167 us  binary=   0.541 us  recursive=   0.574 us
  N=   1000  query=last    linear=    34.758 us  binary=   0.696 us  recursive=   0.714 us
  N=   1000  query=absent  linear=    27.496 us  binary=   0.639 us  recursive=   0.682 us
  N=  10000  query=last    linear=   282.538 us  binary=   0.907 us  recursive=   0.870 us
  N=  10000  query=absent  linear=   222.819 us  binary=   0.682 us  recursive=   0.705 us
  N= 100000  query=last    linear=  2939.964 us  binary=   2.235 us  recursive=   0.965 us
  N= 100000  query=absent  linear=  2563.919 us  binary=   0.925 us  recursive=   0.978 us

Notice the curve: linear grows with N, binary grows with log N.
For tiny N the constants matter and the gap is small.
For large N the gap is enormous.

2. Binary starts to clearly beat linear around the 100 bestiary size.

3. Binary, it would seem like something that short wouldn't really matter.

4. It can't find Goblin, as the list is not in alphabetical order 
   (which means that the function is going to where it SHOULD be, but the name is not there)

5. They don't differ by much, but the binary is slightly faster. (like 0.1)
   The recursive has to call more functions and do just slightly more work.