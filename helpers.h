/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
#include "shared.h"
#include "stdio.h"
#ifndef HELPERS_H
#define HELPERS_H
#define fileInput 3
char* strdup(const char[]);

/**
 * the input and output functions
 **/
int normal_output(const char[], ...);

int error_output(const char[], ...);
BOOLEAN inputGetter(char* input);
BOOLEAN argsChecker(int args);

#endif
