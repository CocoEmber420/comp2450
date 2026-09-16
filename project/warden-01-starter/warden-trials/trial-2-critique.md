# Trial II — *The Critique*

*Warden of the Foundations · Midterm 1 · 15 %*

This trial **requires** you to use an LLM. You will paste the prompt and the reply, then critique what you got. Reading and judging AI output is part of the job now; we are practicing it on purpose.

---

## The prompt

Open Claude (or your LLM of choice) and paste **this exact prompt**:

> *Write a C++ function template that returns the largest element of a `std::vector<T>`. Handle the case where the vector is empty. Briefly explain your design choices.*

Tell us which tool you used and the date:

- **Tool: Claude Sonnet 5 - High**
- **Date of the conversation:** 2026-09-16

---

## The LLM's reply

Paste the **full reply**, code and prose. Use a fenced code block for the code. Do not edit the reply — we want to see what you actually got.

Solution:
```cpp
#include <vector>
#include <optional>
#include <algorithm>
#include <stdexcept>

template <typename T>
std::optional<T> max_element_value(const std::vector<T>& v) {
    if (v.empty()) {
        return std::nullopt;
    }
    return *std::max_element(v.begin(), v.end());
}
```
Usage:
```cpp
std::vector<int> nums = {3, 7, 2, 9, 4};
if (auto result = max_element_value(nums)) {
    std::cout << "Max: " << *result << '\n';
} else {
    std::cout << "Vector was empty\n";
}
```
"Design choices

Return type: std::optional<T> instead of throwing or returning a sentinel value.
An empty vector has no "largest element" — there's no valid T to return. Three common approaches exist:

Throw an exception (e.g. std::invalid_argument) — forces the caller into try/catch even when emptiness is an expected, recoverable case.
Return a sentinel (e.g. T{} or std::numeric_limits<T>::min()) — ambiguous, since that value might legitimately be in the vector, and 
doesn't work generically for arbitrary T.
Return std::optional<T> — makes "no answer" part of the type itself, forces the caller to explicitly handle the empty case (via if, .value_or(),
etc.), and works for any T without needing a magic sentinel.

std::optional is the modern (C++17+) idiomatic choice for "a value, or nothing."

Use std::max_element from <algorithm> rather than a hand-rolled loop.
It's a single, well-tested pass over the range, communicates intent clearly, and is exactly what the standard library is for. 
*std::max_element(...) dereferences the iterator it returns to get the value.

Requirement on T: the only constraint is that T be LessThanComparable (has operator<), since that's what std::max_element uses internally by default. 
No other requirements (no default constructor needed, unlike the sentinel approach) — this makes the template maximally generic.

Pass by const std::vector<T>&: avoids copying the vector; const signals the function doesn't modify it.

Alternative if you don't want <optional>: if your codebase prefers exceptions for invariant violations, swap the if (v.empty()) branch to throw 
std::invalid_argument("empty vector"); and change the return type to plain T. This is reasonable if callers can guarantee non-empty input and treat 
an empty vector as a programming error rather than a normal case."

---

## My critique  *( ≥ 150 words )*

Your critique must read like an engineer reviewing a colleague's pull request — specific, technical, and naming exactly what the LLM did. A vague critique ("looks fine to me, but it could be better") is *not* full credit even if the LLM's code was great.

Address each of these:

- **Compile.** Did you actually try to compile and run the code? On what types? What happened?
    - I did try to compile and run the code, and it worked exactly as expected. I noticed that this code only works with the newest version of C++17, 
      since my LLM decided to use <optional> instead of just throwing an exception. I originally tried to compile it on a not cmake project, and it
      wasn't able to. I believe that was because it wasn't running c++17, but it did start working once I switched out the <optional> for an exception
      statement. The program just found (and printed) the max value in a vector using the function template.
- **Empty case.** What does the empty-vector case actually do in this code? Is the LLM's choice reasonable? Is it different from what *you* would have chosen?
    - It immediately returns nullopt if the vector is empty. According to the LLM, "std::nullopt is a special constant that represents 'an optional 
      holding no value.'" I honestly have no clue what that means, but it seems like it's just 'nothing'. Like not even a nullptr? It is definitely
      not what I would have done, since I haven't learned how to use <optional>. I would throw an exception inside the if (v.empty()) instead
      of returning the nullopt. I have to assume the LLM's choice is reasonable because it ends the function immediately with a return, but I still
      think an exception would be a better idea.
- **Requirements on `T`.** What does the code require of `T`? What happens if you instantiate it with a type that doesn't support `<` (e.g., a custom struct)?
    - T needs to be 'LessThanComparable', so it needs to be able to use the < comparator. The code wouldn't compile, it spits out an ugly error message
      instead. I assume there's a way around it, but it would be entirely too complicated.
- **Const-correctness.** Pass by value or by reference? Return by value or by reference? Would you change either?
    - It passed by reference and returned by value. No, I wouldn't change it. The pass by reference is so that we don't unneccessarily copy the whole
      vector for no reason. The return by value is because there's nothing to reference by the time it gets to the main function. The value needs to 
      live past the rest of the template.
- **`std::max_element`?** Did the LLM cheat by using the algorithm header, or did it write the loop? Which would *you* have shipped, and why?
    - The LLM did 'cheat', it used std::max_element instead of writing the loop. I probably would have written it out, since I didn't know that 
      max_element existed. I'm sure that it's faster and safer, though, so it's probably better to use that.
- **One concrete improvement.** Name one specific change you would make before merging this into a real project. Not "make it better" — a concrete code change.
    - I would switch the <optional> to an exception. I feel like it's better to throw an exception so that we know what the problem actually is. I would
      change 'return nullopt' to something along the lines of 'throw std::invalid_argument("empty vector");'. I would also have to write a try{} catch(){}
      statement around the call in the main function as well.

(your critique — at least 150 words) --> whoops... sorry
