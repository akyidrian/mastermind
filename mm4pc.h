/* *********************************************** */
/* This is the header file for MM4PC.              */
/* Written by: Paul Bowler & Aydin Arik            */
/*						   */
/* Created for ENEL206 C Assignment 2010           */
/* Created: February 10, 2010                      */
/* Last edited: April 1st, 2010                    */
/* File: mm4pc.h                                   */
/* Purpose: Main header file for constants,        */
/*          function prototypes, etc.              */
/* *********************************************** */

/* libraries for printf, scanf, etc. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* constant definitions */
#define FALSE 0
#define TRUE (!FALSE)
#define MAX_PEGS 4
#define MAX_COLS 6
#define GUESS_SIZE 12
#define CODE_SIZE 10
#define HISTORY_LENGTH 73
#define VARIABLE_SIZE 7

/* type definitions */
typedef unsigned int Boolean;

/* function prototypes */
extern void do_bottom_border(void);
extern void do_top_border(void);
extern char check_word(char *element);
extern void search_colour_position (unsigned int *colour_and_position, char guessword_element, char codeword_element, char *code_position_count, char *guess_position_count);
extern void search_colour_only (unsigned int *colour_only, char *guessword_element, char *codeword_element, char colour_count_code[], char colour_count_guess[], int *index, char *code_position_count, char *guess_position_count);
extern void lookup (char *guessword_element);
extern void print_game(unsigned int *colour_and_position, char *game_history, unsigned int *colour_only);




