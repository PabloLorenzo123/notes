#include <stdio.h>

#define LOWER   0       /* lower limit of table */
#define UPPER   300     /* upper limit */
#define STEP    20      /* step size*/

/** Exercise 1-3. */
void fahToCel() {
    printf("Fahrenheit to celsius table\n");
    int fah, cel;
    
    fah = LOWER;
    while (LOWER <= UPPER){
        cel = (5.0/9.0) * (fah-32.0);
        printf("%3.2f fahrenheit is %6.2f celsius\n", fah, cel);
        fah = fah + STEP;
    }
}

/** Exercise 1-4. */
void celToFah() {
    printf("Celsius to Fahrenheit table.\n");
    int fah, cel;
    
    cel = LOWER;
    while (LOWER <= UPPER){
        fah = cel * (5.0/9.0) + 32;
        printf("%3.2f celsius is %6.2f fahrenheit\n", fah, cel);
        cel = cel + STEP;
    }
}

/** Exercise 1-5. */
void celToFahInReverseOrder() {
    printf("Celsius to Fahrenheit table in reverse order.\n");
    for (float cel = UPPER; cel >= LOWER; cel = cel - STEP) {
        printf("%3.2f celius is %6.2f fahrenheit\n", cel, cel * (5.0/9.0) + 32);
    }
}

/** Exercise 1.6 */
void exercise6() {
    int c;
    while (c = getchar() != EOF){
        putchar(c); // Because we're not using parentheses such as (c = getchar() !+ EOF), c will be either 0 or 1.
    }
}

/** Exercise 7 */
void exercise7(){
    printf("%i\n", EOF);
}

/** Exercise 8: wirte a program to count blanks, tabns and newlines. */
void exercise8(){
    int c;
    long count;
    while ((c = getchar()) != EOF) {
        if (c == '\t' || ' ' || '\n'){
            count++;
        }
    }
    printf("blanks, tabs and newlines: %ld", count);
}

/** Exercise 9: Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank. */
void exercise9() {
    int prev = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ' && prev == ' '){
            continue;
        }
        putchar(c);
        prev = c;
    }
}

/** Exercise 10 Write a program to copy its input to its output, replacing each tab by \t, each
backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an
unambiguous way. */
void exercise10() {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            putchar('\\');
            putchar('t');
        }
        else if (c == '\b') {
            putchar('\\');
            putchar('b');
        }
        else if (c == '\\') {
            putchar('\\');
            putchar('\\');
        }
        else {
            putchar(c);
        }
    }
}

#define IN_WORD      0
#define OUT_WORD     1
// Exercise 1-12. Write a program that prints its input one word per line. 
void exercise12() {
    int state = OUT_WORD;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t'){
            if (state == IN_WORD){
                putchar('\n');
                state = OUT_WORD;
            }
        } else {
            putchar(c);
            state = IN_WORD;
        }
    }
}

// Exercise 1-13. Write a program to print a histogram of the lengths of words in its input. It is
// easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging. 
void exercise13() {
    // Initialize array, with 0 values.
    int wordLenghts[100];
    for (int i = 0; i < 100; i++) {
        wordLenghts[i] = 0;
    }

    // get user input and fill the array.
    int c;
    int currentWordLenght = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n'){
            if (currentWordLenght > 0){
                wordLenghts[currentWordLenght] = wordLenghts[currentWordLenght] + 1;
            }
            currentWordLenght = 0;
        }
        else {
            currentWordLenght++;
        }
    }

    if (currentWordLenght > 0){
        wordLenghts[currentWordLenght] = wordLenghts[currentWordLenght] + 1;
    }

    // Print histogram.
    printf("\nWord Count Historigram\n");
    for (int i = 0; i < 100; i++){
        int count = wordLenghts[i];
        if (count == 0){
            continue;
        }
        printf("%i | ", i);
        for (int j = 0; j < count; j++){
            printf("#");
        }
        printf("\n");
    }
}

// takes a string and converts it into a number.
int atoi(char* i) {
    int loops = 0;
    int value = 0;

    char* pointer = i;              // Initially points to the start of the string.
    while (*pointer != '\0'){       // loop until we reach the final of the string - reach null delimiter.
        int placeMultiplier = 1;
        for (int i = 0; i < loops; i++) {
            placeMultiplier = placeMultiplier * 10;
        }
        value = (value * placeMultiplier) + (*pointer - '0');
        pointer = pointer + 1;
        loops++;
    }

    return value;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage .exe <exercise_number>.\n");
        return 1;
    }
    int option = atoi(argv[1]);
    printf("you chose exercise %i\n", option);
    if (option == 1){
        fahToCel();
    }
    else if (option == 2){
        celToFah();
    }
    else if (option == 3){
        celToFahInReverseOrder();
    }
    else if (option == 6){
        exercise6();
    }
    else if (option == 7){
        exercise7();
    }
    else if (option == 8){
        exercise8();
    }
    else if (option == 9){
        exercise9();
    }
    else if (option == 13) {
        exercise13();
    }
    return 0;
}

