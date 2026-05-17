// Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum
// number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.
// When either a tab or a single blank would suffice to reach a tab stop, which should be given
// preference?
#include <stdio.h>

#define TAB_SIZE 4
#define LINE_LENGTH 1000

int main()
{
    char text[LINE_LENGTH]; // holds the current line.
    int c;                  // character input.

    int t_i = 0;             // text index.
    int column = 1;          // column in the line.
    int last_char_col = 0;   // idx of the last character in text.
    int whiteSpaceCount = 0; // amount of spaces of the last set of consecutive spaces.

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            ++whiteSpaceCount;
            // calculate spaces until next hop.
            int currentTabBrack = (column / TAB_SIZE);
            if (column % TAB_SIZE > 0) {
                ++currentTabBrack;
            }
            int spacesUntilNextStop = (currentTabBrack * TAB_SIZE) - last_char_col;

            if (spacesUntilNextStop == whiteSpaceCount)
            {
                printf("\nfound %i consecutive spaces, let's change it by a tab. last_i: %i\n", whiteSpaceCount, last_char_col);

                // remove the last spaceCount white spaces.
                int next = 0;
                int j = 0;
                while (text[t_i - j] == ' '){
                    text[t_i - j] = '\0';
                    j++;
                }

                // reset consecutive white spaces to 0.
                whiteSpaceCount = 0;

                // insert a tab after the last character column.
                int last_char_idx = t_i - whiteSpaceCount - 1;
                text[last_char_idx] = '-';
                // update text index.
                t_i = last_char_idx + 1;
                continue;
            }
        }
        else if (c == '\n')
        {
            last_char_col = 0;
            whiteSpaceCount = 0;
            column = 1;
        }
        else
        {
            last_char_col = column;
            whiteSpaceCount = 0;
            ++column;
        }
        ++t_i;
    }

    text[t_i] = '\0';

    printf("result\n%s", text);
}
