  #include "mm4pc.h"

  /* ********************************************* */
  /* Mastermind game for PC 			   */
  /* Written by: Paul Bowler & Aydin Arik          */
  /*                                               */
  /* Created for ENEL206 C Assignment 2010         */
  /* Created: February 10, 2010                    */
  /* Last edited: April 1st, 2010                  */
  /* File: main.c                                  */
  /* ********************************************* */


  /* The "main" function which runs through each game of mastermind */ 
  int main (void)
  {
	    
      Boolean quit = FALSE; 		/* Boolean loop variable */
      
      int i,j;				/* Declare indexes */
      int turn;				/* Current turn */
      char fail_status = 0;		/* Fail status flag for check_word() NB: fail_status assumes zero when no failure */
      char guessword[CODE_SIZE]; 	/* This is the guessed codeword */
      char codeword[CODE_SIZE];		/* Codemaker's codeword */
      unsigned int colour_and_position;	/* This is the 1st column of output */
      unsigned int colour_only;		/* This is the second column of the output */
      char colour_count_code[VARIABLE_SIZE];		/* Array to count number of colours in codemaker word, so colour only return does not exceed individual number of colours */ 
      char colour_count_guess[VARIABLE_SIZE];		/* Array to compare iteratively to codemaker array in colour_only function */ 
      char game_history[HISTORY_LENGTH];		/* Game history array (of each turn in a game) */
      char num_of_players[VARIABLE_SIZE];		/* Variable to assertain single player/ two player mode */
      char code_position_count[VARIABLE_SIZE];		/* Arrays to recognise if a colour has already been counted in colour_and_position function, so it isn't counted TWICE in colour_only function */
      char guess_position_count[VARIABLE_SIZE];		/* "         "           "            "       " */
      int turn_history_address = 6;			/* The number of characters stored each iteration of the game */
      
    
    printf("\nPlease select the number of players playing...\n");
    do
    {
      printf("Enter \"1\" for one player, or \"2\" for two players.\n");
      printf("Players: ");
      fgets(num_of_players, VARIABLE_SIZE, stdin);
      fail_status = 0; /* Resetting fail_status if invalid player numbers is inputted */
      if (*num_of_players == '1')
      {
		/* The computers (the codemaker) turn */
		srand ( (unsigned)time(NULL) );	/* Our seed is the system time clock */

		/* Generating random numbers that correspond to colours in the codeword*/
		for (i=0; i <= 3 ;i++)
			{
			  codeword[i] = rand() % 6;
			}
      }
      else if (*num_of_players == '2')
      {
		/* Codemakers turn to start the game off */
		do
		{
			printf("\nCodemaker: Enter a 4-letter colour code without spaces,\n");
			printf("given: R=Red;  G=Green;  B=Blue;  C=Cyan  M=Magenta;  Y=Yellow\n");
			printf("e.g. \"RGBM\" (or 'Q' to Quit): ");
			fgets(codeword, CODE_SIZE, stdin); 
      
			if (codeword[0] == 'Q' || codeword[0] == 'q') 
			{
				quit = TRUE;
				fail_status = 0; /* Required for the situation where an invalid character is entered, then a "quit" command is issued */
			}
			else
			{
      
				for (i = 0; i <= 3; i++)		/* check_word function checks input string/word for valid characters and converts letters to corresponding numbers */
			{
				fail_status = check_word(&codeword[i]); 
				if (fail_status == 1)
				{
					break;
				}
			}
	
			}   
      
		}while(fail_status == 1);
	  }
      else
      {
		if (quit == 1)
		{
			break;
		}
		printf("\n\nPlease re-enter a valid number of players...\n");
		fail_status = 1;
      }
    }while(fail_status == 1); 
    
    
	printf("\033[2J"); /* Clears the terminal screen so the codebreaker can't cheat (using escape sequences) */
	printf("\033[0;0f"); /* Resets the cursor back to the original position (line 0,column 0) at the top left of the terminal window (using escape sequences) */
      
      
      /* Initialise all variables relating to this part of the game */
      turn = 1;			
      colour_and_position = 0;

      while (!quit && turn <= GUESS_SIZE)
      {
		printf("\nCodebreaker: Enter a 4-letter colour code without spaces,\n");
		if (turn == 1)			/* Only writes out the following once */
		{
			printf("given: R=Red;  G=Green;  B=Blue;  C=Cyan  M=Magenta;  Y=Yellow\n");	
		}
		printf("e.g. \"RGBM\" (or 'Q'to Quit): ");
		fgets(guessword, CODE_SIZE, stdin);	/* get guessword */
	  
		/* Lets allow the user to exit the program */
		if (guessword[0] == 'Q'|| guessword[0] == 'q')
		{
			printf("\nWinners never quit!! The codemakers code was: ");
			for (i = 0; i  <= 3; i++)
			{
				lookup(&codeword[i]); /* Consult lookup table function to print Codeword to screen */
			}
			printf("\n\n");
			break;
		}
		else 
		{
			/* Format output to begin new/next iteration of game */
			/* Reset variables for each iteration of the game */
			colour_and_position = 0; 
			colour_only = 0;
			for (i = 0; i<= 5; i++) /* Initialising the following arrays (i.e fill with zeros, at start of each iteration of the game) */
			{
				colour_count_code[i] = 0;
				colour_count_guess[i] = 0;
				code_position_count[i] = 0;
				guess_position_count[i] = 0;
			}
			/* Function used to process through array/strings to identify solutions */
			for (i = 0; i <= 3; i++)
			{
				fail_status = check_word(&guessword[i]); /* Validate string (check for legal characters) */
				search_colour_position(&colour_and_position, guessword[i], codeword[i], &(code_position_count[i]), &(guess_position_count[i])); /*function to locate colour AND position */
				if (fail_status == 1) 			 /* Illegal character(s), re-enter word string */
				{
					break;
				}
			}
			for (i = 0; i<=3; i++)
			{
				for (j = 0; j <= 3; j++)
				{
					search_colour_only(&colour_only, &guessword[i], &codeword[j], colour_count_code, colour_count_guess, &i, &(code_position_count[j]), &(guess_position_count[i])); /*function to find colour only! */
					
				}	
			}	
			
	    }
	        
	    
	    if (fail_status != 1) /* Stores and displays guessing information provided legal characters are entered */
	    {		
			/* Storing the history of the most recent turn into the game_history array */
			for (i = 0; i <= 5 ;i++)
			{
				if (i == 4)
				{
					game_history[i + turn_history_address * (turn - 1)] = colour_and_position; 
				}
				else if (i == 5)
				{
					game_history[i + turn_history_address * (turn - 1)] = colour_only;
				}
				else
				{
					game_history[i + turn_history_address * (turn - 1)] = guessword[i];
				}
			}
	      
	    
	  printf("\033[2J"); /* Clears the terminal screen so the codebreaker can't cheat (using escape sequences) */
	  printf("\033[0;0f"); /* Resets the cursor back to the original position (line 0,column 0) at the top left of the terminal window (using escape sequences) */


	    /*Outputing game interface*/
	    do_top_border();
	   
	    /* This process displays a history of game iterations to screen */
	    for (j = 1; j <= turn; j++)
			{
				printf("*"); /* Prints a "*", for the frame of the terminal display, before printing out the guessword */
				for (i = 0; i <= 5; i++)
				{
					if (i == 4)
					{
						colour_and_position = game_history[i + turn_history_address * (j - 1)];
					}
					else if (i == 5)
					{		
						colour_only = game_history[i + turn_history_address * (j - 1)];
					}
					else
					{
						lookup(&game_history[i + turn_history_address * (j - 1)]);
					}
				}
				printf("|   %d          %d  *\n", colour_and_position, colour_only);
			}
	    
	    do_bottom_border();  /* Finish off with a bottom border */
		
		
		
		
		/* If the codebreaker guesses the codeword, they win */
	       if (colour_and_position == MAX_PEGS)
	      {
				quit = TRUE;
				printf("\nYou win in %d moves!!\n\n", turn);
	      }		
	      
	      /* If the codebreaker fails to guess the codeword in the number of turns allowed, they lose */
	      else if (turn == GUESS_SIZE)
		  {
				quit = TRUE;
				printf("\nYou lose!! The codemakers code was: ");
				for (i = 0; i <= 3; i++)
				{
					lookup(&codeword[i]);
				}
				printf("\n\n");
		  }
		  else 
		  {
			turn += 1;
		  }
	    }/* if else ...*/
      } /* while (!quit ... */
      return 0;
  }/* end of game */
 
 
 /* Function used to validate characters entered by players, in a game */
char check_word(char *element) /* *element is a single character from guessword or codeword that is being validated and changed */   
{
     
     if (*element == 'm' ||*element == 'M')
     {
       *element = 0;
       return 0;
     }
     else if (*element == 'y' ||*element == 'Y')
     {
       *element = 1;
       return 0;
     }
     else if (*element == 'r' ||*element == 'R')
     {
       *element = 2;
       return 0;       
     }
     else if (*element == 'g' ||*element == 'G')
     {
       *element = 3;
       return 0;
     }
     else if (*element == 'b' ||*element == 'B')
     {
       *element = 4;
       return 0;
     }
     else if (*element == 'c' ||*element == 'C')
     {
       *element = 5;
       return 0;
     }
     else
     {
     printf("\nInvalid entry! Please re-enter valid word:\n");
     return 1;
     }
} 

/* Functions used to compare and count any matching colours, which are in the same positions, in the codeword and guesswords */
void search_colour_position (unsigned int *colour_and_position, char guessword_element, char codeword_element, char *code_position_count, char *guess_position_count)
{
  if (guessword_element == codeword_element)
  {
    *colour_and_position = *colour_and_position + 1;
    *code_position_count = 1;
    *guess_position_count = 1;
  }
}

/*Functions used to compare and count any matching colours (provided they haven't already been counted in the search_colour_position function) in the codeword and guessword */
void search_colour_only (unsigned int *colour_only, char *guessword_element, char *codeword_element, char colour_count_code[], char colour_count_guess[], int *index, char *code_position_count, char *guess_position_count) /* Note: Index is i from the main function */
{
  int which_colour;
  
  if (*codeword_element == 0)
  {
    if (*index == 0)
    {
      colour_count_code[0] = colour_count_code[0] + 1;
    }
    which_colour = 0;
  }
   if (*codeword_element == 1)
  {
    if (*index == 0)
    {
      colour_count_code[1] = colour_count_code[1] + 1;
    }
    which_colour = 1;
  }
   if (*codeword_element == 2)
  {
    if (*index == 0)
    {
      colour_count_code[2] = colour_count_code[2] + 1;
    }
    which_colour = 2;
  }
   if (*codeword_element == 3)
  {
    if (*index == 0)
    {
      colour_count_code[3] = colour_count_code[3] + 1;
    }
    which_colour = 3;
  }
   if (*codeword_element == 4)
  {
    if (*index == 0)
    {
      colour_count_code[4]= colour_count_code[4] + 1;
    }
    which_colour = 4;
  }
   if (*codeword_element == 5)
  {
   if (*index == 0)
    {
      colour_count_code[5] = colour_count_code[5] + 1;
    }
    which_colour = 5;
  }
  
  /* Compare elements of guessword and codeword, if they are same AND it hasn't already been counted before either in colour_and_position function or this one, increment counters */
  if (*guessword_element == *codeword_element)
  {
    if (colour_count_code[which_colour] > colour_count_guess[which_colour])
    {
      if (*code_position_count == 0 && *guess_position_count == 0)
      {
	*colour_only = *colour_only + 1;
	colour_count_guess[which_colour] = colour_count_guess[which_colour] + 1;
      }
    }
  }
}
