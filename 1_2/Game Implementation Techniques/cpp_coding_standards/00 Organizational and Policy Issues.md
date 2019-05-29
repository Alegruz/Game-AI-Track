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

## 004. Invest in code reviews.