#include "DungeonCrawl.h"

int main (int argc, char** argv)
{
 
  FILE* inFile = fopen("Room1.txt", "r");
  DungeonCrawl* d = new DungeonCrawl;
  d->readFromFile(inFile);
  fclose(inFile);

  FILE* pfile = stdin;
  d->startDungeon(pfile);
 

  printf ("Goodbye\n");
  return 1;
}
/*
USER INTERFACE FUNCTIONS
*/


 userInterface::userInterface(int x, int y, int g, int t)
 {
 	p = new Player(x,y,g,t);
 	r = new Room;
 	int xstr = x;
 	int ystr = y;
 	firstLine = true;
 }

Player userInterface::getPlayer()
{
	return *p;
}

Room userInterface::getRoom()
{
	return *r;
}
void userInterface::setdoorReached(bool dr)
{
	doorReached = dr;
}

bool userInterface::getdoorReached()
{

	return doorReached;
}


int userInterface::getTilesMoved()
{
	return tilesMoved;
}

void userInterface::setRoom(Room* nr)
{
	r = nr;
}
 void userInterface::processCommandLoop (FILE* inFile)
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
     
     if (doorReached == true)
     {
     	return;
     }
    input = fgets ( buffer, 300, inFile );   // get the next line of input
  }
 }

void userInterface::push(myStack **head, int xpos, int ypos)
{
	
	myStack *temp = (myStack *) malloc(sizeof(myStack));

	temp->xpos = xpos;
	temp->ypos = ypos;
	temp->next = *head;
	
	*head = temp;

}

int userInterface::isEmpty(myStack *head)
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

void userInterface::pop(myStack **head)
{
  //set temp head
  myStack *temp = *head;
  //check to see if list is empty
  if(*head != NULL){
    *head = (*head)->next;
    free(temp);
    return;
  }

  //printf("\nCannot pop from empty stack\n");
  return;
}

 void userInterface::findDoor()
 {
 	myStack* list;
 	int xcurr = p->getxLocation();
 	int ycurr = p->getyLocation();

 	int newxend = r->getxend();
 	int newyend = r->getyend();

 	push(&list,xstr, ystr);
 	
 	/* loop while stack is not empty and end has not been found */
  while(isEmpty(list) != 1)
  {
  //check if top of the stack is the end position
  if(list->xpos == newxend && list->ypos == newyend)
	break;
  //check if top of the stack has unvisited and unblocked neighbor
  if(r->getVisited()[xcurr][ycurr + 1] == 0)
  { 
    //check right
	ycurr++;
	//push coordinates of unvisited neighbor on the stack
	push(&list, xcurr, ycurr);
	//mark the unvisited as visited
	r->getVisited()[xcurr][ycurr] = 2;
  }
		else if(r->getVisited()[xcurr + 1][ycurr] == 0)
		{ //check down
			//set new xcurr
			xcurr++;
			//push coordinates of unvisited neighbor on the stack
			push(&list, xcurr, ycurr);
			//mark the unvisited neighbor as visited
			r->getVisited()[xcurr][ycurr] = 2;
			
		}
		else if(r->getVisited()[xcurr][ycurr - 1] == 0)
		{ //check left
			//set new ycurr
			ycurr--;
			//push coordinates of unvisited neighbor on the stack
			push(&list, xcurr, ycurr);
			//mark the unvisited neighbor as visited
			r->getVisited()[xcurr][ycurr] = 2;
		}
		else if(r->getVisited()[xcurr - 1][ycurr] == 0)
		{ //check up
			//set new xcurr
			xcurr--;
			//push coordinates of unvisited neighbor on the stack
			push(&list, xcurr, ycurr);
			//mark the unvisited neighbor as visited
			r->getVisited()[xcurr][ycurr] = 2;
		}
		
		else
		{ //no positions available. go back to previous
			pop(&list); 
			if(isEmpty(list)) //check for no solution
				continue;
			xcurr = list->xpos;
			ycurr = list->ypos;
		}
  }
	//check if stack is empty
	if(isEmpty(list))
	{
		printf("\nNo solution\n");
		return;
	}
	else{ //the items on the stack contain the coordinates of the solution from the end of the maze to start of the maze
		printf("sample solution\n");
		r->printBoth();
		printf("\n");
		//exit(1);
	}



 }

 void userInterface::printDungeon()
 {
 	r->printRoom();
 }
 void userInterface::moveRight()
 {
 	int oldyPos = p->getyLocation();
 	int newyPos = p->getyLocation() + 1;
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == '*')
 	{
 		printf("error. that is a wall.\n");
 		return;
 	}
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == 'D')
 	{
 		doorReached = true;
 	}
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == 'C')
 	{
 		printf("Chest found. It contained:%d gold.\n",r->getRoom()[p->getxLocation()][newyPos].getgoldValue() );
 		int prevGold = p->getGoldScore();
 		int newGold = prevGold + r->getRoom()[p->getxLocation()][newyPos].getgoldValue();
 		p->setgoldScore(newGold);
 	}
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == 'E')
 	{
 		tilesMoved = tilesMoved + 1;
 		doorReached = true;
 		doorReached = true;
 	}
 	p->setyLocation(newyPos);
 	r->getRoom()[p->getxLocation()][oldyPos].setCTile('.');
 	r->getRoom()[p->getxLocation()][newyPos].setCTile('P');
 	r->printRoom();
 	tilesMoved = tilesMoved + 1;
 

 }

 void userInterface::moveUp()
 {
 	int oldxPos = p->getxLocation();
 	int newxPos = p->getxLocation() - 1;
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == '*')
 	{
 		printf("error. that is a wall.\n");
 		return;
 	}
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == 'D')
 		doorReached = true;
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == 'C')
 	{
 		printf("Chest found. It contained:%d gold.\n",r->getRoom()[newxPos][p->getyLocation()].getgoldValue() );
 		int prevGold = p->getGoldScore();
 		int newGold = prevGold + r->getRoom()[newxPos][p->getyLocation()].getgoldValue();
 		p->setgoldScore(newGold);
 	}

 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == 'E')
 	{
 		tilesMoved = tilesMoved + 1;
 		doorReached = true;
 	}
 	p->setxLocation(newxPos);
 	r->getRoom()[oldxPos][p->getyLocation()].setCTile('.');
 	r->getRoom()[newxPos][p->getyLocation()].setCTile('P');
 	r->printRoom();
 	tilesMoved = tilesMoved + 1;

 }

 void userInterface::moveLeft()
 {
 	int oldyPos = p->getyLocation();
 	int newyPos = p->getyLocation() - 1;
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == '*')
 	{
 		printf("error. that is a wall.\n");
 		return;
 	}
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == 'D')
 		doorReached = true;
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == 'C')
 	{
 		printf("Chest found. It contained:%d gold.\n",r->getRoom()[p->getxLocation()][newyPos].getgoldValue() );
 		int prevGold = p->getGoldScore();
 		int newGold = prevGold + r->getRoom()[p->getxLocation()][newyPos].getgoldValue();
 		p->setgoldScore(newGold);
 	}
 	if(r->getRoom()[p->getxLocation()][newyPos].getCTile() == 'E')
 	{
 		tilesMoved = tilesMoved + 1;
 		doorReached = true;
 	}

 	p->setyLocation(newyPos);
 	r->getRoom()[p->getxLocation()][oldyPos].setCTile('.');
 	r->getRoom()[p->getxLocation()][newyPos].setCTile('P');
 	r->printRoom();
 	tilesMoved = tilesMoved + 1;

 }

 void userInterface::moveDown()
 {
 	int oldxPos = p->getxLocation();
 	int newxPos = p->getxLocation() + 1;
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == '*')
 	{
 		printf("error. that is a wall.\n");
 		return;
 	}
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == 'D')
 		doorReached = true;
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == 'C')
 	{
 		printf("Chest found. It contained:%d gold.\n",r->getRoom()[newxPos][p->getyLocation()].getgoldValue() );
 		int prevGold = p->getGoldScore();
 		int newGold = prevGold + r->getRoom()[newxPos][p->getyLocation()].getgoldValue();
 		p->setgoldScore(newGold);
 	}
 	if(r->getRoom()[newxPos][p->getyLocation()].getCTile() == 'E')
 	{
 		tilesMoved = tilesMoved + 1;
 		doorReached = true;
 	}
 	p->setxLocation(newxPos);
 	r->getRoom()[oldxPos][p->getyLocation()].setCTile('.');
 	r->getRoom()[newxPos][p->getyLocation()].setCTile('P');
 	r->printRoom();
 	tilesMoved = tilesMoved + 1;
 
 }
 void userInterface::printScore()
 {
 	printf("Current Score in this room:%d\n", p->getGoldScore());
 }

 void userInterface::printCommands()
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


 /*
player class
*/

	Player::Player(int x, int y, int g, int t)
	{
		xLocation = x;
		yLocation = y;
		tilesVisited = t;
		goldScore = g;
	}

	Player::Player()
	{
		xLocation = 1;
		yLocation = 1;
		tilesVisited = 0;
		goldScore = 0;
	}

	void Player::setxLocation(int x)
	{
		xLocation = x;
	}

	void Player::setyLocation(int y)
	{
		yLocation = y;
	}

	void Player::setTilesVisited(int tv)
	{
		tilesVisited = tv;
	}

	void Player::setgoldScore(int gs)
	{
		goldScore = gs;
	}

	int Player::getxLocation()
	{
		return xLocation;
	}

	int Player::getyLocation()
	{
		return yLocation;
	}

	int Player::getTilesVisited()
	{
		return tilesVisited;
	}

	int Player::getGoldScore()
	{
		return goldScore;
	}

	void Player::addVisited()
	{
		tilesVisited = tilesVisited + 1;
	}

	void Player::addScore(int s)
	{
		goldScore = goldScore + s;
	}
	void Player::reset(int x, int y)
	{
		xLocation = x;
		yLocation = y;
	}

/*
Room class
*/
Room::Room(int xsz, int ysz, int xstrt, int ystrt, int xnd, int ynd)
{
	initRoom(xsz,ysz,xstrt,ystrt,xnd,ynd);
}
Tile** Room::getRoom()
{
	return myRoom;
}
Room::Room()
{


}

int** Room::getVisited()
{
	return visited;
}

int Room::getxend()
{
	return xend;
}

int Room::getyend()
{
	return yend;
}

void Room::setxend(int x)
{
	xend = x;
}

void Room::setyend(int y)
{
	yend = y;
}
int Room::getxStart()
{
	return xstart;
}

int Room::getyStart()
{
	return ystart;
}
void Room::initRoom(int xsz, int ysz, int xstrt, int ystrt, int xnd, int ynd)
{
	int i;
	int j;
	
	xsize = xsz;
	ysize = ysz;

	xstart = xstrt;
	ystart = ystrt;

	xend = xnd;
	yend = ynd;
	
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

void Room::printRoom()
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
      //printf("%d", visited[i][j]); // rewrites over "stock" maze with visited locations.
    }
    printf("\n");

  }

}

void Room::printBoth()
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

/*
everything else
*/

	Door::Door()
	:Tile()
	{

	}

	void Door::setfile(char* f)
	{
		filename = f;
	}

	char* Door::getfile()
	{
		return filename;
	}

	Chest::Chest()
	:Tile()
	{
		goldAmount = 0;
	}

	void Chest::setgoldAmount(int ga)
	{
		goldAmount = ga;
	}

	int Chest::getGold()
	{
		return goldAmount;
	}

	Wall::Wall()
	:Tile()
	{
		setCTile('*');
	}

	char Wall::getCTile()
	{
		return getCTile();
	}

	Tile::Tile()
	{
		visited = false;
		ctile = ' ';
		goldValue = 0;
	}

	void Tile::setVisited(bool vis)
	{
		visited = vis;
	}

	bool Tile::getVisited()
	{
		return visited;
	}

    char Tile::getCTile()
	{
		return ctile;
	}

	void Tile::setCTile(char c)
	{
		ctile = c;
	}

	void Tile::setgoldValue(int g)
	{
		goldValue = g;
	}

	int Tile::getgoldValue()
	{
		return goldValue;
	}
