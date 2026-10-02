1.
> search Goblin
Goblin   HP 8   ATK 2   weakness: fire
  (found in bestiary)
> search Iron key
  Iron key  (wt 0.1, val 0)
  (found in inventory)
> search began
  began session as "Nameless One"
  (found in event log)
> log
   1.  search began ΓÇö found in event log
   2.  search Iron key ΓÇö found in inventory
   3.  search Goblin ΓÇö found in bestiary
   4.  began session as "Nameless One"
  (newest first; chain length 4)
> log --oldest 3
   1.  began session as "Nameless One"
   2.  search Goblin ΓÇö found in bestiary
   3.  search Iron key ΓÇö found in inventory
  (oldest first; chain length 4)
> selftest iterator
  range-for over Chain<int>: OK
  std::find(Chain<int>, 42): OK
  std::distance(begin, end): OK
  range-for over const Chain<int>&: OK
  std::reverse(Chain<int>) ΓÇö first now == 9: OK
  all phases OK
> quit
The lens dims. The lens does not remember what it saw ΓÇö only how it moved.

2.
> log
   1.  list ΓÇö bestiary printed
  (newest first; chain length 4)

3.
> search began
No such creature, item, or past event under that name.
> log
  (the chain is empty ΓÇö nothing to remember yet)
> log --oldest
  (the chain is empty ΓÇö nothing to remember yet)
end() equals begin() right away, so the range doesn't equal the size of the chain.

4.
[1/2] Building CXX object CMakeFiles\the_descent.dir\main.cpp.obj
  FAILED: [code=2] CMakeFiles/the_descent.dir/main.cpp.obj 
  C:\PROGRA~1\MICROS~4\18\COMMUN~1\VC\Tools\MSVC\1451~1.362\bin\Hostx64\x64\cl.exe  /nologo /TP   /DWIN32 /D_WINDOWS /GR /EHsc /Zi /Ob0 /Od /RTC1 -std:c++17 -MDd /W4 /showIncludes /FoCMakeFiles\the_descent.dir\main.cpp.obj /FdCMakeFiles\the_descent.dir\ /FS -c C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-05-starter\main.cpp
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\algorithm(9085): error C2676: binary '-': 'const _RanIt' does not define this operator or a conversion to a type acceptable to the predefined operator
          with
          [
              _RanIt=dungeon::Chain<int>::iterator
          ]
  C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\xutility(4711): note: could be 'unknown-type std::operator -(const std::move_iterator<_Iter> &,const std::move_iterator<_Iter2> &) noexcept(<expr>)'
  C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\algorithm(9085): note: 'unknown-type std::operator -(const std::move_iterator<_Iter> &,const std::move_iterator<_Iter2> &) noexcept(<expr>)': could not deduce template argument for 'const std::move_iterator<_Iter> &' from 'const _RanIt'
          with
          [
              _RanIt=dungeon::Chain<int>::iterator
          ]
  C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\xutility(2176): note: or       'unknown-type std::operator -(const std::reverse_iterator<_BidIt> &,const std::reverse_iterator<_BidIt2> &) noexcept(<expr>)'
  C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\algorithm(9085): note: 'unknown-type std::operator -(const std::reverse_iterator<_BidIt> &,const std::reverse_iterator<_BidIt2> &) noexcept(<expr>)': could not deduce template argument for 'const std::reverse_iterator<_BidIt> &' from 'const _RanIt'
          with
          [
              _RanIt=dungeon::Chain<int>::iterator
          ]
  C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\algorithm(9085): note: the template instantiation context (the oldest one first) is
  C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-05-starter\main.cpp(97): note: see reference to function template instantiation 'void std::sort<dungeon::Chain<int>::iterator>(const _RanIt,const _RanIt)' being compiled
          with
          [
              _RanIt=dungeon::Chain<int>::iterator
          ]
  C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\algorithm(9090): note: see reference to function template instantiation 'void std::sort<_RanIt,std::less<void>>(const _RanIt,const _RanIt,_Pr)' being compiled
          with
          [
              _RanIt=dungeon::Chain<int>::iterator,
              _Pr=std::less<void>
          ]
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\algorithm(9085): error C2672: 'std::_Sort_unchecked': no matching overloaded function found
  C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\algorithm(9051): note: could be 'void std::_Sort_unchecked(_RanIt,_RanIt,iterator_traits<_Iter>::difference_type,_Pr)'
  C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\algorithm(9085): note: 'void std::_Sort_unchecked(_RanIt,_RanIt,iterator_traits<_Iter>::difference_type,_Pr)': expects 4 arguments - 3 provided
  ninja: build stopped: subcommand failed.

Line 50 --> "error C2676: binary '-': 'const _RanIt' does not define this operator or a conversion 
              to a type acceptable to the predefined operator"
It needs the '-' operator to figure out distance. We have "--" and "++" to move one node at a time, but
we cannot add or subract iterators.

5.
The auto loop never explicitly states the container type, so it can be called with multiple different
types. With the spelled-out iterator type loop, you would have to make multiple different calls for 
every one of your container types and would need to edit all of them every time you need to change.

6. 
This gives every container the same interface for moving along the data (iterators) (++, --, ==/!=, *), so we don't
need to know the fine details with head_ and tail_ except for in the real iterator. The function now looks so
simple because we hide the chain and bag-specific stuff in their personal iterators that get called by the 
printLog function.