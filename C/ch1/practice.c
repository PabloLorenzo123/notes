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
