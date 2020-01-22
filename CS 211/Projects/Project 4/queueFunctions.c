/* Functions in files
	doAdd()
	doCallAhead()
	doWaiting()
	doRetrieve()
	doList()
	doDisplay()
*/

#include "restaurantSystem.h"

extern debugMode;

void doAdd (ticketList** hd)
{
 /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

 printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);

 // add code to perform this operation here
 	if(doesNameExist(hd, name))
 	{
		printf("This name already has an order\n");
	}
 	//add to back of the list
	else
	{ 
		addToList(hd, name, 0, NumBurgers, NumSalads);
		return;
	} 

  if(debugMode == TRUE)
  {
    printf("List now becomes.\n");
    displayListInformation(hd);

  }

}


void doCallAhead (ticketList** hd)
{
   /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  


 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

 printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);

 // add code to perform this operation here
 if(doesNameExist(hd, name))
 	{
		printf("This name already has an order\n");
	}
 	//add to back of the list
	else
	{ 
		addToList(hd, name, 1, NumBurgers, NumSalads);
		return;
	} 

   if(debugMode == TRUE)
  {
    printf("List now becomes.\n");
    displayListInformation(hd);

  }
}

void doWaiting (ticketList** hd)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

 printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);

 // add code to perform this operation here
 if(!doesNameExist(hd, name)){ 
    if(debugMode == TRUE)
    {
      displayListInformation(hd);
   }
    printf("No ticket for given name\n");
    return;
  }
  if(updateStatus(hd, name) == FALSE){
    return;
  }
  else
  {
    updateStatus(hd, name);
    return;
  }

}

void doRetrieve (ticketList** hd)
{
 /* get info of prepared food ready on the counter from input */
 int PreparedBurgers = getPosInt();
 if (PreparedBurgers < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }

 int PreparedSalads = getPosInt();
 if (PreparedSalads < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }   

 clearToEoln();
 printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);

 // add code to perform this operation here
 retrieveAndRemove(hd,PreparedBurgers,PreparedSalads);
  if(debugMode == TRUE)
  {
    printf("Removing person from list...\n");
    displayListInformation(hd);

  }
}

void doList (ticketList** hd)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }

 printf ("Order for \"%s\" is behind the following orders\n", name);

 // add code to perform this operation here
	if(doesNameExist(hd, name)){
		printf("Number of groups ahead of \"%s\": %d\n", name, countOrdersAhead(hd, name));
		
		printf ("Group \"%s\" is behind the following groups\n", name);
		//list size of each group
		displayOrdersAhead(hd, countOrdersAhead(hd, name));
	}
 	//add to back of the list
	else{
		printf("Name does not exist in list\n");
	}
	


}
 
void doDisplay (ticketList **hd)
{
 clearToEoln();
 printf ("Display information about all orders\n");
 // add code to perform this operation here
 displayListInformation(hd);
}


void doEstimateTime(ticketList** hd)
{
  /* get order name from input */
 
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: t <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }


  // add code to perform this operation here  
  displayWaitingTime(hd,name);
}

