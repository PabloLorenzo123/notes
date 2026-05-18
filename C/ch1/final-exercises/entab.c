// Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum
// number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.
// When either a tab or a single blank would suffice to reach a tab stop, which should be given
// preference?
#include <stdio.h>

#define TAB_SIZE 4
#define MAX_TEXT_LENGTH 1000

int main()
{
    char text[MAX_TEXT_LENGTH]; // holds the entire text.
    for (int i = 0; i < MAX_TEXT_LENGTH; i++) {text[i] = '\0';}
    int t_i = 0;                // text index.

    int last_char_col = 0;     // col corresponding to the last character (non space non newline) in the line.
    int last_char_txt_id = -1; // idx of the last character in text.
    
    int column = 1;            // column in the line. base 1.
    int whiteSpaceCount = 0;   // amount of spaces of the last set of consecutive spaces.

    int c; // character input.
    while ((c = getchar()) != EOF)
    {
        text[t_i] = c;
        // If it's a space, check if we can trap a white space set and swap it by a tab.
        if (c == ' ')
        {
            ++whiteSpaceCount;
            // calculate spaces until next hop. starting from the last character placed.
            int currentTabBrack = (last_char_col / TAB_SIZE) + 1;
            int spacesUntilNextStop = (currentTabBrack * TAB_SIZE) - last_char_col;

            if (spacesUntilNextStop == whiteSpaceCount)
            {
                // remove the last spaceCount white spaces.
                for (int i = 0; i < whiteSpaceCount; i++)
                {
                    text[t_i - i] = '\0';
                }

                // reset consecutive white spaces to 0.
                whiteSpaceCount = 0;
                // insert a tab after the last character column.
                text[last_char_txt_id + 1] = '-';

                // update text index.
                t_i = last_char_txt_id + 2;

                // update the last char column
                last_char_col = column - whiteSpaceCount;
                last_char_txt_id = last_char_txt_id + 1;
            }
            else
            {
                ++t_i;
            }
            ++column;
        }
        else if (c == '\n')
        {
            last_char_col = 0;
            last_char_txt_id = 0;
            whiteSpaceCount = 0;

            ++t_i;
            column = 1;
        }
        // if it's a normal character.
        else
        {
            last_char_col = column;
            last_char_txt_id = t_i;
            whiteSpaceCount = 0;

            ++t_i;
            ++column;
        }
        text[t_i] = '\0';
    }

    

    printf("result\n%s", text);
}
