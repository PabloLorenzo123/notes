// Exercise 1-22. Write a program to ``fold'' long input lines into two or more shorter lines after
// the last non-blank character that occurs before the n-th column of input. Make sure your
// program does something intelligent with very long lines, and if there are no blanks or tabs
// before the specified column.
#include <stdio.h>

#define MAX_TEXT_LENGTH 100000
#define MAX_LINE_LENGTH 10
#define CLI_TAB_SIZE 4

void initializeString(char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        str[i] = '\0';
    }
}

int lineHasEmptyOrTab(char *str, int size)
{
    for (int i = size; i >= 0; i--)
    {
        if (str[i] == '\n')
        {
            return -1;
        }
        if (str[i] == ' ' || str[i] == '\t')
        {
            return i;
        }
    }
    return -1;
}

void moveCharsBy(char *str, int from, int until, int steps)
{
    while (steps > 0)
    {
        for (int i = until; i > from; i--)
        {
            if (i > 0)
            {
                int prev = str[i - 1];
                str[i] = prev;
            }
        }
        --steps;
    }

    for (int i = from; i <= until; i++) {
        if (str[i] == '\0'){
            str[i] = '@';
        }
    }
}

int main()
{
    char text[MAX_TEXT_LENGTH];              // text will be buffered up here.
    initializeString(text, MAX_TEXT_LENGTH); // Initialize text.

    int t_i = 0; // tracks the index of the last element in text.

    int columns = 0; // columns in the current line.

    int c;
    while ((c = getchar()) != EOF && t_i < MAX_TEXT_LENGTH)
    {
        text[t_i] = c;
        if (c == '\t')
        {
            columns += CLI_TAB_SIZE;
        }
        else if (c == '\n')
        {
            columns = 0;
        }
        else
        {
            columns++;
        }
        // fold
        if (columns > MAX_LINE_LENGTH)
        {
            // printf("need to fold the line\n");
            int foldIndex;
            if ((foldIndex = lineHasEmptyOrTab(text, t_i)) != -1)
            {
                // move all the characters starting from foldIndex a step to the right.
                moveCharsBy(text, foldIndex, t_i + 1, 1);
                text[foldIndex + 1] = '\n';
                t_i += 2; // one for the next position, and another for the shift to the right.
            }
            else // it's a continuous line.
            {
                int overflowedBy = columns - MAX_LINE_LENGTH;
                foldIndex = t_i - overflowedBy;
                moveCharsBy(
                    text,
                    foldIndex,
                    t_i + 2,
                    2 // one step for the hypen and another for the line break.
                );
                text[foldIndex + 1] = '-';
                text[foldIndex + 2] = '\n';
                t_i += 3; // one because of the hypen, another cause of the line break.
            }
            columns = 1;
            continue;
        }
        ++t_i;
    }

    printf("Result:\n%s.", text);
}
