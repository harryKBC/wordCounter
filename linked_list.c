/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
#include "linked_list.h"
#include "array_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* create list function */

struct linked_node *makeLinkedNode(void) {

    struct linked_node *linkedNode =
        (struct linked_node *)calloc(1, sizeof(struct linked_node));

    if (!linkedNode) {
        perror("malloc");
        return NULL;
    }

    return linkedNode;
}

BOOLEAN intLinkedList(struct linked_list *list) {

    /*list = (struct linked_list *)malloc(sizeof(struct linked_list));*/
    if (!list) {
        perror("list malloc failed");
        return FALSE;
    }

    list->word_count = 0;
    list->head = NULL;
    list->tail = NULL;

    return TRUE;
}

BOOLEAN addLinkedList(struct linked_list *list, char *word) {
    struct linked_node *point;
    struct linked_node *pointTwo;
    struct linked_node *pointThree;
    struct word temp;
    char *wordSave;
    struct linked_node *tempNode;
    int i, x, j;

    point = list->head;
    for (i = 0; i <= list->word_count - 1; i++) {
        if (point == NULL) {
            break;
        }
        if (strcmp(word, point->theword.text) == 0) {
            point->theword.count++;

            if (i != 0) {
                pointTwo = list->head;
                for (j = 0; j <= list->word_count - 1; j++) {
                    pointThree = list->head;
                    for (x = 0; x <= list->word_count - 1; x++) {
                        if (pointTwo->theword.count >
                            pointThree->theword.count) {

                            temp = pointTwo->theword;
                            pointTwo->theword = pointThree->theword;
                            pointThree->theword = temp;
                        }

                        pointThree = pointThree->next;
                    }
                    pointTwo = pointTwo->next;
                }
            }
            return TRUE;
        }

        point = point->next;
    }
    wordSave = (char *)calloc((strlen(word) + ONE), sizeof(char));
    tempNode = makeLinkedNode();
    strcpy(wordSave, word);
    tempNode->theword.text = wordSave;
    tempNode->next = NULL;

    if (list->head == NULL) {
        list->head = tempNode;
        list->tail = tempNode;
        list->word_count++;

    } else {
        list->tail->next = tempNode;
        list->tail = list->tail->next;
        list->word_count++;
    }

    return TRUE;
}

void freeMemoryLinkedList(struct linked_node *head) {

    struct linked_node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;

        temp->theword.count = 0;
        free((char *)temp->theword.text);
        free(temp);
    }
}
