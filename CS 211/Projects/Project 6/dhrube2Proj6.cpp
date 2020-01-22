//Dan Hrubec
//CS 211
//Project 6


#include "Island.h"


fnode::fnode(char* n)
{
	name = n;
}
char* fnode::getName()
{
	return name;
}

fnode* fnode::getNext()
{
	return next;
}

void fnode::setName(char* n)
{
	name = n;
}

void fnode::setNext(fnode* newnode)
{
	next = newnode;
}


fileNames::fileNames()
{
	head= NULL;
}

int fileNames::find(char* nm)
{
	fnode* temp = head;
	if(head == NULL)
	{
		return FALSE;
	}
	while(temp != NULL)
	{

		if(strcmp(temp->getName(),nm) == 0)
			return TRUE;

		temp = temp->getNext();
	}
	return FALSE;
}

int fileNames::isEmpty()
{
	if(head == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
	
void fileNames::pop(char* nm)
{

	fnode* temp = head;
	fnode* prev = temp;
	if(this->isEmpty() == TRUE)
	{
		printf("error. cannot pop front empty stack.\n");
		return;
	}
		
	//testing the front of the linked list
	if(temp->getName() == nm)
	{
		head = head->getNext();
		delete temp;
		return;
	}

	while(temp->getNext() != NULL)
	{
		if(temp->getName() == nm)
		{
			prev->setNext(temp->getNext());
			temp->setNext(NULL);
			delete temp;
			return;
		}
		prev = temp;
		temp = temp->getNext();
	}

	if(temp->getName() == nm)
	{
		prev->setNext(NULL);
		delete temp;
		return;
	}
		
	printf("error. could not find value in stack\n");
	return;
}
	
void fileNames::push(char* nm)
{
	//printList();
	fnode* tmp = new fnode(nm);
	tmp->setNext(head);
	head = tmp;
	//printList();

}

void fileNames::printList()
{	
	fnode* temp = head;
	if(this->isEmpty() == TRUE)
		printf("List empty.\n");

	while(temp != NULL)
	{
		printf("\t%s, ", temp->getName());
		temp = temp->getNext();

	}
	printf("\n\n");
}



Node::Node(int elem, bool vis)
{
	element = elem;
	visited = vis;

}

int Node::getElem()
{
	return element;
}

Node* Node::getNext()
{
	return next;
}

bool Node::getVisited()
{
	return visited;
}

void Node::setElem(int val)
{
	element = val;

}

void Node::setVisited(bool vis)
{
	visited = vis;
}

void Node::setNext(Node* newnode)
{
	next = newnode;

}


 ArchipelagoExpedition::ArchipelagoExpedition()
 {
  length = 10;
  linkedLists = new Island[10];
  
 }
  

  
 // The main loop for reading in input
 void ArchipelagoExpedition::processCommandLoop (FILE* inFile)
 {
  char  buffer[300];
  char* input;

  input = fgets ( buffer, 300, inFile );   // get a line of input
    
  // loop until all lines are read from the input
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \n\t");

    printf ("*%s*\n", command);
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "q") == 0)
    {
      freeTrip(); 
      exit(1);
  }
     
    else if ( strcmp (command, "?") == 0) 
      showCommands();
     
    else if ( strcmp (command, "t") == 0) 
      doTravel();
     
    else if ( strcmp (command, "r") == 0) 
      doResize();

    else if ( strcmp (command, "i") == 0) 
      doInsert();

    else if ( strcmp (command, "d") == 0) 
      doDelete();

    else if ( strcmp (command, "l") == 0) 
      doList();

    else if ( strcmp (command, "f") == 0) 
      doFile();

    else if ( strcmp (command, "#") == 0) 
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
 }
 void ArchipelagoExpedition::depthFirstSearchHelper(int x,int y)
 {
 	int i;
 	for(i = 0;i < length; i++)
 	{
 		linkedLists[i].reset();
 	}

 	if(dfs(x,y) == TRUE)
 		printf("You can get from Island:%d to Island:%d in 1+ ferry rides.\n", x,y);
 	else
 		printf("You cannot get from Island:%d to Island:%d in 1+ ferry rides.\n", x,y);
 }

 bool ArchipelagoExpedition::dfs(int a, int b)
 {
 	Node* c = linkedLists[a-1].listHead();

 	if(c == NULL)
 			return false;

 	while(c != NULL)
 	{
 		if(c->getElem() == b)
 				return true;

 		if(c->getVisited() == false)
 		{
 			c->setVisited(true);

 			if(dfs(c->getElem(), b) == true)
 				return true;
 		}

 		c = c->getNext();
 	}

 	return false;

 }



 
 void ArchipelagoExpedition::showCommands()
 {
   printf ("The commands for this project are:\n");
   printf ("  q \n");
   printf ("  ? \n");
   printf ("  # \n");
   printf ("  t <int1> <int2> \n");
   printf ("  r <int> \n");
   printf ("  i <int1> <int2> \n");
   printf ("  d <int1> <int2> \n");
   printf ("  l \n");
   printf ("  f <filename> \n");
 }
 
 void ArchipelagoExpedition::doTravel()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   
   printf ("Performing the Travel Command from %d to %d\n", 
            val1, val2);

   depthFirstSearchHelper(val1,val2);
   
 }
 
 void ArchipelagoExpedition::doResize()
 {
   int val1 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   printf ("Performing the Resize Command with %d\n", val1 );
  
   freeTrip();
   length = val1;
   length++; //adding an extra so i dont have to convert 0 to 1 and what not

   Island* temp = new Island[length];
   
   linkedLists = temp;
 }
 
 void ArchipelagoExpedition::doInsert()
 {

   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   if( val1 + 1 > length || val2+1 > length)
   {
   	printf("Error. Island does not exist.\n");
   	return;

   }

   if(linkedLists[val1-1].find(val2) == TRUE)
   {
   	printf("Cannot add ferry ride that already exists.\n");
   	return;
   }

   linkedLists[val1-1].push(val2,false);

   printf ("Performing the insert command from %d to %d\n", 
            val1, val2);
 }
 
 void ArchipelagoExpedition::doDelete()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   

   if(linkedLists[val1-1].find(val2) == TRUE)
   {
  	linkedLists[val1-1].pop(val2);
   	printf("Island found. Deleting link between island:%d and island:%d\n", val1,val2);
   }
   else
   {
   	printf("No edge found between island:%d and island:%d.\n", val1,val2);
   }
 }
 
 void ArchipelagoExpedition::doList()
 {
   int i;
   for(i = 0; i < length - 1;i++)
   {
   	printf("Island:%d ", i + 1);
   	linkedLists[i].printList();

   }
 }
 
 void ArchipelagoExpedition::doFile()
 {
   // get a filename from the input
   char* fname = strtok (NULL, " \n\t");
   if ( fname == NULL )
   {
     printf ("Filename expected\n");
     return;
   }
   
   printf ("Performing the File command with file: %s\n", fname);

   if(fns.find(fname) == TRUE)
   {
   	printf("already exists.\n");
   	return;
   }
   else
   {
   	fns.push(fname);
   	fns.printList();
   }
  
   
   // next steps:  (if any step fails: print an error message and return ) 
   //  1. verify the file name is not currently in use

   
   //  2. open the file using fopen creating a new instance of FILE*
   FILE* pFile;
   pFile = fopen(fname,"r");
   if(pFile == NULL)
   {
   	printf("File is empty. Exiting.\n");
   	return;
   }

   //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter

   this->processCommandLoop(pFile);
   //  4. close the file when processCommandLoop() returns
   fclose(pFile);

   fns.pop(fname);
   
 }

 void ArchipelagoExpedition::freeTrip()
 {
 	
 	int i;
 	for(i = 0; i < length;i++)
 	{
 		linkedLists[i].freeList();

 	}
 	
 	delete[] linkedLists;
 }

int main (int argc, char** argv)
{
  // set up the variable inFile to read from standard input
  FILE* inFile = stdin;

  // set up the data needed for the island adjcency list
  ArchipelagoExpedition islandData;
   
  // call the method that reads and parses the input
  islandData.showCommands();
  printf ("\nEnter commands at blank line\n");
  printf ("    (No prompts are given because of f command)\n");
  islandData.processCommandLoop (inFile);
  islandData.freeTrip();


  printf ("Goodbye\n");
  return 1;
 }
