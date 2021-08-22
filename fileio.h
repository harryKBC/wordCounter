/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
#include "shared.h"
#include "linked_list.h"
#include "array_list.h"

#ifndef FILEIO_H
#define FILEIO_H
#define ONE 1

/**
 * the union of the two possible list types - only one can be used at a time
 **/
union list {
    struct linked_list linked_list;
    struct array_list array_list;
};

/**
 * enum for the possible types of list
 **/
enum list_type {
    LINKEDLIST,
    ARRAYLIST
};

/* enum to pull and save inputs from CMD line */
enum inputFileType {
    programCall,
    readFile,
    exitFile,
    list
};

/**
 * datastructure for managing the lists
 **/
struct file_data {
    /**
     * union of the two possible list types
     **/
    union list whichlist;
    /* enum that defines which kind of list we are using */
    enum list_type type;
    /* did the file load in a valid and complete way */
    BOOLEAN valid;
};

/**
 * function prototypes for this module
 **/
struct file_data load_file(const char[], enum list_type);
int normal_output(const char[], ...);
int error_output(const char[], ...);
BOOLEAN argsChecker(int args);
BOOLEAN openChecker(FILE** file);
BOOLEAN listChecker(char* argv);
BOOLEAN whichList(char* argv);
int listTypeMenuChecker(char* input);
BOOLEAN save_data(struct file_data*, const char[]);
BOOLEAN removeWordInputChecker(char* input);
BOOLEAN mostCommonWordChecker(char* input);
BOOLEAN removeWordTextChecker(const char* word, char* input);
#endif
