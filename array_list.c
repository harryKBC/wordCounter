/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
#include "array_list.h"
#include <stdlib.h>
#include <string.h>

/**
 * create appropriate functions for managing the array list here
 *
 *function to add word passed in to array

 function to remove word passed in from array


 *
 *
 *
 *
 **/

/* add to array function with dynamic memory allocation */

BOOLEAN addArray(struct array_list* list, char* word) {
    long i, x, j;
    char* wordSave;
    struct word* temp;

    /* check to see if there is enough room left in memory for values to be
     * saved */

    if (list->word_count == list->word_capacity) {
        struct word* tempRealloc;

        tempRealloc =
            realloc(list->words, (list->word_capacity + (MIN_ARRAY_SIZE)) *
                                     sizeof(struct word));
        list->words = tempRealloc;
        list->word_capacity = (list->word_capacity + MIN_ARRAY_SIZE);
        if (!list->words) {
            printf("memory allocation for array error");
            return FALSE;
        }
    }

    /*check to see if word is in array*/
    for (i = 0; i <= list->word_count - 1; i++) {

        if (list->words[i].text == NULL) {
            break;
        }
        if (strcmp(word, list->words[i].text) == 0) {
            list->words[i].count++;
            if (i != 0) {

                for (x = 0; x <= list->word_count; x++) {
                    for (j = 0; j <= list->word_count; j++) {
                        if (list->words[x].count > list->words[j].count) {
                            temp = (struct word*)calloc((ONE),
                                                        sizeof(struct word));

                            if (!temp) {
                                perror("memory allocation for array error");
                                return FALSE;
                            }

                            temp[0] = list->words[x];
                            list->words[x] = list->words[j];
                            list->words[j] = temp[0];
                            free(temp);
                        }
                    }
                }
            }

            return TRUE;
        }
    }

    /* copy new word to current array and increase the count of words in the
     * array */

    wordSave = (char*)calloc((strlen(word) + 1), sizeof(char*));
    strcpy(wordSave, word);
    list->words[list->word_count].text = wordSave;
    list->word_count++;

    return TRUE;
}

/*initialise array function */

BOOLEAN intArray(struct array_list* data) {
    data->word_count = 0;
    data->word_capacity = MIN_ARRAY_SIZE;
    data->words = (struct word*)calloc(MIN_ARRAY_SIZE, sizeof(struct word));

    if (!data) {
        perror("memory allocation for array error");
        return FALSE;
    }

    return TRUE;
}

/*free memory explicitly allocated */

void freeMemory(struct array_list* words) {
    int i;

    for (i = 0; i <= words->word_count; i++) {
        free((char*)words->words[i].text);
        words->words[i].count = 0;
    }
    words->word_count = 0;
    words->word_capacity = 0;

    free(words->words);
}
