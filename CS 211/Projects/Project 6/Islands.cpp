#include "Island.h"

Island::Island()
{
	head = NULL;
}
	
int Island::isEmpty()
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

int Island::find(int num)
{
	Node* temp = head;
	if(head == NULL)
	{
		return FALSE;
	}
	while(temp != NULL)
	{
		if(temp->getElem() == num)
			return TRUE;

		temp = temp->getNext();
	}
		return FALSE;
}

int Island::top()
{

	if( head != NULL)
	{
		return head->getElem();
	}
	else
	{
		printf("Cannot get top of empty list. Returning -999\n");
		return -999;
	}
}

void Island::clear()
{
	head = NULL;
}

void Island::printList()
{	
	Node* temp = head;
	if(this->isEmpty() == TRUE)
		printf("List empty.\n");

	while(temp != NULL)
	{
		printf("\t%d, ", temp->getElem());
		temp = temp->getNext();

	}
	printf("\n\n");
}

Node* Island::listHead()
{
	if(head == NULL)
		return NULL;
	else
		return head;
}

void Island::freeList()
{
	if(head == NULL)
	{
		delete head;
	}

	while(head != NULL)
	{
		Node* temp = head;
		head = head->getNext();
		delete temp;

	}
	delete head;
}

void Island::pop(int val)
{

	Node* temp = head;
	Node* prev = temp;
	if(this->isEmpty() == TRUE)
	{
		printf("error. cannot pop front empty stack.\n");
		return;
	}
		
	//testing the front of the linked list
	if(temp->getElem() == val)
	{
		head = head->getNext();
		delete temp;
		return;
	}

	while(temp->getNext() != NULL)
	{
		if(temp->getElem() == val)
		{
			prev->setNext(temp->getNext());
			temp->setNext(NULL);
			delete temp;
			return;
		}
		prev = temp;
		temp = temp->getNext();
	}

	if(temp->getElem() == val)
	{
		prev->setNext(NULL);
		delete temp;
		return;
	}
	
	printf("error. could not find value in stack\n");
	return;
}
void Island::push(int num, bool val)
{
	Node* tmp = new Node(num,val);
	tmp->setNext(head);
	head = tmp;

}

void Island::reset()
{	
	Node* temp = head;

	if(temp == NULL)
	{
		//printf("empty list. cannot reset visited values.\n");
		return;
	}

	while(temp != NULL)
	{
		temp->setVisited(false);
		temp = temp->getNext();
	}
}


