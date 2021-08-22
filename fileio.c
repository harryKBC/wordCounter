/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
#include "fileio.h"
#include "helpers.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/**
 * modified clear_buffer() function to work with file input
 **/
static void clear_buffer(FILE *fp) {
    int ch;
    while (ch = getc(fp), ch != '\n' && ch != EOF)
        ;
    clearerr(fp);
}

/**
 * loads the data into the appropriate list type according to the value
 * passed in.
 **/
struct file_data load_file(const char filename[], enum list_type type) {

    struct file_data data;
    int i;
    char line[BUFSIZ + EXTRACHARS];
    char *tokLine;
    FILE *fileRead;

    /* set values to arraylist */

    data.valid = TRUE;

    if (type == ARRAYLIST) {
        data.type = ARRAYLIST;
        if (intArray(&data.whichlist.array_list) != TRUE) {
            data.valid = FALSE;
            return data;
        }
    }
    if (type == LINKEDLIST) {
        data.type = LINKEDLIST;
        if (intLinkedList(&data.whichlist.linked_list) != TRUE) {
            data.valid = FALSE;
            return data;
        }
    }
    /* open the file inputed from user */

    fileRead = fopen(filename, "r+");
    if (openChecker(&fileRead) != TRUE) {
        data.valid = FALSE;
        return data;
    }

    /* loop though file and tokenize each line then add them to array */

    while (fgets(line, sizeof(line), fileRead) != NULL) {

        if (strlen(line) > BUFSIZ) {
            clear_buffer(fileRead);
            data.valid = FALSE;
            error_output("buffer overflow detected");
            return data;
        }

        tokLine = strtok(line, SPACES PUNCTUATION NUMBERS);

        for (i = 0; tokLine != NULL; i++) {
            if (tokLine == NULL) {
                return data;
            }

            /*linked list function here*/

            if (type == LINKEDLIST) {
                addLinkedList(&data.whichlist.linked_list, tokLine);
            }

            /* array function save in array_list.c here */
            if (type == ARRAYLIST) {

                if (addArray(&data.whichlist.array_list, tokLine) != TRUE) {
                    error_output("error saving word to array");
                    data.valid = FALSE;
                    return data;
                }
            }

            /* incremnet count */

            tokLine = strtok(NULL, SPACES PUNCTUATION NUMBERS);
        }
    }

    /*adjust values to allow the arrays to start at 1 instead of 0 */
    if (type == ARRAYLIST) {
        data.whichlist.array_list.word_count =
            data.whichlist.array_list.word_count;
    }
    if (type == LINKEDLIST) {
        data.whichlist.linked_list.word_count =
            data.whichlist.linked_list.word_count - ONE;
    }
    fclose(fileRead);

    return data;
}

/**
 * saves data from the current list type to the output file that was
 *specified
 * as part of the command line args.
 **/
BOOLEAN save_data(struct file_data *data, const char filename[]) {

    int i;

    /* open file then loop though contence using fprintf to print the values
     * to
     * said file then closing file*/

    FILE *fileWrite = fopen(filename, "w");
    if (openChecker(&fileWrite) != TRUE) {
        data->valid = FALSE;
        return FALSE;
    }

    if (data->type == LINKEDLIST) {
        struct linked_node *point;
        point = data->whichlist.linked_list.head;

        for (i = 0; i <= data->whichlist.linked_list.word_count; i++) {
            fprintf(fileWrite, "%s:%ld\n", point->theword.text,
                    point->theword.count + 1);
            point = point->next;
        }
    }

    if (data->type == ARRAYLIST) {

        for (i = 0; i <= data->whichlist.array_list.word_count; i++) {
            if (data->whichlist.array_list.words[i].text != NULL) {
                fprintf(fileWrite, "%s: %ld\n",
                        data->whichlist.array_list.words[i].text,
                        (data->whichlist.array_list.words[i].count + ONE));
            }
        }
    }
    fclose(fileWrite);

    return TRUE;
}
