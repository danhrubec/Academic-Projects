//Dan Hrubec
//dhrube2
//CS 211
//project 5

#include "project5Header.h"

int debugMode = FALSE;

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

int eval(int num1, char op, int num2)
{
	int result = 0;

	if(op == '*')
	{
		result = num1 * num2;
		if(debugMode == TRUE)
		{
			printf("\nEvaluting %d   %c   %d.\nResult:%d\n",num1,op,num2,result);
		}
		return result;
	}
	else if(op == '/')
	{
		result = num1 / num2;
		if(debugMode == TRUE)
		{
			printf("\nEvaluting %d   %c   %d.\nResult:%d\n",num1,op,num2,result);
		}
		return result;
	}
	else if(op == '+')
	{
		result = num1 + num2;
		if(debugMode == TRUE)
		{
			printf("\nEvaluting %d   %c   %d.\nResult:%d\n",num1,op,num2,result);
		}
		return result;
	}
	else if(op == '-')
	{
		result = num1 - num2;
		if(debugMode == TRUE)
		{
			printf("\nEvaluting %d   %c   %d.\nResult:%d\n",num1,op,num2,result);
		}
		return result;
	}
	else
	{
		//printf("Invalid operator detected.\n");
		//printf("Error operator:%c\n",op);
		return -999;

	}


}

void popAndEval(IntMyClass &intStack, CharMyStack &charStack)
{
	char op;
	op = charStack.top();
	charStack.pop();
	if(op == '(' || op == ')')
		return;

	int v2;
	v2 = intStack.top();

	intStack.pop();

	int v1;
	v1 = intStack.top();

	intStack.pop();

	int v3;
	v3 = eval(v1,op,v2);

	//printf("\nNum1:%d\tNum2:%d\tOP%c\n",v1,v2,op);

	intStack.push(v3);
}


void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
	IntMyClass intvals;
	CharMyStack charvals;
	
	
 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       /* make this a debugMode statement */
      	if(debugMode == TRUE)
		{
			printf ("Val: %d, ", inputToken.getValue() );

		}

       // add code to perform this operation here
       intvals.push(inputToken.getValue());
       

      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
    {
       /* make this a debugMode statement */
    	if(debugMode == TRUE)
		{
			printf ("OP: %c, ", inputToken.getOperator() );
		
		}
       

       // add code to perform this operation here
       if(inputToken.getOperator() == '(')
       {
       	charvals.push(inputToken.getOperator());
       }



       if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-');
       {

       		while(charvals.isEmpty() == FALSE && (charvals.top() == '-' || charvals.top() == '+' || charvals.top() == '*' || charvals.top() == '/'))
       		{
       			popAndEval(intvals,charvals);
       		}
       	charvals.push(inputToken.getOperator());
       }




       if((inputToken.getOperator() == '*' || inputToken.getOperator() == '/') && intvals.getLength() >=2)
       {
     	 while(charvals.isEmpty() == FALSE && (charvals.top() == '*' || charvals.top() == '/'))
     	 {
     	 	
     	 	popAndEval(intvals,charvals);

     	 }
     	 charvals.push(inputToken.getOperator());
       }
       if(inputToken.getOperator() == ')')
       {
       	 while(charvals.isEmpty() == FALSE && charvals.top() != '(')
       	 {
       		popAndEval(intvals,charvals);
       	 }
       	 if(charvals.isEmpty() == TRUE)
       	 {
       		printf("Error. Missing '('. Expression cannot be evaluated.\n");
       		return;
       	 } 
       	 else
       	 {
       		charvals.pop();
       	 }

       }

    }
    
    /* get next token from input */
    inputToken = tr->getNextToken ();
   }


 /* The expression has reached its end */
 // add code to perform this operation here



  while(charvals.isEmpty() == FALSE)
  {
  	popAndEval(intvals,charvals);

  }

  intvals.pop();

  if(intvals.isEmpty() ==FALSE)
  {
  	printf("\nError, invalid expression entered.\n");
  	return;
  }

  intvals.print(0);


 printf ("\n");
 charvals.clear();
 intvals.clear();

 charvals.freeArr();
 intvals.freeArr();

}



int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
	int q;
	for ( q = 0 ; q < argc ; q++ ) 
 	{
 		if (strcmp(argv[q], "-d") == 0 ) 
 			debugMode = TRUE;
	}

	if(debugMode == TRUE)
	{
		printf("\nEntering program in debugMode...\n");
	}

    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}



