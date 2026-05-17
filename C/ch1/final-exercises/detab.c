// Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number
// of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
// Should n be a variable or a symbolic parameter? 
#include <stdio.h>


#define TAB_SPACES 4
#define MAX_LINE_LENGTH 200

int main(){
    int c;  // current character.

    char answer[MAX_LINE_LENGTH]; // line without tabs.
    int column = 0;
    
    while (column < MAX_LINE_LENGTH - 1 && (c = getchar()) != EOF && c != '\n'){
        if (c == '\t'){
            int currentBracket = (column / TAB_SPACES) + 1;
            int spacesTillNextStop = (currentBracket * TAB_SPACES) - column;
            for (int k = 0; k < spacesTillNextStop && column < MAX_LINE_LENGTH - 1; k++){
                answer[column] = ' ';
                ++column;
            }
        }
        else {
            answer[column] = c;
            ++column;
        }
    }
    answer[column] = '\0';
    printf("\nYou typed:\n%s\n", answer);
    return 0;
}
