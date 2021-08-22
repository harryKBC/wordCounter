/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 3, study period 2, 2020.
 *****************************************************************************/
#include "menu.h"
#include "fileio.h"
#include "array_list.h"
#include "helpers.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

/**
 * Initalisee the menu with the correct strings and function pointers.
 * You must not stored the menu numbers and the structure should be
 * initialised in a maintainable way such that it will be relatively
 * easy to add menu items
 **/
void menu_init(struct menuitem menu[]) {

    int i;
    char* temp;
    char* menuOptions[] = {"load a file", "most common words", "delete word",
                           "save",        "quit"};

    for (i = 0; i <= sizeOfMenu - 1; i++) {

        temp = menuOptions[i];
        memcpy((char*)menu[MNU_load].menu_text, temp, strlen(temp) + 1);
        menu[MNU_load].function = &menu_load_file;

        if ((i = MNU_most_common)) {
            temp = menuOptions[i];
            memcpy((char*)menu[MNU_most_common].menu_text, temp,
                   strlen(temp) + 1);
            menu[MNU_most_common].function = &menu_most_common;
        }
        if ((i = MNU_delete)) {
            temp = menuOptions[i];
            memcpy((char*)menu[MNU_delete].menu_text, temp, strlen(temp) + 1);
            menu[MNU_delete].function = &menu_delete_word;
        }
        if ((i = MNU_save)) {
            temp = menuOptions[i];
            memcpy((char*)menu[MNU_save].menu_text, temp, strlen(temp) + 1);
            menu[MNU_save].function = &menu_save_stats;
        }
        if ((i = MNU_quit)) {
            temp = menuOptions[i];
            memcpy((char*)menu[MNU_quit].menu_text, temp, strlen(temp) + 1);
            menu[MNU_quit].function = &menu_quit;
        }
    }
}

/* this function kick starts the menu and contains the menu LOOP it does this
 * by calling the int menu function initialising the menu struct array and
 * taking the first round of user input*/

void run_menu(void) {
    long numberInput;
    int counter;
    char* ptr[LINELEN + EXTRACHARS];
    char input[LINELEN + EXTRACHARS];
    BOOLEAN checker;
    BOOLEAN checkerTwo;
    struct file_data thedata;
    struct menuitem menuItem[sizeOfMenu];
    int i;

    checker = FALSE;
    checkerTwo = FALSE;
    counter = 0;
    menu_init(menuItem);
    do {
        do {
            do {
                char* menuTitle = "data Structure Tester";
                normal_output("%s\n", menuTitle);
                menuLine(strlen(menuTitle), '=');
                for (i = 0; i <= sizeOfMenu - 1; i++) {

                    normal_output("%d) %s\n", i + 1, menuItem[i].menu_text);
                }
                normal_output("Please enter your choice: ");
                if (inputGetter(input) != TRUE) {
                    numberInput = MNU_quit + 1;
                    checkerTwo = TRUE;
                    checker = TRUE;
                };
                if (strlen(input) == 0) {
                    numberInput = MNU_quit + 1;
                    checkerTwo = TRUE;
                    checker = TRUE;
                } else {
                    checker = mostCommonWordChecker(input);
                    numberInput = strtol(input, &ptr[LINELEN], 10);
                    if (numberInput >= 1 && numberInput <= 5) {
                        checkerTwo = TRUE;
                    }
                }
            } while (checker == FALSE);
        } while (checkerTwo == FALSE);

        switch (numberInput - 1) {
            case MNU_load:
                if (counter > 0) {
                    normal_output("%s\n", menuItem[MNU_load].menu_text);
                    menuLine(strlen(menuItem[MNU_load].menu_text), '=');
                    menu_quit(&thedata);
                    if (menuItem[MNU_load].function(&thedata) == FALSE) {
                        numberInput = MNU_quit + 1;
                    }
                    break;
                }
                if (counter == 0) {
                    normal_output("%s\n", menuItem[MNU_load].menu_text);
                    menuLine(strlen(menuItem[MNU_load].menu_text), '=');
                    if (menuItem[MNU_load].function(&thedata) == FALSE) {
                        numberInput = MNU_quit + 1;
                    }
                }
                counter++;
                break;
            case MNU_most_common:
                if (counter > 0) {
                    normal_output("%s\n", menuItem[MNU_most_common].menu_text);
                    menuLine(strlen(menuItem[MNU_most_common].menu_text), '=');
                    if (menuItem[MNU_most_common].function(&thedata) == FALSE) {
                        menu_quit(&thedata);
                        numberInput = MNU_quit + 1;
                    };
                }
                break;

            case MNU_delete:
                if (counter > 0) {
                    normal_output("%s\n", menuItem[MNU_delete].menu_text);
                    menuLine(strlen(menuItem[MNU_delete].menu_text), '=');
                    if (menuItem[MNU_delete].function(&thedata) == FALSE) {
                        menu_quit(&thedata);
                        numberInput = MNU_quit + 1;
                    }
                }
                break;
            case MNU_save:
                if (counter > 0) {
                    normal_output("%s\n", menuItem[MNU_save].menu_text);
                    menuLine(strlen(menuItem[MNU_save].menu_text), '=');
                    if (menuItem[MNU_save].function(&thedata) == FALSE) {
                        menu_quit(&thedata);
                        numberInput = MNU_quit + 1;
                    }
                }
                break;
            case MNU_quit:
                if (counter > 0) {
                    menuItem[MNU_quit].function(&thedata);
                }
                break;
        }
        if (counter == 0 && numberInput != MNU_quit + 1) {
            error_output("please load a file\n\n");
        }
    } while (numberInput - 1 != MNU_quit);
}

/* this function loads the file you will be woking on in the menu, it gives
 * you the option to load the file in either an arraylist or linked list,
 * this function all handles all the user input for this section */

BOOLEAN menu_load_file(struct file_data* thedata) {
    clock_t start, end;
    double seconds;
    int listTypeValadator;

    char input[LINELEN + EXTRACHARS];
    char inputTwo[fileInput];
    do {
        listTypeValadator = 0;
        normal_output("Enter the path to the filename you want to load: ");
        if (inputGetter(input) != TRUE) {
            return FALSE;
        };
        if (strlen(input) == 0) {
            return FALSE;
        }
        normal_output(
            "Would you like to load this into an (a)rraylist or a "
            "(l)inkedlist?\n(Enter a or 1): ");

        listTypeValadator = listTypeMenuChecker(inputTwo);
        if (listTypeValadator == 3) {
            return FALSE;
        }
        start = clock();

        if (listTypeValadator == 1) {
            *thedata = load_file(input, ARRAYLIST);
            thedata->type = ARRAYLIST;
        }
        if (listTypeValadator == 2) {
            *thedata = load_file(input, LINKEDLIST);
            thedata->type = LINKEDLIST;
        };
        if (thedata->valid == FALSE) {
            error_output("Please try again error occured\n");
        }

        end = clock();
        seconds = ((double)end - start) / CLOCKS_PER_SEC;
    } while (thedata->valid != TRUE);

    normal_output("loading a file took %lf\n\n", seconds);

    return TRUE;
}

/**
 * this function retrieves the most common words from the list that are
 * specified by the user. It will then check to see which storage format the
 * user has saved the data in and display the list accordingly.
 **/
BOOLEAN menu_most_common(struct file_data* thedata) {

    int i, x;
    long numberInput;
    char input[LINELEN + EXTRACHARS];
    char* ptr[LINELEN + EXTRACHARS];
    struct linked_node* point;
    BOOLEAN checker;
    checker = FALSE;

    normal_output("Please enter how many items to display: ");
    i = 0;
    do {
        if (i > 0) {
            normal_output("Please enter a number: ");
        }

        if (inputGetter(input) != TRUE) {
            return FALSE;
        };
        if (strlen(input) == 0) {
            return FALSE;
        }

        checker = mostCommonWordChecker(input);
        i++;
    } while (checker == FALSE);

    numberInput = strtol(input, &ptr[LINELEN], 10);

    if (thedata->type == LINKEDLIST) {
        point = thedata->whichlist.linked_list.head;

        for (x = 0; x <= numberInput - 1; x++) {
            if (x > thedata->whichlist.linked_list.word_count) {
                normal_output("There are only %ld words in the list\n\n",
                              thedata->whichlist.linked_list.word_count + 1);
                break;
            }
            normal_output("%d) %s - %ld occurences\n", x + 1,
                          point->theword.text, point->theword.count + 1);
            point = point->next;
        }
    }
    if (thedata->type == ARRAYLIST) {

        for (x = 0; x <= numberInput - 1; x++) {
            if (x > thedata->whichlist.array_list.word_count - 1) {
                normal_output("There are only %ld words in the list\n\n",
                              thedata->whichlist.array_list.word_count);
                break;
            }
            normal_output("%d) %s - %ld occurences\n", x + 1,
                          thedata->whichlist.array_list.words[x].text,
                          thedata->whichlist.array_list.words[x].count + 1);
        }
    }

    return TRUE;
}

/* this function promps the user to enter any word, it then checks to see
if that word is in the list frist if it is, it will remove said word and update
thelist accordingly */

BOOLEAN menu_delete_word(struct file_data* thedata) {
    clock_t start, end;
    double seconds;
    int i, x, j;
    long occurencesLinkedList;
    struct linked_node* point;
    struct linked_node* pointTwo;
    struct linked_node* temp;
    struct word* tempTwo;
    char input[LINELEN + EXTRACHARS];
    BOOLEAN checker;
    BOOLEAN checkerTwo;
    checkerTwo = FALSE;
    checker = FALSE;

    normal_output("Please enter the word to delete: ");
    i = 0;
    do {
        if (i > 0) {
            error_output("Please enter the word to delete: ");
        }
        if (inputGetter(input) != TRUE) {
            return FALSE;
        };
        if (strlen(input) == 0) {
            return FALSE;
        }

        checker = removeWordInputChecker(input);
        i++;
    } while (checker == FALSE);
    start = clock();
    if (thedata->type == LINKEDLIST) {

        point = thedata->whichlist.linked_list.head;

        for (x = 0; x <= thedata->whichlist.linked_list.word_count; x++) {
            if (removeWordTextChecker(point->theword.text, input) == TRUE) {
                occurencesLinkedList = point->theword.count;
                thedata->whichlist.linked_list.word_count--;
                if (x == 0) {
                    temp = point;
                    thedata->whichlist.linked_list.head = point->next;
                    free((char*)temp->theword.text);
                    free(temp);
                    checkerTwo = TRUE;
                    break;
                }
                temp = point;
                point = point->next;
                free((char*)temp->theword.text);
                free(temp);
                checkerTwo = TRUE;
                break;
            }
            point = point->next;
        }
        pointTwo = thedata->whichlist.linked_list.head;
        for (j = 0; j < x; j++) {
            if (j == (x - 1)) {
                pointTwo->next = point;
                break;
            }
            pointTwo = pointTwo->next;
        }
        if (checkerTwo != TRUE) {
            error_output("%s : does not exist in the list of words\n", input);
        }
        if (checkerTwo != FALSE) {
            normal_output(
                "Sucessfully deleted %s from the Linked List - there was "
                "%ld occurences\n",
                input, occurencesLinkedList + 1);
        }
    }
    if (thedata->type == ARRAYLIST) {
        int i, x;

        for (i = 0; i <= thedata->whichlist.array_list.word_count - 1; i++) {
            if (removeWordTextChecker(
                    thedata->whichlist.array_list.words[i].text, input) ==
                TRUE) {
                occurencesLinkedList =
                    thedata->whichlist.array_list.words[i].count;

                tempTwo = (struct word*)malloc((1) * sizeof(struct word));
                tempTwo[0] = thedata->whichlist.array_list.words[i];
                free((char*)thedata->whichlist.array_list.words[i].text);

                for (x = i; x <= thedata->whichlist.array_list.word_count - 1;
                     x++) {

                    thedata->whichlist.array_list.words[x] =
                        thedata->whichlist.array_list.words[x + 1];
                }
                thedata->whichlist.array_list.word_count--;

                free(tempTwo);

                checkerTwo = TRUE;
                break;
            }
        }
        if (checkerTwo != TRUE) {

            error_output("%s : does not exist in the list of words\n", input);
        }
        if (checkerTwo != FALSE) {
            normal_output(
                "Sucessfully deleted %s from the Array List - there was "
                "%ld occurences\n",
                input, occurencesLinkedList + 1);
        }
    }
    end = clock();
    seconds = ((double)end - start) / CLOCKS_PER_SEC;

    normal_output("removing a word took %lf\n\n", seconds);

    return TRUE;
}

/* this function allows the user to save the list in a non directory file */

BOOLEAN menu_save_stats(struct file_data* thedata) {
    clock_t start, end;
    double seconds;
    char input[LINELEN + EXTRACHARS];
    normal_output("Enter the path to the filename you want to save: ");
    if (inputGetter(input) != TRUE) {
        return FALSE;
    };

    if (strlen(input) == 0) {
        return FALSE;
    }
    start = clock();

    if (thedata->type == ARRAYLIST) {
        save_data(thedata, input);
    }
    if (thedata->type == LINKEDLIST) {
        save_data(thedata, input);
    };

    end = clock();
    seconds = ((double)end - start) / CLOCKS_PER_SEC;

    normal_output("saving the file took:  %lf\n\n", seconds);

    return TRUE;
}

/**
 * this function quits the program and cleans up memory.
 **/
BOOLEAN menu_quit(struct file_data* thedata) {

    if (thedata->type == ARRAYLIST) {
        freeMemory(&thedata->whichlist.array_list);
    }
    if (thedata->type == LINKEDLIST) {
        freeMemoryLinkedList(thedata->whichlist.linked_list.head);
    };

    return FALSE;
}
