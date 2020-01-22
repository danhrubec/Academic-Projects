//Daniel Hrubec
//netID:dhrube2
//Programming Project 2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

int DebugMode;

/*
Struct with 3 members that will basically act as a make shift stack
Holds a location which is used for the array to access to current top
allocated is an int which is used when dynamically allocating memory
*/ 
typedef struct StackStruct
{
 char*    darr;  //pointer for the dynamo array
 int     allocated;  //amount of space needed to allocate
 int     location; //records the top of the stack
} Stack;

/*
Basic function. Called once only, just adds some starting values to the
members of a stack. Expects a pointer to a stack, and values are kept as a 
result of pass by reference
*/
void init (Stack* s)
{
 if(DebugMode == TRUE)
 	printf("Entering init function...\n");

 s->allocated= 2;
 s->darr = (char*) malloc ( sizeof (char) * s->allocated);
 s->location  = 0;

 if(DebugMode == TRUE)
 	printf("Exiting init...\n");
}

/*
Called during algorithm. Expects a value and a pointer to a stack. item added to array as a result
of pass by reference. Used when opening symbol is encountered. Stores it into the array, if
needed, allocates more memory.
*/
void push (Stack* s, char val)
{
	if(DebugMode == TRUE)
 		printf("Entering push function...\n");

  //checks to see if we out of space, adds more if we out
  if(s->location >= s->allocated)
  {
  	char*temp = s->darr;
  	s->darr = (char*) malloc (s->allocated * 2 * sizeof(char));
	int i;
  	for(i = 0; i < s->allocated;i++)
  	{
  		s->darr[i] = temp[i];
  	}
  	free(temp);
  	s->allocated = s->allocated + 2;
  	if(DebugMode == TRUE)
 		printf("Dynamic Memory Allocation for array complete...\n");

  }

  //adds the val parameter into the stack
  s->darr[s->location] = val;
  s->location = s->location + 1;
   	if(DebugMode == TRUE)
 		printf("Value added to array. Exiting push function...\n");
}


/*
Supporting function. Checks to see if the stack is empty, returns 1 if it is else it will return 0
*/

int isEmpty (Stack* s)
{
  if ( s->location == 0)
    return TRUE;
  else
    return FALSE;
}

/*
Standard function. Expects a pointer to a stack. Returns the value that is currently at the top of the stack
used during the algorithm
*/
char top (Stack* s)
{
  return (  s->darr[s->location -1] );
}

/*
Pop function, moves the current top down one. Used when a matching closing symbol and opening symbol
was encountered during the algorithm
*/
void pop (Stack* s)
{
  if(DebugMode == TRUE)
 	printf("Entering pop function...\n");
  s->location = s->location - 1;
  if(DebugMode == TRUE)
 	printf("Top moved down one. Pop function complete. Exiting...\n");

}

/*
Resets all their values back to their defaults.
*/
void clear(Stack* s)
{
  s->location = 0;
  free(s->darr);
  s->allocated= 2;
  s->darr = (char*) malloc ( sizeof (char) * s->allocated);
}

/*
Error code 1, during algorithm and a closing symbol is encounted. If the closing symbol does not match up 
with the opening symbol at the top, loop exists and this is called
*/
void error1(char symbol)
{
	printf("Expression exited with error code 1.\n");
	if(symbol == '[')
	{
		printf("The current expression is not balanced.\n");
		printf("The expression is not balanced because it is expected the closing symbol:%c\n", ']');
	}
	if(symbol == '{')
	{
		printf("The current expression is not balanced.\n");
		printf("The expression is not balanced because it is expected the closing symbol:%c\n", '}');
	}
	if(symbol == '<')
	{
		printf("The current expression is not balanced.\n");
		printf("The expression is not balanced because it is expected the closing symbol:%c\n", '>');
	}
	if(symbol == '(')
	{
		printf("The current expression is not balanced.\n");
		printf("The expression is not balanced because it is expected the closing symbol:%c\n", ')');
	}

}
/*
Error code 2, during algorithm and a closing symbol is encounted. If the closing symbol has no opening symbol 
whatsoever this is called.
*/

void error2(char symbol)
{
	printf("Expression exited with error code 2.\n");
 	printf("The current expression is not balanced.\n");
	printf("The expression is not balanced because it is expected the opening symbol:%c\n", symbol);

}

/*
Error code 3 function. This is called during the algorithm. At the end if there is still a leftover
opening symbol that has no matching closing that was read in, this error message will be called
*/
void error3(char symbol)
{
	printf("Expression exited with error code 3.\n");
	printf("The current expression is not balanced.\n");
	printf("The expression is not balanced because there is no closing for the symbol:%c\n",symbol);

}


int main (int argc, char** argv)
{

 char input[301]; // char array that holds all the input before putting the data in a struct
 int exitflag = 0; //if an error occurs during algorithm, indicates that it exited the loop

 //global variable, assigning default value to 0
 DebugMode = FALSE; 

 //data to check if -d was passed, it so then enters debugmode
 int q;
 for ( q = 0 ; q < argc ; q++ ) 
 {
 	if (strcmp(argv[q], "-d") == 0 ) 
 		DebugMode = TRUE;
 }
 
 //creating a stack and initializing it
 if(DebugMode == TRUE)
 	printf("Creating a stack.\n");

 Stack myStack;
 init(&myStack);

 //loop to prompt for inputs, exists when q is typed in
 while (1)
 {

   //gets the line of inputs and assigns it to the array
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   //removes the new line when entering data
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';


   //test to see if user wanted to exit the loop
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;
   printf ("%s\n", input);




  // loop for algorithm
   if(DebugMode == TRUE)
 		printf("Entering Loop to start algorithm...\n");
  int j;
  for(j = 0; j < i;j++)
  {

  	if(DebugMode == TRUE)
  		printf("Received input:%c\n",input[j]);

  	//If a closing symbol is read in, adds it to the stack.
  	if(input[j] == '[' || input[j] == '{' || input[j] == '<' || input[j] == '(')
  	{
  		 if(DebugMode == TRUE)
 			printf("Found an opening symbol...\n");
  		push(&myStack, input[j]);
  	}

  	//next bunch of ifs tests to see if a closing symbol was read in
  	//if it is, makes sure it has a matching opening else it exists with proper error code
  	if(input[j] == ']')
  	{
  		if(isEmpty(&myStack) == 1)
  		{
  			if(DebugMode == TRUE)
 				printf("Error 2 detected...\n");
  			error2('[');
  			j=i;
  			exitflag = 1;
  		}
  		else if(top(&myStack) == '[')
  		{
  			if(DebugMode == TRUE)
 				printf("Matching opening symbol found!\n");
  			pop(&myStack);
  		}
  		else
  		{
  			if(DebugMode == TRUE)
 				printf("Error 1 detected...\n");
  			error1(top(&myStack));
  			j=i;
  			exitflag = 1;
  		}

  	}

  	if(input[j] == '}')
  	{
  		if(isEmpty(&myStack) == 1)
  		{
  			if(DebugMode == TRUE)
 				printf("Error 2 detected...\n");
  			error2('{');
  			j=i;
  			exitflag = 1;
  		}
  		else if(top(&myStack) == '{')
  		{
  			if(DebugMode == TRUE)
 				printf("Matching opening symbol found!\n");
  			pop(&myStack);
  		}
  		else
  		{
  			if(DebugMode == TRUE)
 				printf("Error 1 detected...\n");
  			error1(top(&myStack));
  			j=i;
  			exitflag = 1;
  		}

  	}

  	if(input[j] == ')')
  	{
  		if(isEmpty(&myStack) == 1)
  		{
  			if(DebugMode == TRUE)
 				printf("Error 2 detected...\n");
  			error2('(');
  			j=i;
  			exitflag = 1;
  		}
  		else if(top(&myStack) == '(')
  		{
  			if(DebugMode == TRUE)
 				printf("Matching opening symbol found!\n");
  			pop(&myStack);
  		}
  		else
  		{
  			if(DebugMode == TRUE)
 				printf("Error 1 detected...\n");
  			error1(top(&myStack));
  			j=i;
  			exitflag = 1;
  		}

  	}

  	if(input[j] == '>')
  	{
  		if(isEmpty(&myStack) == 1)
  		{
  			if(DebugMode == TRUE)
 				printf("Error 2 detected...\n");
  			error2('<');
  			j=i;
  			exitflag = 1;
  		}
  		else if(top(&myStack) == '<')
  		{
  			if(DebugMode == TRUE)
 				printf("Matching opening symbol found!\n");
  			pop(&myStack);
  		}
  		else
  		{
  			if(DebugMode == TRUE)
 				printf("Error 1 detected...\n");
  			error1(top(&myStack));
  			j=i;
  			exitflag = 1;
  		}

  	}
	if(DebugMode == TRUE)
  		printf ("Loop counter:%d\n", j);

  

  }

  //after all data is read, checks to see if anything is left, if yes then error message
  //else the expression must be balanced
  if (isEmpty(&myStack) != 1 && exitflag == 0)
  {
  	error3(top(&myStack));
  }
  else if(exitflag == 0)
  {

  	printf("Expression is balanced\n");
  }

  //resetting variables
  clear(&myStack);
  exitflag = 0;
 }


 free(myStack.darr);
 printf ("\nGoodbye\n");
 return 0;
}
