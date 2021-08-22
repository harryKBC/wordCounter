/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/

#include "shared.h"
#include <stdio.h>
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct linked_node {
    /* the pointer to the next node */
    struct linked_node *next;
    /* the word we are storing */
    struct word theword;
};

struct linked_list {
    /* pointer to the beginning of the list */
    struct linked_node *head;
    /* pointer to the end of the list */
    struct linked_node *tail;
    /* how many words we have stored */
    long word_count;
};
struct linked_node *makeLinkedNode(void);
BOOLEAN intLinkedList(struct linked_list *list);
BOOLEAN addLinkedList(struct linked_list *list, char *word);
void freeMemoryLinkedList(struct linked_node *list);

#endif
