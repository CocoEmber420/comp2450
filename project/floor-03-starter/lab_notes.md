1. DEMO
> search Goblin
Goblin   HP 8   ATK 2   weakness: fire
> search Iron key
 Iron key  (wt 0.1, val 0)
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> inspect 3
  Iron key  (wt 0.1, val 0)
> inspect 99
No such item. (index 98 out of bounds for size 5)
> sort inventory by weight
   1.  Iron key          (wt 0.1, val 0)
   2.  Loaf of bread     (wt 0.1, val 1)
   3.  Healing potion    (wt 0.5, val 12)
   4.  Cloak of shadows  (wt 1.5, val 80)
   5.  Rusty sword       (wt 4.0, val 5)
> benchmark sort 10000
  N=  10000  mergeSort=  54.091 ms  quicksort=   41.718 ms  std::sort=  28.896 ms

  2. 
  FAILED: [code=2] CMakeFiles/the_descent.dir/main.cpp.obj 
  C:\PROGRA~1\MICROS~4\18\COMMUN~1\VC\Tools\MSVC\1451~1.362\bin\Hostx64\x64\cl.exe  /nologo /TP   /DWIN32 /D_WINDOWS /GR /EHsc /Zi /Ob0 /Od /RTC1 -std:c++17 -MDd /W4 /showIncludes /FoCMakeFiles\the_descent.dir\main.cpp.obj /FdCMakeFiles\the_descent.dir\ /FS -c C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-03-starter\main.cpp
C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-03-starter\main.cpp(77): warning C4189: 'found': local variable is initialized but not referenced
C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-03-starter\bestiary\Search.h(52): error C2228: left of '.name' must have class/struct/union
  C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-03-starter\bestiary/Search.h(52): note: type is 'const int'
  C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-03-starter\bestiary/Search.h(52): note: the template instantiation context (the oldest one first) is
  C:\Users\CocoEmber42\source\repos\CocoEmber420\comp2450\project\floor-03-starter\main.cpp(77): note: see reference to function template instantiation 'const T *dungeon::findByName<int>(const dungeon::Bag<T> &,const std::string &)' being compiled
          with
          [
              T=int
          ]
  ninja: build stopped: subcommand failed.

  line 29 is where the error really is --> an int doesn't have a 'name' in the class.
  It's harder to read beacuse of the cascading errors it causes because of the trail that the program has to follow to know why the function failed.
  Templates aren't checked when you write them, only when you actually put a certain type of data in them.

  3. 
  It popped up with a window saying "Debug Assertion Failed!" error. I looked it up, and this only happens because Visual Studio has a safety check in Debug mode.
  Not really, I'd only use [] over .at() if I checked separately that the index was okay. .at() does take more data to use, so if we were for sure that the index was safe it would be better to use [].

  4.
  With no try/catch, throwing the uncaught BagException didn't have a normal error message. I think it's another VS thing, but it shows an 'abort has been called' dialog and just exits with code 3.
  With an empty catch, it just moved past it like I didn't input anything at all. Now, it doesn't tell me WHY it messed up. In fact, I can't even see that an exception has been called.

  5.
  It all still compiles, it just throws an unhandled exception because normal std code can't catch it.
  Inheriting lets our custom exceptions be caught (yes I looked this up) and have it's message read with what() by any basic std code.