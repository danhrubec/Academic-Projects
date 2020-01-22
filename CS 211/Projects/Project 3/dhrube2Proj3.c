//Dan Hrubec
//CS 211
//Programming Project 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Globals
#define TRUE 1
#define FALSE 0
int DebugMode = 0;

//Struct definition for the maze
typedef struct mazeStruct
{
 char** arr;  // 2d array that creates the grid for the maze
 int** visited;  //parallel 2d array will keep track of spots that have been visited
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

//creating a struct for linked list to be used as stack
typedef struct structLinkList
{
  int xpos;
  int ypos;  //x and y pos will keep track of where we at
  struct structLinkList *next;
}stack;

//supporting function, prints maze info like start location, end and size of it.
void printMazeInfo(maze m1)
{
  if(DebugMode == TRUE)
 	printf("Entering printMazeInfo...\n");
  printf ("\nsize: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n\n", m1.xend, m1.yend);
  if(DebugMode == TRUE)
 	printf("Exiting printMazeInfo...\n");
}

void printMaze(maze* m1)
{
  if(DebugMode == TRUE)
 	printf("Entering printMaze...\n");
  int i;
  int j;
  for(i = 0;i < m1->xsize+2; i++)
  {
    for(j = 0; j < m1->ysize+2; j++)
    {
      printf("%c",m1->arr[i][j]);

    }
    printf("\t");
    for(j=0; j < m1->ysize+2;j++)
    {
      printf("%d", m1->visited[i][j]); // rewrites over "stock" maze with visited locations.
    }
    printf("\n");
  }
  if(DebugMode == TRUE)
 	printf("Exiting printMaze...\n");
}

void readFromFile(FILE *src, int *xsize, int *ysize, int *xstart, int *ystart, int *xend, int*yend)
{
	if(DebugMode == TRUE)
 		printf("Reading data from file...\n");
	//Testing to see if valid maze size, breaks loops once found.
	while(fscanf (src, "%d %d", &*xsize, &*ysize) != EOF){
		if(*xsize > 0 && *ysize > 0)
			break;
		else{
			printf("Not a valid maze size: %d, %d\n", *xsize, *ysize);
			*xsize = -1;
			*ysize = -1;
		}
	}
	//Testing to see if a valid start location. Breaks loop when it is found
	while(fscanf (src, "%d %d", &*xstart, &*ystart) != EOF){
		if(*xstart <= *xsize && *ystart <= *ysize)
			break;
		else{
			printf("Not a valid maze start location: %d, %d\n", *xstart, *ystart);
			*xstart = -1;
			*ystart = -1;
		}
	}
	//Testing to see if the end location is valid. Breaks loop if it finds a valid location
	while(fscanf (src, "%d %d", &*xend, &*yend) != EOF){
		if(*xend <= *xsize && *yend <= *ysize)
			break;
		else{
			printf("Not a valid location for end of maze: %d, %d\n", *xend, *yend);
			*xend = -1;
			*yend = -1;
		}
	}
	if(DebugMode == TRUE)
 		printf("Data successfully read...\n");
}

//Has 6 parameters, checking to see if information is valid and then will assign to maze.
void checkValid(int xsize, int ysize, int xstart, int ystart, int xend, int yend)
{
	if(DebugMode == TRUE)
 		printf("checkValid Function...\n");
	//Testing size to see if valid
	if(xsize == -1 || ysize == -1)
	{
		printf("End of file reached. No valid parameters for maze was found.\n");
		exit(1);
	}
	//Testing start to see if it is valid
	if(xstart == -1 || ystart == -1)
	{
		printf("End of file reached. No valid parameters for maze was found.\n");
		exit(1);
	}
	//Testing the end to see if it is valid
	if(xend == -1 || yend == -1)
	{
		printf("End of file reached. No valid parameters for maze was found.\n");
		exit(1);
	}
	if(DebugMode == TRUE)
 		printf("Exiting checkValid Function...\n");
}


void freeMaze(maze* m1)
{
  int i;
  for(i = 0; i < m1->xsize + 2; i++)
  {
    free(m1->visited[i]);
    free(m1->arr[i]);
  }
  free(m1->arr);
  free(m1->visited);

}

void pop(stack **head)
{
  //set temp head
  stack *temp = *head;
  //check to see if list is empty
  if(*head != NULL){
    *head = (*head)->next;
    free(temp);
    return;
  }

  printf("\nCannot pop from empty stack\n");
  return;
}


void markBlocked(FILE *src, maze *maze, int *xpos, int *ypos, int xstart, int ystart, int xend, int yend, int xsize, int ysize)
{
	if(DebugMode == TRUE)
 		printf("Blocking marked locations...\n");
	while (fscanf (src, "%d %d", &*xpos, &*ypos) != EOF)
	{
		
 		if(*xpos == xstart && *ypos == ystart)
 		{
			printf("starting position invalid: %d, %d\n", *xpos, *ypos);
			continue;
		}
		
		if(*xpos == xend && *ypos == yend)
		{
			printf("end position invalid: %d, %d\n", *xpos, *ypos);
			continue; 
		}
	
		if(*xpos > xsize || *ypos > ysize)
		{
			printf("outside of maze parameters: %d, %d\n", *xpos, *ypos);
			continue;
		}
	
		if(*xpos < 1 || *ypos < 1)
		{
			printf("invalid blocking location: %d, %d\n", *xpos, *ypos);
			continue;
		}
		maze->arr[*xpos][*ypos] = '*';
		maze->visited[*xpos][*ypos] = 1;
	}
	if(DebugMode == TRUE)
 		printf("Complete. Exiting...\n");
}


int isEmpty(stack *head)
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

void push(stack **head, int xpos, int ypos){
	
	stack *temp = (stack *) malloc(sizeof(stack));

	temp->xpos = xpos;
	temp->ypos = ypos;
	temp->next = *head;
	
	*head = temp;

}

void displayList(stack *head)
{
  stack* temp = head;
  //first will check to see if the list is currently empty
  //if it is, it will exit the function immediately 
  if(isEmpty(head) == 1)
  {
    printf("\nStack is Empty\n");
    return;

  }

  while(temp->next != NULL)
  {
    printf("Location: (%d,%d)\n", temp->xpos, temp->ypos);
    temp = temp->next;
  }
  printf("Location: (%d,%d)\n", temp->xpos, temp->ypos);
}



void initMaze(maze *m1, int xsize, int ysize, int xstart, int ystart, int xend, int yend){
	//loop control variables
	int i;
	int j;
	//Assigning maze starting locations, already tested for validity
	m1->xsize = xsize;
	m1->ysize = ysize;

	m1->xstart = xstart;
	m1->ystart = ystart;

	m1->xend = xend;
	m1->yend = yend;
	
	//allocating memory for both the maze and the parallel 2d array visited
	m1->arr = (char **) malloc(sizeof(char *) * (m1->xsize + 2));
	m1->visited = (int **) malloc(sizeof(int *) * (m1->xsize + 2));
	for(i = 0; i < m1->xsize + 2; i++)
	{
		m1->arr[i] = (char *) malloc(sizeof(char) * (m1->ysize + 2));
		m1->visited[i] = (int *) malloc(sizeof(int) * (m1->ysize + 2));
	}
		
	//assigning . and 0 as starting values for all locations within both 2d arrays
	for (i = 0; i < m1->xsize + 2; i++)
	{
		for (j = 0; j < m1->ysize + 2; j++)
		{
			m1->arr[i][j] = '.';
			m1->visited[i][j] = 0;
		}
	}
		
	//marking the borders
	for (i=  0; i < m1->xsize + 2; i++)
	{
		m1->arr[i][0] = '*';
		m1->arr[i][m1->ysize + 1] = '*';
		m1->visited[i][0] = 1;
		m1->visited[i][m1->ysize + 1] = 1;
	}

	for (i = 0; i < m1->ysize + 2; i++)
	{
		m1->arr[0][i] = '*';
		m1->arr[m1->xsize + 1][i] = '*';
		m1->visited[0][i] = 1;
		m1->visited[m1->xsize + 1][i] = 1;
	}	
	//marking the start and end locations
	m1->arr[m1->xstart][m1->ystart] = 's';
	m1->arr[m1->xend][m1->yend] = 'e';
	
	//starting position as visited
	m1->visited[m1->xstart][m1->ystart] = 1;
}

void freeList(stack *head)
{
   stack* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

int main (int argc, char **argv)
{
  maze m1;

  int xpos, ypos;
  int i,j;

  int xstart = -1;
  int ystart = -1;

  int xsize = -1;
  int ysize = -1;

  int xend = -1;
  int yend = -1;

  stack *list = NULL;


  FILE *src;

 //global variable, assigning default value to 0
 DebugMode = FALSE; 

 //data to check if -d was passed, it so then enters debugmode
 int q;
 for ( q = 0 ; q < argc ; q++ ) 
 {
 	if (strcmp(argv[q], "-d") == 0 ) 
 		DebugMode = TRUE;
 }
  /* verify the proper number of command line arguments were given */
  if(argc > 3) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }
   
  /* Try to open the input file. */
  if ( ( src = fopen(  argv[1], "r" )) == NULL && ( src = fopen(  argv[2], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s",  argv[1] );
    exit(-1);
  }


  /* read in the size, starting and ending positions in the maze */
  readFromFile(src, &xsize, &ysize, &xstart, &ystart, &xend, &yend);

  checkValid(xsize, ysize, xstart, ystart, xend, yend); //checking if info on file is valid
  initMaze(&m1, xsize, ysize, xstart, ystart, xend, yend); //giving maze starting values
  printMazeInfo(m1);// printing maze
  markBlocked(src, &m1, &xpos, &ypos, xstart, ystart, xend, yend, xsize, ysize);

  printf("Maze\n");
  printMaze(&m1);

  push(&list, xstart, ystart);

  //variables to keep track of current positions
  int xcurr = xstart, ycurr = ystart;


  /* loop while stack is not empty and end has not been found */
  while(isEmpty(list) != 1)
  {
  //check if top of the stack is the end position
  if(list->xpos == m1.xend && list->ypos == m1.yend)
	break;
		
  //check if top of the stack has unvisited and unblocked neighbor
  if(m1.visited[xcurr][ycurr + 1] == 0)
  { 
    //check right
	ycurr++;
	//push coordinates of unvisited neighbor on the stack
	push(&list, xcurr, ycurr);
	//mark the unvisited as visited
	m1.visited[xcurr][ycurr] = 1;
	m1.arr[xcurr][ycurr] = '>';
  }
		else if(m1.visited[xcurr + 1][ycurr] == 0){ //check down
			//set new xcurr
			xcurr++;
			//push coordinates of unvisited neighbor on the stack
			push(&list, xcurr, ycurr);
			//mark the unvisited neighbor as visited
			m1.visited[xcurr][ycurr] = 1;
			m1.arr[xcurr][ycurr] = '-';
		}
		else if(m1.visited[xcurr][ycurr - 1] == 0){ //check left
			//set new ycurr
			ycurr--;
			//push coordinates of unvisited neighbor on the stack
			push(&list, xcurr, ycurr);
			//mark the unvisited neighbor as visited
			m1.visited[xcurr][ycurr] = 1;
			m1.arr[xcurr][ycurr] = '<';
		}
		else if(m1.visited[xcurr - 1][ycurr] == 0){ //check up
			//set new xcurr
			xcurr--;
			//push coordinates of unvisited neighbor on the stack
			push(&list, xcurr, ycurr);
			//mark the unvisited neighbor as visited
			m1.visited[xcurr][ycurr] = 1;
			m1.arr[xcurr][ycurr] = '+';
		}
		
		else{ //no positions available. go back to previous
			pop(&list); 
			if(isEmpty(list)) //check for no solution
				continue;
			xcurr = list->xpos;
			ycurr = list->ypos;
		}
	}
	
	//check if stack is empty
	if(isEmpty(list)){
		printf("\nNo solution\n");
		exit(1);
	}
	else{ //the items on the stack contain the coordinates of the solution from the end of the maze to start of the maze
		printf("sample solution\n");
		printMaze(&m1);
		printf("\n");
		displayList(list);
		//exit(1);
	}
	
	/* deallocate memory */
  for(i = 0; i < m1.xsize + 2; i++)
  {
    free(m1.visited[i]);
    free(m1.arr[i]);
  }
  free(m1.arr);
  free(m1.visited);
  freeList(list);
  fclose(src);


  }
