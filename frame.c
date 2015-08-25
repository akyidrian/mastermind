#include "mm4pc.h"

  /* ********************************************* */
  /* A terminal display file for MM4PC.		   */
  /* Written by: Paul Bowler & Aydin Arik          */
  /*                                               */
  /* Created for ENEL206 C Assignment 2010         */
  /* Created: February 10, 2010                    */
  /* Last edited: April 1st, 2010                  */
  /* File: frame.c                                 */
  /* ********************************************* */


/* This function adds a top board to the mm4pc game  */
void do_top_border(void)
{
  printf("\n\n************************************************************\n");
  printf("* MM4PC Game      M=Magenta; Y=Yellow    | Colour   Colour *\n");
  printf("* R=Red; G=Green; B=Blue;    C=Cyan      | & Place    only *\n");
  printf("* -------------------------------------------------------- *\n");
}


/* This basic function adds a bottom board to the mm4pc game */
void do_bottom_border(void)
{
  printf("************************************************************\n");
}


/* Function used to convert and print the guesswords and the codeword (if required) for display in the terminal window */               
void lookup (char *guessword_element)
{
  if (*guessword_element == 0)
  {
    printf("  Magenta ");
  }
  else if (*guessword_element == 1)
  {
    printf("  Yellow  ");
  }
  else if (*guessword_element == 2)
  {
    printf("  Red     ");
  }
  else if (*guessword_element == 3)
  {
    printf("  Green   ");
  }
  else if (*guessword_element == 4)
  {
    printf("  Blue    ");
  }
  else if (*guessword_element == 5)
  {
    printf("  Cyan    ");
  }
}
