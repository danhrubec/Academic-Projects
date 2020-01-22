//Dan Hrubec
//Project 7
//CS 211

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

#define TRUE 1
#define FALSE 0

class Tile
{
private:
bool visited;
char ctile;
int goldValue;
public:
	Tile();
	void setVisited(bool vis);
	bool getVisited();
    char getCTile();
	void setCTile(char c);
	void setgoldValue(int g);
	int getgoldValue();
};

class Wall : public Tile
{
private:
public:
	Wall();
	char getCTile();
};

class Chest : public Tile
{
private:
	int goldAmount;
public:
	Chest();
	void setgoldAmount(int ga);
	int getGold();
};


class Door : public Tile
{
private:
	char* filename;
public:
	Door();
	void setfile(char* f);
	char* getfile();
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
Room(int xsz, int ysz, int xstrt, int ystrt, int xnd, int ynd);
Tile** getRoom();
Room();
int** getVisited();
int getxend();
int getyend();
void setxend(int x);
void setyend(int y);
int getxStart();
int getyStart();
void initRoom(int xsz, int ysz, int xstrt, int ystrt, int xnd, int ynd);
void printRoom();
void printBoth();
};

class Player
{
private:
	int xLocation;
	int yLocation;
	int tilesVisited;
	int goldScore;
public:
Player(int x, int y, int g, int t);
Player();
void setxLocation(int x);
void setyLocation(int y);
void setTilesVisited(int tv);
void setgoldScore(int gs);
int getxLocation();
int getyLocation();
int getTilesVisited();
int getGoldScore();
void addVisited();
void addScore(int s);
void reset(int x, int y);
};

//used for find door function
typedef struct structLinkList
{
  int xpos;
  int ypos;  //x and y pos will keep track of where we at
  struct structLinkList *next;
}myStack;

class userInterface
{
private:
Player* p;
Room* r;
bool firstLine;
bool doorReached;
int tilesMoved;
int xstr;
int ystr;
public:
userInterface(int x, int y, int g, int t);
Player getPlayer();
Room getRoom();
void setdoorReached(bool dr);
bool getdoorReached();
int getTilesMoved();
void setRoom(Room* nr);
void processCommandLoop (FILE* inFile);
void push(myStack **head, int xpos, int ypos);
int isEmpty(myStack *head);
void pop(myStack **head);
void findDoor();
void printDungeon();
void moveRight();
void moveUp();
void moveLeft();
void moveDown();
void printScore();
void printCommands();
};

class DungeonCrawl
{
private:
	//userInterface* u;
	Room** rooms;
	int arrayTracker;
	int counter;
	bool firstLine;
	int totalGold;
	int totalTiles;
	int xdim;
	int ydim;
	int xstart;
	int ystart;
	int xend;
	int yend;
public:
DungeonCrawl();
void readFromFile(FILE* inFile);
void addDoor();
void addExit();
void addWall();
void addChest();
void setStart();
void createRoom();
void printAll();
void startDungeon(FILE* inFile);
};



