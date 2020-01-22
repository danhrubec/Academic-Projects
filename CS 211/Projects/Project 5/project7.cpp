//Dan Hrubec
//Project 7
//CS 211

#include <cstdio>
#include <cstring>
#include <cstdlib>

#define TRUE 1
#define FALSE 0



class Tile
{
private:
bool visited;
char ctile;

public:
	Tile()
	{
		visited = false;
		ctile = ' ';
	}

	void setVisited(bool vis)
	{
		visited = vis;
	}

	bool getVisited()
	{
		return visited;
	}

    char getCTile()
	{
		return ctile;
	}

	void setCTile(char c)
	{
		ctile = c;
	}
};

class Wall : public Tile
{
private:
 	

public:

	Wall()
	:Tile()
	{
		setCTile('*');
	}

	char getCTile()
	{
		return getCTile();
	}
	

};

class Chest : public Tile
{
private:

public:

};


class Door : public Tile
{
private:

public:

};



class Room
{
private:
 Tile** myRoom;
 int** visited;  
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
public:
Room()
{
	initRoom();
}
Tile** getRoom()
{
	return myRoom;
}
void initRoom()
{
	int i;
	int j;
	//hard coding values for time being
	xsize = 10;
	ysize = 10;

	xstart = 1;
	ystart = 1;

	xend = 10;
	yend = 10;
	
	//allocating memory for both the maze and the parallel 2d array visited
	myRoom = (Tile**) malloc(sizeof(Tile*) * (xsize + 2));
	visited = (int**) malloc(sizeof(int *) * (xsize + 2));
	for(i = 0; i < xsize + 2; i++)
	{
		myRoom[i] = (Tile *) malloc(sizeof(Tile) * (ysize + 2));
		visited[i] = (int *) malloc(sizeof(int) * (ysize + 2));
	}
	
	//assigning . and 0 as starting values for all locations within both 2d arrays
	for (i = 0; i < xsize + 2; i++)
	{
		for (j = 0; j < ysize + 2; j++)
		{
			myRoom[i][j].setCTile('.');
			visited[i][j] = 0;
		}
	}
		
	//marking the borders
	for (i=  0; i < xsize + 2; i++)
	{
		myRoom[i][0].setCTile('*');
		myRoom[i][ysize + 1].setCTile('*');
		visited[i][0] = 1;
		visited[i][ysize + 1] = 1;
	}

	for (i = 0; i < ysize + 2; i++)
	{
		myRoom[0][i].setCTile('*');
		myRoom[xsize + 1][i].setCTile('*');
		visited[0][i] = 1;
		visited[xsize + 1][i] = 1;
	}	
	//marking the start and end locations
	myRoom[xstart][ystart].setCTile('P');
	myRoom[xend][yend].setCTile('D');
	
	//starting position as visited
	visited[xstart][ystart] = 1;

}

void printRoom()
{

  int i;
  int j;
  for(i = 0;i < xsize+2; i++)
  {
    for(j = 0; j < ysize+2; j++)
    {
      printf("%c",myRoom[i][j].getCTile());

    }
    printf("\t");
    for(j=0; j < ysize+2;j++)
    {
      printf("%d", visited[i][j]); // rewrites over "stock" maze with visited locations.
    }
    printf("\n");

  }

}


};


class Player
{
private:
	int xLocation;
	int yLocation;
	int tilesVisited;
	int goldScore;

public:
	Player()
	{
		xLocation = 1;
		yLocation = 1;
		tilesVisited = 0;
		goldScore = 0;
	}

	void setxLocation(int x)
	{
		xLocation = x;
	}

	void setyLocation(int y)
	{
		yLocation = y;
	}

	void setTilesVisited(int tv)
	{
		tilesVisited = tv;
	}

	void setgoldScore(int gs)
	{
		goldScore = gs;
	}

	int getxLocation()
	{
		return xLocation;
	}

	int getyLocation()
	{
		return yLocation;
	}

	int getTilesVisited()
	{
		return tilesVisited;
	}

	int getGoldScore()
	{
		return goldScore;
	}

	void addVisited()
	{
		tilesVisited = tilesVisited + 1;
	}

	void addScore(int s)
	{
		goldScore = goldScore + s;
	}
};

class userInterface
{
private:
Player* p;
Room* r;
public:
 userInterface()
 {
 	p = new Player;
 	r = new Room;
 }

 void processCommandLoop (FILE* inFile)
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
      exit(1);
    }
     
    else if ( strcmp (command, "w") == 0) 
      moveUp();
     
    else if ( strcmp (command, "a") == 0) 
      moveLeft();
     
    else if ( strcmp (command, "s") == 0) 
      moveDown();

    else if ( strcmp (command, "d") == 0) 
      moveRight();

    else if ( strcmp (command, "h") == 0) 
      printCommands();

    else if ( strcmp (command, "g") == 0) 
      printScore();

    else if ( strcmp (command, "f") == 0) 
      findDoor();
  	else if (strcmp(command,"p") == 0)
  	  printDungeon();

    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input
  }
 }

 void findDoor()
 {


 }

 void printDungeon()
 {
 	r->printRoom();
 }
 void moveRight()
 {
 	int oldyPos = p->getyLocation();
 	int newyPos = p->getyLocation() + 1;
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == '*')
 	{
 		printf("error. that is a wall.\n");
 		return;
 	}
 	p->setyLocation(newyPos);
 	r->getRoom()[p->getxLocation()][oldyPos].setCTile('.');
 	r->getRoom()[p->getxLocation()][newyPos].setCTile('P');
 	r->printRoom();
 

 }

 void moveUp()
 {
 	int oldxPos = p->getxLocation();
 	int newxPos = p->getxLocation() - 1;
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == '*')
 	{
 		printf("error. that is a wall.\n");
 		return;
 	}
 	p->setxLocation(newxPos);
 	r->getRoom()[oldxPos][p->getyLocation()].setCTile('.');
 	r->getRoom()[newxPos][p->getyLocation()].setCTile('P');
 	r->printRoom();

 }

 void moveLeft()
 {
 	int oldyPos = p->getyLocation();
 	int newyPos = p->getyLocation() - 1;
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == '*')
 	{
 		printf("error. that is a wall.\n");
 		return;
 	}
 	p->setyLocation(newyPos);
 	r->getRoom()[p->getxLocation()][oldyPos].setCTile('.');
 	r->getRoom()[p->getxLocation()][newyPos].setCTile('P');
 	r->printRoom();

 }

 void moveDown()
 {
 	int oldxPos = p->getxLocation();
 	int newxPos = p->getxLocation() + 1;
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == '*')
 	{
 		printf("error. that is a wall.\n");
 		return;
 	}
 	p->setxLocation(newxPos);
 	r->getRoom()[oldxPos][p->getyLocation()].setCTile('.');
 	r->getRoom()[newxPos][p->getyLocation()].setCTile('P');
 	r->printRoom();
 
 }
 void printScore()
 {
 	printf("Current Score:%d\n", p->getGoldScore());
 }

 void printCommands()
 {

  printf ("The commands for this project are:\n");
   printf ("  q (quit program) \n");
   printf ("  w (Move up)\n");
   printf ("  a (Move left)\n");
   printf ("  s (Move down) \n");
   printf ("  d (Move right) \n");
   printf ("  h (Prints commands) \n");
   printf ("  g (Print Score)\n");
   printf ("  f (Find door and print path)\n");
   printf ("  p (prints dungeon)\n");
 }

};


class DungeonCrawl
{
private:
	userInterface u;
	Room* r;
	int arrayTracker;
public:
DungeonCrawl()
{
	r = new Room[5];
	arrayTracker = 0;
}


void readFromFile(FILE* inFile)
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
      //freeTrip(); 
      exit(1);
  }
    else if ( strcmp (command, "?") == 0) 
      system("pause");
     
    else if ( strcmp (command, "t") == 0) 
      system("pause");
     
    else if ( strcmp (command, "r") == 0) 
      system("pause");

    else if ( strcmp (command, "i") == 0) 
      system("pause");

    else if ( strcmp (command, "d") == 0) 
      system("pause");

    else if ( strcmp (command, "l") == 0) 
      system("pause");

    else if ( strcmp (command, "f") == 0) 
     system("pause");

    else if ( strcmp (command, "#") == 0) 
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
}

};

int main (int argc, char** argv)
{
 /*
  FILE* inFile = stdin;
  userInterface u;
  u.printCommands();
  u.processCommandLoop(stdin);
 */
  FILE* inFile = stdin;
  DungeonCrawl* d = new DungeonCrawl;
  d->readFromFile(inFile);
 

  printf ("Goodbye\n");
  return 1;
}

