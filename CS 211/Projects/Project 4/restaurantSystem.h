#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE = 0, TRUE = 1, NO = 0, YES} boolean;



typedef struct node{
	char *name;
	struct node *next;
	int status; // 0 if they are in restaurant, 1 if they are called in but not there
	int numBurger;
	int numSalad;
} ticketList;


//*****List of functions within each file******

//userFile.h
char *getName();
void clearToEoln();
void printCommands();
int getPosInt();
int getNextNWSChar();
//main is included in this function but it cannot be a function prototype

//queueFunctions.c
void doAdd(ticketList **hd);
void doCallAhead(ticketList **hd);
void doWaiting(ticketList **hd);
void doRetrieve(ticketList **hd);
void doList(ticketList **hd);
void doDisplay(ticketList **hd);
void doEstimateTime(ticketList** hd);

//supportFunctions.c
void addToList(ticketList** hd, char* nm, int stat, int nb,int ns);
int doesNameExist(ticketList** hd,char* nm);
void displayListInformation(ticketList** hd);
void displayOrdersAhead(ticketList** hd, int ahead);
void retrieveAndRemove(ticketList** hd, int nb, int ns);
int countOrdersAhead(ticketList **hd, char *name);
int updateStatus(ticketList** hd, char *name);
int totalBurgers(ticketList** hd, char* name);
int totalSalads(ticketList** hd, char* name);
void displayWaitingTime(ticketList** hd, char* name);


