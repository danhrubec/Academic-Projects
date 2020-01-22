#include "DungeonCrawl.h"

DungeonCrawl::DungeonCrawl()
{
	rooms = new Room*[6];
	//u = new userInterface;
	arrayTracker = 0;
	counter = 0;
	firstLine = true;
	totalGold = 0;

}


void DungeonCrawl::readFromFile(FILE* inFile)
{
  char  buffer[300];
  char* input;

 

   input = fgets ( buffer, 300, inFile );   // get a line of input

   // get an integer value from the input
   
   if(firstLine == true)
   {
  	 xdim = atoi(input);
   	 ydim = atoi(input);
   	 firstLine = false;
   }
  
  // loop until all lines are read from the input
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \n\t");
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "S") == 0)
    {
      setStart(); 
      input = fgets ( buffer, 300, inFile );
    }
    else if ( strcmp (command, "O") == 0) 
    {
      addWall();
      input = fgets ( buffer, 300, inFile );
    }
     
    else if ( strcmp (command, "C") == 0) 
    {
      addChest();
      input = fgets ( buffer, 300, inFile );
    }
     
    else if ( strcmp (command, "D") == 0) 
    {
      addDoor();
      input = fgets ( buffer, 300, inFile );
    }

    else if ( strcmp (command, "E") == 0) 
    {
      addExit();
      input = fgets ( buffer, 300, inFile );
      
    }
     
    else
      //printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }

  return;
}
  void DungeonCrawl::addDoor()
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
   rooms[arrayTracker]->getRoom()[val1][val2].setCTile('D');
   rooms[arrayTracker]->setxend(val1);
   rooms[arrayTracker]->setyend(val2);

   char* fname = strtok (NULL, " \n\t");
   if ( fname == NULL )
   {
     printf ("Filename expected\n");
     return;
   }
   
   FILE* pFile;
   pFile = fopen(fname,"r");
   if(pFile == NULL)
   {
   	printf("File is empty. Exiting.\n");
   	return;
   }

 
   arrayTracker++;
   firstLine = true;
   this->readFromFile(pFile);
 
   fclose(pFile);

  }
  void DungeonCrawl::addExit()
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

  rooms[arrayTracker]->getRoom()[val1][val2].setCTile('E');
  //printAll();
  }
  void DungeonCrawl::addWall()
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

  rooms[arrayTracker]->getRoom()[val1][val2].setCTile('*');
  rooms[arrayTracker]->getVisited()[val1][val2] = 8;

  }
  void DungeonCrawl::addChest()
  {
   int val1 = 0;
   int val2 = 0;
   int val3 = 0;

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
   //getting 3rd input
   next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val3 = atoi ( next );
   if ( val3 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

  rooms[arrayTracker]->getRoom()[val1][val2].setCTile('C');
   rooms[arrayTracker]->getRoom()[val1][val2].setgoldValue(val3);




  }
  void DungeonCrawl::setStart()
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
   

   xstart = val1;
   ystart = val2;

   createRoom();
  }

  void DungeonCrawl::createRoom()
  {
  	Room* r = new Room(xdim,ydim,xstart,ystart,0,0);
  	rooms[arrayTracker] = r;
  	rooms[arrayTracker]->getRoom()[0][0].setCTile('*');


  }

  void DungeonCrawl::printAll()
  {
  	int i;

  	for( i = 0; i < arrayTracker + 1;i++)
  	{
  		rooms[i]->printRoom();
  		printf("\n\n");
  	}

  }

  void DungeonCrawl::startDungeon(FILE* inFile)
  {
  	int i;
  	for(i = 0; i < arrayTracker + 1;i++)
  	{
  		userInterface* u2 = new userInterface(rooms[i]->getxStart(),rooms[i]->getyStart(), 0, totalTiles);
		u2->setRoom(rooms[i]);
  		u2->getRoom().printRoom();
  		u2->processCommandLoop(inFile);
  		totalGold = totalGold + u2->getPlayer().getGoldScore();
  		totalTiles = totalTiles + u2->getTilesMoved();
  		u2->setdoorReached(false);
  	}

  	printf("Congratulations! You have exited the dungeon!\n");
	printf("Tiles moved:%d\n", totalTiles);
	printf("Total Gold:%d\n",totalGold);
	exit(1);
  	
  }
