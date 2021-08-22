/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
#include "helpers.h"
#include "shared.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#define LINELEN 80

#define expectedArgs 1
#define loadFileArgs 4

/**
 * modified clear_bufferText taken from a1 to handle input
 **/
static void clear_bufferText(void) {
    int ch;
    while (ch = getc(stdin), ch != '\n' && ch != EOF)
        ;
    clearerr(stdin);
}

/* function to check if args has taken correct input */

BOOLEAN argsChecker(int args) {
    if (args == expectedArgs || args == loadFileArgs) {
        return TRUE;
    } else {
        error_output("invalid args Provided\n");

        return FALSE;
    }
}

/* check if file has been opened correctly */

BOOLEAN openChecker(FILE** file) {
    if (*file == NULL) {
        perror("failed to open file");
        return FALSE;
    } else {
        return TRUE;
    }
}

/* check if 4th list input is correct */

BOOLEAN listChecker(char* argv) {
    int i;
    i = 0;

    while (argv[i]) {

        argv[i] = toupper(argv[i]);
        i++;
    }

    if (strcmp(argv, "LINKEDLIST") == 0 || strcmp(argv, "ARRAYLIST") == 0) {
        return TRUE;
    }
    error_output("incorrect list type\n");
    return FALSE;
}

/* check to see which list to run */

BOOLEAN whichList(char* argv) {

    if (strcmp(argv, "LINKEDLIST") == 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/* word only input chekcer*/

BOOLEAN removeWordInputChecker(char* input) {

    int number, punct, space, i;
    space = 0;
    punct = 0;
    number = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i]) != 0) {
            number++;
        }
        if (ispunct(input[i]) != 0) {
            punct++;
        }
        if (isspace(input[i]) != 0) {
            space++;
        }
    }
    if (number > 0 || punct > 0 || space > 0) {
        return FALSE;
    }

    return TRUE;
}

/* check text remove word menu */

BOOLEAN removeWordTextChecker(const char* word, char* input) {

    if (strcmp(word, input) == 0) {
        return TRUE;
    }
    return FALSE;
}

/* get input for the menu function */

BOOLEAN inputGetter(char* input) {
    int i;
    BOOLEAN checker;
    checker = FALSE;

    do {
        fgets(input, LINELEN, stdin);
        if (feof(stdin)) {
            return FALSE;
        }
        for (i = 0; i <= LINELEN; i++) {
            if (input[i] == '\n') {
                checker = TRUE;
                break;
            }
        }
        if (checker == FALSE) {
            error_output("Buffer overflow, please try again:");
            clear_bufferText();
        }
    } while (checker != TRUE);
    input[strlen(input) - 1] = '\0';

    return TRUE;
}

/* checker for menu_load_file listype */

int listTypeMenuChecker(char* input) {
    int i, valadator;
    BOOLEAN checker;
    BOOLEAN checkerTwo;
    BOOLEAN checkerThree;
    BOOLEAN checkerFour;

    do {
        checkerTwo = FALSE;
        checker = FALSE;
        checkerThree = FALSE;
        checkerFour = FALSE;
        if (checkerThree == FALSE) {
            do {
                fgets(input, fileInput, stdin);
                if (feof(stdin)) {
                    valadator = 3;
                    return valadator;
                }

                for (i = 0; i <= LINELEN; i++) {
                    if (input[i] == '\n') {
                        checkerFour = TRUE;
                        break;
                    }
                }
                if (checkerFour == FALSE) {
                    error_output("Buffer overflow, please try again:");
                    clear_bufferText();
                }
            } while (checkerFour != TRUE);
        }
        for (i = 0; i <= fileInput; i++) {
            input[i] = toupper(input[i]);
            if (input[i] == '\n') {
                input[strlen(input) - 1] = '\0';
                if (strlen(input) == 0) {
                    valadator = 3;
                    return valadator;
                }
                checker = TRUE;
                if (strcmp(input, "A") == 0) {
                    checkerTwo = TRUE;
                    valadator = 1;
                    return valadator;
                }
                if (strcmp(input, "L") == 0) {
                    checkerTwo = TRUE;
                    valadator = 2;
                    return valadator;
                }
            }
        }

        if (checker == FALSE) {
            error_output("Please Enter a or l:");
            checkerThree = TRUE;
            clear_bufferText();
        }
        if (checkerThree == FALSE) {
            error_output("please Enter a or l:");
        }

    } while ((checker != TRUE) || (checkerTwo != TRUE));

    return TRUE;
}

/*checker for most common word*/

BOOLEAN mostCommonWordChecker(char* input) {
    int alpha, punct, space, i;
    space = 0;
    punct = 0;
    alpha = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i]) != 0) {
            alpha++;
        }
        if (ispunct(input[i]) != 0) {
            punct++;
        }
        if (isspace(input[i]) != 0) {
            space++;
        }
    }
    if (alpha > 0 || punct > 0 || space > 0) {
        return FALSE;
    }

    return TRUE;
}

/**
 * convenience function for copying a string to another pointer
 **/
char* strdup(const char orig[]) {
    /* allocate the space for the copy */
    char* copy = (char*)malloc(strlen(orig) + 1);
    if (!copy) {
        perror("malloc");
        return NULL;
    }
    /* copy the string */
    strcpy(copy, orig);
    return copy;
}

/**
 *
 * you call printf. There is no difference in its use. Provided Paul Miller
 *A1
 **/
int normal_output(const char format[], ...) {
    int count = 0;
    va_list vlist;
    va_start(vlist, format);
    count += vprintf(format, vlist);
    va_end(vlist);
    return count;
}

/**
 * use this function to print out errors. We will test that you are
 *doing
 *separate output to stderr for errors. Provided Paul Miller A1
 **/
int error_output(const char format[], ...) {
    int count = 0;
    va_list vlist;
    va_start(vlist, format);
    count += fprintf(stderr, "Error: ");
    count += vfprintf(stderr, format, vlist);
    va_end(vlist);
    return count;
}
