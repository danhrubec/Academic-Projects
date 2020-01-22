#include "restaurantSystem.h"

extern debugMode;

void addToList(ticketList** hd, char* nm, int stat, int nb,int ns)
{
 if(debugMode == TRUE)
  {
    printf("Entering addToList()..\n");

  }
	ticketList *newOrder = (ticketList*) malloc(sizeof(ticketList));
	newOrder->name = nm;
	newOrder->numBurger = nb;
	newOrder->numSalad = ns;
	newOrder->status = stat;

	newOrder->next = NULL;

	if(*hd == NULL)
	{
		*hd = newOrder;
	}
	else
	{
		ticketList *temp = *hd; 
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = newOrder; 
	}

  if(debugMode == TRUE)
  {
    printf("Exiting...\n");
  }

}
//returns 0 if it is not in the list, returns 1 if it is in the list
int doesNameExist(ticketList** hd,char* nm)
{
  if(debugMode == TRUE)
  {
    printf("Entering doesNameExist...\n");

  }
	ticketList *tmp = *hd;
	if(tmp == NULL) // if list empty, name cannot be in the list
		return 0;


	while(tmp != NULL){
		if(strcmp(tmp->name, nm) == 0)
			return 1;
		tmp = tmp->next;
	}
	return 0;
  if(debugMode == TRUE)
  {
    printf("Exiting doesNameExist...\n");

  }
}

void displayListInformation(ticketList** hd)
{
	ticketList* tmp = *hd;
	int i = 1;
	char* present;
	if(tmp == NULL)
	{
		printf("List empty.\n");
		return;//if its empty, dont do anything else. just exit the function.
	}
	printf("#\tName\tBurgers\tSalads\tStatus\n");
	while(tmp != NULL){
		if(tmp->status == 0)
			present = "Present";
		else
			present = "Not Present";
		printf("%d\t%s\t%d\t%d\t%s\n", i, tmp->name, tmp->numBurger,tmp->numSalad, present);
		i++;
		tmp = tmp->next;
	}

}

void displayOrdersAhead(ticketList** hd, int ahead)
{
	ticketList *tmp = *hd;
	int counter = 0;
	int i = 1;
	char *sc;
	
	if(tmp == NULL){
		printf("The list is empty\n");
	}
	else if(counter == ahead){
		printf("Entry is the first in line. No one is in front.\n");
	}
	printf("#\tName\tBurgers\tSalads\tStatus\n");
	while(counter != ahead && tmp != NULL){
		if(tmp->status == 0)
			sc = "Present";
		else
			sc = "Not Present";
		printf("%d\t%s\t%d\t%d\t%s\n", i, tmp->name, tmp->numBurger,tmp->numSalad, sc);

		i++;
		tmp = tmp->next;
		counter++;
	}
}


void retrieveAndRemove(ticketList** hd, int nb, int ns){
	ticketList *tmp = *hd;
	ticketList *z;
	int i = 1;
	
	if(tmp == NULL){
		printf("The list is empty\n");
		return;
	}
	
	if(tmp->numBurger <= nb && tmp->numSalad <= ns && tmp->status == 0){
		*hd = (*hd)->next;
		free(tmp);
		return;
	}
	
	while(tmp->next != NULL)
	{
		if(tmp->next->numBurger <= nb && tmp->next->numSalad <= ns)
		{
			if(tmp->next->status == 0){
				z = tmp->next;
				tmp->next = z->next;
				
				free(z);
				return;
			}
		}
		tmp = tmp->next;
	}
	
	printf("No valid order available\n");
}

int countOrdersAhead(ticketList **hd, char *name){
	ticketList *tmp = *hd;
	if(tmp == NULL)
		return 0;
	int result = 0;
	int i = 1;
	
	while(tmp != NULL){
		if(strcmp(tmp->name, name) == 0){
			return result;
		}
		result++;
		tmp = tmp->next;
	}
	return 0;
}

int updateStatus(ticketList** hd, char *name)
{
	int i = 1;
	ticketList *tmp = *hd;
	if(tmp == NULL){
		printf("List is empty\n");
		return FALSE;
	}
	
	while(tmp != NULL){
		if(strcmp(tmp->name, name) == 0){
			if(tmp->status == 0)
				return FALSE;
			else{
				tmp->status = 0;
				return TRUE;
			}
		}
		tmp = tmp->next;
	}
	return FALSE;
}

int totalBurgers(ticketList** hd, char* name)
{
	ticketList *tmp = *hd;
	if(tmp == NULL)
		return 0;
	int result = 0;
	
	while(tmp != NULL){
		if(strcmp(tmp->name, name) == 0){
			return result;
		}
		result = result + tmp->numBurger;
		tmp = tmp->next;
	}
	return 0;
}

int totalSalads(ticketList** hd, char* name)
{
	ticketList *tmp = *hd;
	if(tmp == NULL)
		return 0;
	int result = 0;
	int i = 1;
	
	while(tmp != NULL){
		if(strcmp(tmp->name, name) == 0){
			return result;
		}
		result = result + tmp->numSalad;
		tmp = tmp->next;
	}
	return 0;
}

void displayWaitingTime(ticketList** hd, char* name)
{
  int burgers = totalBurgers(hd,name);
  int salads = totalSalads(hd,name);
  int total = (salads*5) + (burgers*10);
  if(debugMode == TRUE)
  	printf("Burgers:%d\tSalads:%d\t", burgers, salads);
  printf("Total waiting time is %d minutes\n", total);
}
