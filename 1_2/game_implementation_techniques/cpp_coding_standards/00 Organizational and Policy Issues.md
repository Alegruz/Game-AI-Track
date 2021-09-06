## 000. Don't sweat the small stuff. (Or: Know what not to standardize.)
### Summary
Say only what needs saying: Don't enforce personal tastes or obsolete practices.

### Discussion
Use a consistent format within each source file or even each project.<br>
* Indent to show structure.
* Keep line lengths readable.
* Use a consistent naming convention.
    * Never use "underhanded names".
        * Ones that begin with an underscore.
        * Ones that contain a double underscore.
    * Always use ONLY_UPPERCASE_NAMES for macros.
    * Suggestions:
        * Classes, Functions, enums: **LikeThis**
        * Varibles: **likeThis**
        * Private Member Variable: **likeThis_**
        * Macros: **LIKE_THIS**\
* Write useful comments (*except where tools extract certain styles into documentation*)

### Examples
* Brace placements
* Spaces vs Tabs
* Hungarian Notations
* Single entry, single exit (SESE)

## 001. Compile cleanly at high warning levels.
### Summary
Take warnings to heart: Use your compiler's highest warning level. Require clean
(warning-free) builds.<br>Understand all warnings. Eliminate warnings by changing
your code, not by reducing the warning level.

### Discussion

To get rid of a warning:
* understand it; and then
* rephrase your code to eliminate
the warning and make it clearer to both humans and compilers that the code does what you intended.

Do this even when the program seemed to run correctly in the first place. Do this even when you are positive that the warning is benign.

### Examples
* A third-party header file
* "Unused function parameter"
* "Variable defined but never used"
* "Variable may be used without being initialized." (see 019)
* "Missing return"
* "Signed/unsigned mismatch"

## 002. Use an automated build system.
### Summary
Push the (singular) button: Use a fully automatic ("one-action") build system that builds the whole project without user intervention.

### Discussion
You need a one-action build that is automated and dependable.

Successful builds should be silent, warning-free (see Item 1).<br>
The ideal build produces no noise and only one log message: **"Build succeeded."**

Have two build modes:
* Incremental: rebuilds only what has changed since the last incremental or full build.
    * Corollary: The second of two successive incremental builds should not write any output files; if it does, you probably have a dependency cycle (see Item 22), or your build system performs unnecessary operations (e.g., writes spurious temporary files just to discard them).
* Full: A project can have different forms of full build. Consider parameterizing your build by a number of essential features; likely candidates are target architecture, debug vs. release, and breadth (essential files vs. all files vs. full installer).

If you don't use one from the start, you will waste time and resources.

## 003. Use a version control system.

### Summary
The palest of ink is better than the best memory (Chinese proverb):<br>
> Use a **version control system (VCS)**. Never keep files checked out for long periods. Check in frequently after your updated unit tests pass. Ensure that checked-in code does not break the build.

### Discussion
A VCS automates and controls checkouts, versioning, and merging.<br>
A VCS will do it faster and more correctly than you could do it by hand.<br>
A VCS automatically tracks the history of each file and lets you "turn the clock back."<br>
Don't break the build. The code in the VCS must always build successfully.

### Exceptions
A project with one programmer that takes about a week from start to finish probably can live without a VCS.

## 004. Invest in code reviews.

### Summary
Re-view code:
> More eyes will help make more quality. Show your code, and read
others'. You'll all learn and benefit.

### Discussion
A good code review process benefits your team in many ways. It can:
* **Increase code quality** through beneficial peer pressure.
* **Find bugs, non-portable code (if applicable), and potential scaling problems.**
* **Foster better design and implementation** through cross-breeding of ideas.
* **Bring newer teammates and beginners up to speed.**
* **Develop common values and a sense of community** inside the team.
* **Increase meritocracy, confidence, motivation, and professional pride.**

Make code reviews a routine part of your software development cycle.<br>
If you agree with your teammates on a reward system based on incentives (and perhaps disincentives), so much the better.<br>
Without getting too formalistic, it's best to get code reviews in writing—a simple e-mail can suffice.<br>

When reviewing someone else's code, you might like to keep a checklist nearby for reference.<br>

In summary:
> We know we're preaching to the choir, but it had to be said.Your ego may hate a code review, but the little genius programmer inside of you loves it because it gets results and leads to better code and stronger applications.