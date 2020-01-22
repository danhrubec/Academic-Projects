//Dan Hrubec
//dhrube2
//CS 211
//project 5


#include "project5Header.h"

//int stack class
IntMyClass::IntMyClass()
{
	if(debugMode == TRUE)
	{
		printf("Creating stack for the int values of expression...\n");
	}
  	allocated = 2;
  	inUse = 0;
  	dyarr = (int*) malloc (sizeof(int) * allocated);

}

void IntMyClass::clear()
{
  	free(dyarr);
  	allocated = 2;
  	inUse = 0;
  	dyarr = (int*) malloc (sizeof(int) * allocated);

}
int IntMyClass::isEmpty()
{
  if(inUse == 0)
  	return TRUE;
  else
  	return FALSE;

}

int IntMyClass::top()
{
  return dyarr[inUse - 1];
}


void IntMyClass::pop()
{
  	inUse = inUse - 1;

}

void IntMyClass::push(int val)
{
    if(inUse >= allocated)
  	{
  		int* temp = dyarr;
  		dyarr = (int*) malloc((allocated + 2) * sizeof(int));
  		int i;
  		for(i=0;i<allocated;i++)
  		{

  			dyarr[i] = temp[i];

  		}
  		free(temp);
  		allocated = allocated + 2;
  	}

    dyarr[inUse] = val;
  	inUse = inUse + 1;
}

void IntMyClass::print(int iterator)
{
  	printf("\nResulting Number:%d\n",dyarr[iterator]);

}
  
int IntMyClass::getLength()
{
  	return inUse;
}

void IntMyClass::freeArr()
{
	free(dyarr);

}


//Char Stack for operators
CharMyStack::CharMyStack()
{
	if(debugMode == TRUE)
	{
		printf("Creating stack for the operation chars of expression...\n");
	}
 allocated = 2;
 inUse = 0;
 darr = (char*) malloc (sizeof(char) * allocated);

}

void CharMyStack::clear()
{
  	free(darr);
  	allocated = 2;
  	inUse = 0;
  	darr = (char*) malloc (sizeof(char) * allocated);
}

int CharMyStack::isEmpty()
{
  	if(inUse == 0)
  		return TRUE;
  	else
  		return FALSE;

}

char CharMyStack::top()
{
  	return darr[inUse - 1];

}


void CharMyStack::pop()
{
  	inUse = inUse - 1;

}

void CharMyStack::push(char val)
{
  	if(inUse >= allocated)
  	{
  		char* temp = darr;
  		darr = (char*) malloc((allocated + 2) * sizeof(char));
  		int i;
  		for(i=0;i<allocated;i++)
  		{

  			darr[i] = temp[i];

  		}
  		free(temp);
  		allocated = allocated + 2;
    }

  	darr[inUse] = val;
  	inUse = inUse + 1;
}
  	
void CharMyStack::test(int iterator)
{
  	printf("Stack Value(char):%c\n\n",darr[iterator]);

}

int CharMyStack::getLength()
{

  	return inUse;
}

void CharMyStack::freeArr()
{
	free(darr);
}

//token class member function definition

  Token::Token()
  {
    type = ERROR;
    op = '$';
    val = -999;
  }

  // Initialize to a specific TokenType
  Token::Token (TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a specific TokenType
  void Token::setToType(TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a OPERATOR TokenType with specific operator value
  void Token::setToOperator(char c)
  {
    type = OPERATOR;
    op = c;
    val = -999;
  }

  // Set to a VALUE TokenType with a specific numeric value
  void Token::setToValue(int v)
  {
    type = VALUE;
    op = '$';
    val = v;
  }

  // return true if the Current Token is of the given TokenType
  bool Token::equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool Token::equalsOperator(char c)
  {
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
  }

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char Token::getOperator ()
  {
    if (type == OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
  }

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int Token::getValue()
  {
    if (type == VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
  }





 //Token reader member function definitions
  TokenReader::TokenReader()
  {
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
  }

  // Force the next getNextToken to read in a line of input
  void TokenReader::clearToEoln()
  {
    needline = true;
  }

  // Return the next Token from the input line
  Token TokenReader::getNextToken()
  {
    char* endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets ( inputline, 300, stdin);

      if (endCheck == NULL )
      {
        printf ("Error in reading");
        Token t(EOFILE);
        return t;
      }

      for (int i = 0 ; i < strlen(inputline) ; i++)
          if ('\n' == inputline[i])
              inputline[i] = ' ';
      strcat (inputline , " ");    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while ( pos < strlen(inputline) && isspace(inputline[pos]) )
    {
      pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos]; pos++;

    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return Token (QUIT);
    }

    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return Token (HELP);
    }

    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t;
      t.setToOperator( ch );
      return t;
    }

    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
      int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
      ch = inputline[pos]; pos++;
      while (isdigit(ch))
      {
        number = number * 10 + int (ch) - int('0');
        ch = inputline[pos]; pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t;
      t.setToValue( number );
      return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token (ERROR);
 }




