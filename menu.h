/******************************************************************************
 * Student Name    :Harrison Kinbacher
 * RMIT Student ID :s3559087
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 3, study period 2, 2020.
 *****************************************************************************/
#include "fileio.h"
#define LINELEN 80
#define sizeOfMenu 5
#define menuLine(length, char)         \
    {                                  \
        int i;                         \
        for (i = 0; i < length; ++i) { \
            putchar(char);             \
        }                              \
        putchar('\n');                 \
    }

/**
   * definition of a menu item as a pair of the menu text and a function pointer
   * that points to the implementation of that option.
   **/
struct menuitem {
    const char menu_text[LINELEN + 1];
    BOOLEAN (*function)(struct file_data*);
};

enum menuEnum {
    MNU_load,
    MNU_most_common,
    MNU_delete,
    MNU_save,
    MNU_quit
};
/**
 * functions implemented for the menu
 **/
void run_menu(void);
BOOLEAN menu_load_file(struct file_data*);
BOOLEAN menu_most_common(struct file_data*);
BOOLEAN menu_delete_word(struct file_data*);
BOOLEAN menu_save_stats(struct file_data*);
BOOLEAN menu_quit(struct file_data*);
