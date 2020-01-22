//Dan Hrubec
//dhrube2
//CS 211
//project 5


#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>

#define TRUE 1
#define FALSE 0

extern int debugMode;

//All class definitions
class IntMyClass
{
  private:
  	int* dyarr;
  	int allocated;
  	int inUse;
  public:
	IntMyClass();
	void clear();
	int isEmpty();
	int top();
	void pop();
	void push(int val);
	void print(int iterator);
	int getLength();
  void freeArr();
};


class CharMyStack
{
  private:
  	char* darr;
  	int allocated;
  	int inUse;
  public:
  	CharMyStack();
  	void clear();
  	int isEmpty();
  	char top();
  	void pop();
  	void push(char val);
  	void test(int iterator);
  	int getLength();
    void freeArr();

};

enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

  public:
  	Token();
  	Token (TokenType t);
  	void setToType(TokenType t);
  	void setToOperator(char c);
  	void setToValue(int v);
  	bool equalsType(TokenType t);
    bool equalsOperator(char c);
    char getOperator ();
    int getValue();
};


class TokenReader
{
  private:
    char inputline[300];  // this assumes that all input lines are 300 characters or less in length
    bool needline;
    int pos;
  public:
  	TokenReader();
  	void clearToEoln();
  	Token getNextToken();
};


//All non class functions defined here
void processExpression (Token inputToken, TokenReader *tr);
void popAndEval(IntMyClass &intStack, CharMyStack &charStack);
int eval(int num1, char op, int num2);
void printCommands();
//main in the section as well, but cannot be a function prototype

