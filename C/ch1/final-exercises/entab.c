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
    int t_i = 0;                // text index.
    int c;                      // character input.

    int column = 1;             // column in the line. base 1.
    int last_char_col = 0;      // col corresponding to the last character in the line.
    int last_char_txt_id = 0;   // idx of the last character in text.
    int whiteSpaceCount = 0;    // amount of spaces of the last set of consecutive spaces.

    while ((c = getchar()) != EOF)
    {
        // If it's a space, check if we can trap a white space set and swap it by a tab.
        if (c == ' ')
        {
            ++whiteSpaceCount;

            // calculate spaces until next hop. starting from the last character placed.
            int currentTabBrack = (last_char_col / TAB_SIZE) + 1;
            int spacesUntilNextStop = (currentTabBrack * TAB_SIZE) - last_char_col;

            if (spacesUntilNextStop == whiteSpaceCount)
            {
                printf("\nfound %i consecutive spaces, let's change it by a tab. last_i: %i\n", whiteSpaceCount, last_char_col);

                // remove the last spaceCount white spaces.
                for (int i = 0; i < whiteSpaceCount; i++){
                    printf("from %s about to remove\n", text);
                    printf("removing character %i\n", t_i - i);
                    text[t_i - i] = '\0';
                }

                // reset consecutive white spaces to 0.
                whiteSpaceCount = 0;

                // insert a tab after the last character column.
                printf("inserting tab at %i\n", last_char_txt_id + 1);
                text[last_char_txt_id + 1] = '\t';
                
                // update text index.
                t_i = last_char_txt_id + 2;
            }
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
        printf("the next iteration will to %i\n", t_i);
    }

    text[t_i] = '\0';

    printf("result\n%s", text);
}
