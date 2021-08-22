/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
/**
 * This file
 **/
#ifndef SHARED_H
#define SHARED_H
/**
 * definition of the boolean type for you to use in your program
 **/
typedef enum truefalse {
    FALSE,
    TRUE
} BOOLEAN;

#define EXTRACHARS 2

#define PUNCTUATION "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define SPACES " \n\t\v\f\r"
#define NUMBERS "0123456789"

struct word {
    /* the string data for the word */
    const char* text;
    /* the length of the word, not counting the null terminator */
    long len;
    /* how many times this word has been seen */
    long count;
};
#endif
