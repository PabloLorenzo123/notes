# The importance of the programming Language, C and its history.
When UNIX first camed around, it was written in Assembly language, Assembly language.

Note on Assembly:
Assembly language consists of mapping CPU instructions to words. CPU instructions will depend on the CPU Architecture or ISA (Instruction set architecture), most common examples are x86 (inspired by the intel ships that ended up with 86 in their names, Amd also copies this architecture and instructions) and ARM (snapdragon, and chip devices). Therefore Assembly language is dependent on the ISA, the Assembly language written for a x86 processor won't work on ARM processor.

By the same time UNIX was shipped along the C programming language, and its compiler. Universities and organizations received the UNIX OS and C compiler. later on, in the 1972 i think UNIX was rewritten in C, making it more portable. Why more portable? because now that the source code went from assembly to a higher level language such as C, the only thing needed to be change for UNIX to run on a different cpu architecture was just changing the C compiler, and not the entire source code. We can say that programming language offer a level of abstraction higher to assembly, that's why it's the final architecture level.

levels:
5 - Problem-oriented Language Level (C). Translation (Compiler).
4 - Assembly Language level (maps cpu instructions, to words). Translation (Assembler).
3 - Operating System Machine level. Partial interpretation (operating system). this one is kinda tricky because OS is written in Assembly or a problem oriented language.
2 - Instruction set architecture level. Interpretatrion (micropogram) or direct execution.
1 - Microarchitecture level.
0 - Digital logic.

# Important C concepts i overlooked.

- the #include <stdio.h> includes functions for input/output operations such as printf. stdio -> standard library i/o.
- The ANSI standard the American National Standards Institute, one of its standards defines a standard all C compiler must follow, so C code behave the same in different C compilers.

- string constants vs character constants, a character constant is a char wrapped by single quotes in operations its value represents the numerical value of the character in the machines character set for instance (utf-8). In expressions such as == a character constant is an integer. a string constant is an array of characters that end with a special null character '\0'.

## A confussion i had is how can char *argv[] hold strings
A confussion i had is how can char *argv[] hold strings? if this is an array of character pointers, and a string is an array of characters?
I thought it should be char[][] argv.

Doubt solved: each value is a pointer to a character. and a string value is really the initial pointer of the string.
A string is a continous (not necessarily saved in an array) set of characters in memory delimited by the null character \0.
If you want to know if the character you have is just a single character, or a character part of a string, add +1 to the memory location, if there's a character in there then likely is part of a string, and if you eventually find the \0 character just preceded by character values, it's a string.

```
#include <stdio.h>

void printString(char * startOfString){
    char * endOfString = startOfString;
    while (*endOfString != '\0'){
        // In reallity *endOfString is a numerical value.
        // the %s place holder, will match this numerical value to the machine's character set (UTF-8)
        // and prints its result in screen, even numbers have an entry in this set.
        printf("%c", *endOfString);
        endOfString = endOfString + 1;
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("usage .exe <string>.");
        return 1;
    }

    printString(argv[1]);
}
```

# Good to remember.
- The data types of `int` and `float` the amount of bits it uses will depend on the cpu architecture.
- a `parameter` is a variable defined in the parentheses of the function signature, and an argument is the value that's passed by a caller to a function.

- In C and most programming languages, all function arguments are passed ``by value``. This means that the called function is given the values of its arguments in temporary variables rather than the originals.
Call by value is an asset, howerver, not a liability. It usually leads to more compact programs with fewer extraneous variables, because parameters can be treated as conveniently initialized local variables in the called routine.
The story is different for arrays, when the name of an array is used as an arguemnt, the value passed to the function is the location or address of the beginning of the array - there is no copying of array elements.