#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void copy1(char *to, char from[]);
void exercise17();
void exercise18();
void reverse(char s[]);

/* print the longest input line */
int main()
{
    // exercise17();
    // int len;               /* current line length */
    // int max;               /* maximum length seen so far */
    // char line[MAXLINE];    /* current input line */
    // char longest[MAXLINE]; /* longest line saved here */
    // max = 0;
    // while ((len = getline(line, MAXLINE)) > 0)
    // {
    //     if (len > max)
    //     {
    //         max = len;
    //         copy(longest, line);
    //     }
    // }

    // if (max > 0) /* there was a line */
    //     printf("%s", longest);
    char str[] = "hello world!";
    reverse(str);
    printf("%s\n", str);
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
    }

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

//  Write a program to print all input lines that are longer than 80 characters.
void exercise17()
{
    int len;                    /* current line length. */
    char line[MAXLINE];         /* current input line. */
    
    int desiredLength = 80;
    char* lines[MAXLINE];       /* strings of the desired length. 
                                these are pointers because the start of the string is the address of the first character.
                                printf(%s) will increment the pointer address until it finds \0. */
    int i = 0;                  /** index of the last element in lines. */

    while ((len = getline(line, MAXLINE)) > 0)
    {
        if (len > desiredLength)
        {
            copy(lines[i], line);
            i++;
        }
    }

    // print all the lines
    printf("\nLines longer than %i, count: %i\n", desiredLength, i);
    for (int j = 0; j < i; j++){
        printf("%s\n", lines[j]);
    }
}

// returns string length, 0 if eof, and -1 if it's an empty line.
int getLine2(char s[], int sizeLimit) {
    int c, i, length;
    length = 0;
    
    for (i = 0; i < (sizeLimit - 1) && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
        if (c != ' ' && c != '\t'){
            length++;
        }
    }

    if (length == 0 && c == '\n'){
        return -1; // -1 means it's an empty line.
    }

    // if last character is a newline, add it.
    if (c == '\n'){
        s[i] = '\n';
        ++i;
    }

    // add the delimitir.
    s[i] = '\0';
    return length;
}

// Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input,
// and to delete entirely blank lines.
void exercise18()
{
    char line[MAXLINE];         /* current input line. */
    char* lines[MAXLINE];       /* strings of the desired length. 
                                these are pointers because the start of the string is the address of the first character.
                                printf(%s) will increment the pointer address until it finds \0. */
    int i = 0;                  /** index of the last element in lines. */
    int status;
    while ((status = getLine2(line, MAXLINE)) != 0)
    {
        if (status == -1) { // it's a new line.
            continue;
        }

        char trimmedLine[MAXLINE];

        int i1 = 0; // index of the last element in trimmedline.

        // clean trailing spaces and tabs from the start.
        int hasSentencedBegun = 0;
        for (int j = 0; j < MAXLINE; j++) {
            if (hasSentencedBegun == 1){
                trimmedLine[i1] = line[j];
                i1++;
                continue;
            }

            if (line[j] != '\t' && line[j] != ' ') {
                trimmedLine[i1] = line[j];
                i1++;
                hasSentencedBegun = 1;
            }
        }
        // clean trailing spaces and tabs from the end.
        int hasSentenceEnded = 0;
        while (hasSentenceEnded == 0){
            if (trimmedLine[i1] != '\t' && trimmedLine[i1] != ' ' && trimmedLine[i1] == '\0'){
                hasSentenceEnded = 1;
            }
            i1--;
        }
        printf("%p line address", trimmedLine);
        trimmedLine[i1] = '\0';
        lines[i] = trimmedLine;
        i++;
    }

    // print all the lines
    printf("\nLines without either trailing spaces or tabs.\n");
    for (int j = 0; j < i; j++){
        printf("%s", lines[j]);
    }
}

// Exercise 1-19. Write a function reverse(s) that reverses the character string s. Use it to
// write a program that reverses its input a line at a time. 
void reverse(char s[]){
    // Find length.
    int length;
    for (length = 0; length < MAXLINE; length++){
        if (s[length] == '\0') {break;}
    }
    // fill reversed string.
    char reversedStr[MAXLINE];
    int i = 0;
    for (int j = length - 1; j >= 0; j--){
        reversedStr[i] = s[j];
        i++;
    }

    for (int k = 0; k < length; k++){
        s[k] = reversedStr[k];
    }

    s[length + 1] = '\0';
}
