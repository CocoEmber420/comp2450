# AI Use Declaration — Warden of the Foundations

For each trial, write **one or two lines**: *which* tool, *what* you asked it for, *what* you did with the result. "Did not use" is a perfectly good entry — but the line must be there.

Example entries:

> *Trial I — used Claude to sanity-check my Big-O claim on Q2 after I wrote it; it agreed. Did not use it to write the answer.*
> *Trial III — used Copilot autocomplete on the menu printing function (one of the two functions I declared as written-without-AI is NOT this one). Wrote the turn-loop and the catch block by hand.*

---

## Trial I — The Foundations Brief

*Trial I — used Claude to double-check my Big-O claim on Q2 after I wrote it; it mostly agreed but caught one mistake... I hadn't noticed that the
	inventory was sorted by value instead of name, so binary wouldn't work at all. I didn't change the first part of my answer much, but I added
	the last sentences because of this.*
*Trial I - asked Claude to re-explain Lambda functions to me like a third grader because I never really took the time to understand them before. I
	used my understanding to write my answer, but I didn't check or do anything else with it.*

## Trial II — The Critique

This trial **requires** AI use. The full prompt + reply + critique are in `trial-2-critique.md`. If you used a different LLM for any other reason on this trial (e.g., to look up syntax), declare it here:

*Trial 2 - asked Claude to explain what <optional> was and why it used it, as well as what nullopt is. It affected my answer (I added quotes around its
	definition), but I honestly didn't gain much from it.*

## Trial III — The Encounter

*Trial 3 - asked Claude what to put into a cin.ignore(___, "\n") to ignore the string input. std::numeric_limits<std::streamsize>::max() was it's answer.
	I researched it some more, and it seemed like the normal way to do it, I had just forgotten. I used it on line 145.*

The two functions in your battle code that you wrote *without* AI assistance are named in `encounter-notes.md`. Friday's quiz pulls from those.
