/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 2, 2020.
 *****************************************************************************/
#include "fileio.h"
#include "menu.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* openFileName, *writeFileName;
    struct file_data testCollection;

    /* check the command line args */

    if (argsChecker(argc) != TRUE) {
        return EXIT_FAILURE;
    }
    if (argc == 4) {
        char* listType;
        listType = argv[list];
        openFileName = argv[readFile], writeFileName = argv[exitFile];
        if (listChecker(listType) == TRUE) {

            /*linked list functionality*/

            if (whichList(listType) == FALSE) {
                testCollection = load_file(openFileName, LINKEDLIST);
                if (testCollection.valid == FALSE) {
                    normal_output("\n\nFAILED\n\n");
                    freeMemoryLinkedList(
                        testCollection.whichlist.linked_list.head);
                    return EXIT_FAILURE;
                }
            }

            if (whichList(listType) == TRUE) {
                testCollection = load_file(openFileName, ARRAYLIST);
                if (testCollection.valid == FALSE) {
                    normal_output("\n\nFAILED\n\n");
                    freeMemory(&testCollection.whichlist.array_list);
                    return EXIT_FAILURE;
                }
            }

            /* open the file and check if it successfully opens saves data
 * to
 * array*/

            /*save data to file */

            if (save_data(&testCollection, writeFileName) != TRUE) {
                normal_output("\n\nFAILED\n\n");
                if (testCollection.type == ARRAYLIST) {
                    freeMemory(&testCollection.whichlist.array_list);
                    return EXIT_FAILURE;
                } else {
                    freeMemoryLinkedList(
                        testCollection.whichlist.linked_list.head);
                    return EXIT_FAILURE;
                }
            }

            /*final memory free cleaning up program*/

            if (testCollection.type == ARRAYLIST) {
                freeMemory(&testCollection.whichlist.array_list);
            }
            if (testCollection.type == LINKEDLIST) {
                freeMemoryLinkedList(testCollection.whichlist.linked_list.head);
            }
        }
        normal_output("\n\nSUCCESS\n\n");
        return EXIT_SUCCESS;
    }

    /* menu call */

    run_menu();

    normal_output("\n\nSUCCESS\n\n");

    return EXIT_SUCCESS;
}
