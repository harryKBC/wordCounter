/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
#include "shared.h"
#include <stdio.h>
#ifndef ARRAY_LIST
#define ARRAY_LIST

#define MIN_ARRAY_SIZE 16
#define ONE 1

struct array_list {
    /* array of words */
    struct word* words;
    /* count of words currently stored */
    long word_count;
    /* total current capacity for the data structure */
    long word_capacity;
};

/**
 * insert function prototypes for managing the array list here.
 **/
BOOLEAN intArray(struct array_list* words);
void freeMemory(struct array_list* words);
BOOLEAN addArray(struct array_list* words, char* word);
#endif
