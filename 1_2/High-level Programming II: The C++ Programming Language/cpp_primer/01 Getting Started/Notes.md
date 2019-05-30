# Note
Semicolons mark the end of most statements in C++.<br>
They are easy to overlook but, when forgotten, can lead to mysterious compiler error messages.

# Key Concept: Types
A type defines both the contents of a data element and the operations that are possible on those data.<br>
The data our programs manipulate are stored in variables and every variable has a type.

# Running the GNU or Microsoft Compilers
The most common compilers are the GNU compiler and the Microsoft Visual Studio compilers.<br>
By default, the command to run the GNU compiler is g++:<br>
```$ g++ -o prog1 prog1.cc```
<br>
Here `$` is the system prompt.<br>
The `-o prog1` is an argument to the compiler and names the file in which to put the executable file.<br>
This command generates an executable file named `prog1`.<br>
On UNIX, executable files have no suffix.<br>
If the `-o prog1` is omitted, the compiler generates an executable named `a.out` on UNIX systems.
<br>(Note: Depending on the release of the GNU compiler you are using, you may need to specify `-std=c++0x` to turn on C++ 11 support.)<br>
Compilers usually include options to generate warnings about problematic constructs.
<br>It is usually a good idea to use these options.
<br>Our preference is to use -Wall with the GNU compiler.<br>
For further information consult your compiler’s user’s guide.

# Warning
Programmers often add print statements during debugging.<br>
Such statements should always flush the stream.<br>
Otherwise, if the program crashes, output may be left in the buffer, leading to incorrect inferences about where the program crashed.

# Entering an End-of-File from the Keyboard
On Windows systems we enter an end-of-file by typing a **control-z—hold down the Ctrl key and press z—followed by hitting either the Enter or Return key.**<br>
On UNIX systems, including on Mac OS X machines, end-of-file is usually **control-d**.

# Compilation Revisited
Part of the compiler’s job is to look for errors in the program text.<br>
A compiler cannot detect whether a program does what its author intends, but it can detect errors in the form of the program.<br>
The following are the most common kinds of errors a compiler will detect.
* **Syntax errors**: The programmer has made a grammatical error in the C++ language. The following program illustrates common syntax errors;

        // error: missing ) in parameter list for main
        int main ( {
            // error: used colon, not a semicolon, after endl
            std::cout << "Read each file." << std::endl:
            // error: missing quotes around string literal
            std::cout << Update master. << std::endl;
            // error: second output operator is missing
            std::cout << "Write new master." std::endl;
            // error: missing ; on return statement
            return 0
        }

* **Type errors**: Each item of data in C++ has an associated type.
* **Declaration errors**: Every name used in a C++ program must be declared before it is used. Failure to declare a name usually results in an error message.
    * forgetting to use std:: for a name from the library
    * misspelling the name of an identifier
        ```
        #include <iostream>
        int main()
        {
            int v1 = 0, v2 = 0;
            std::cin >> v >> v2; // error: uses "v" not "v1"
            // error: cout not defined; should be std::cout
            cout << v1 + v2 << std::endl;
            return 0;
        }
        ```
Error messages usually contain a line number and a brief description of what the compiler believes we have done wrong.<br>
It is a good practice to correct errors in the sequence they are reported.<br>
It is also a good idea to recompile the code after each fix—or after making at most a small number of obvious fixes.<br>
This cycle is known as **edit-compile-debug**.

# Warning
It is a common mistake to write `=` when you mean `==` inside a condition.

# Key Concept: Indentation and Formatting of C++ Programs
* The only requirement is that the open curly must be the first nonblank, noncomment character following main’s parameter list.

* Our belief is that there is no single correct style but that there is value in **consistency**.

* When you choose a formatting style, think about how it affects readability and comprehension

* Once you’ve chosen a style, use it consistently.

# Key Concept: Classes Define Behavior
The class author determines all the operations that can be used on objects of the class type.

# Using File Redirection
Most operating systems support file redirection, which lets us associate a named file with the standard input and the standard output:
```
$ addItems <infile >outfile
```
This command will read transactions from a file named `infile` and write its output to a file named `outfile` in the current directory.