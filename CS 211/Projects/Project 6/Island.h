#include <cstdio>
#include <cstring>
#include <cstdlib>

#define TRUE 1
#define FALSE 0

class fnode
{
private:
	char* name;
	fnode* next;
public:
	fnode(char* n);
	char* getName();
	fnode* getNext();
	void setName(char* n);
	void setNext(fnode* newnode);
};

class fileNames
{
private:
	fnode* head;
public:
	fileNames();
	int find(char* nm);
	int isEmpty();
	void pop(char* nm);
	void push(char* nm);
	void printList();

};

class Node
{
	private:
	int element;
	bool visited;
	Node* next;

	public:
	Node(int elem, bool vis);
	int getElem();
	Node* getNext();
	bool getVisited();
	void setElem(int val);
	void setVisited(bool vis);
	void setNext(Node* newnode);
};


class Island
{
private:
	Node* head;
public:
	Island();
	int isEmpty();
	int find(int num);
	int top();
	void clear();
	void printList();
	Node* listHead();
	void freeList();
	void pop(int val);
	void push(int num, bool val);
	void reset();
};

class ArchipelagoExpedition
{
 private:
 	int length;
 	Island* linkedLists;
 	fileNames fns;
 public:
 ArchipelagoExpedition();
 void processCommandLoop (FILE* inFile);
 void depthFirstSearchHelper(int x,int y);
 bool dfs(int a, int b);
 void showCommands();
 void doTravel();
 void doResize();
 void doInsert();
 void doDelete();
 void doList();
 void doFile();
 void freeTrip();
};
