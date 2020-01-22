/*myvector.h*/

// 
// <Daniel Hrubec>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// 
// Project #01: myvector class that mimics std::vector, but with my own
// implemenation outlined as follows:
// I am implementing the solution mentioned in class. I will be using a linked list
// with pointers to the head and the tail with a caching system. This has a benefit to the problem of having to grow the array everytime
// the size reached the capacity. It is a lot easier to add a new node than having to copy over all the values to a new array
// each time the size reached a certain point. All data structures come with a drawback and this being that the runtime can be brutal
// up to the point of O(n^2). To alleviate the issue of the run time, I created a caching system that keeps track of the most recently
// visited node. So when traversing the linked list, the runtime is only O(1) for each node. Having this solution makes it easier to
// add new elements to the vector and address the solution to the runtime issue in most cases.


#pragma once

#include <iostream>  // print debugging
#include <cstdlib>   // malloc, free

using namespace std;

template<typename T>
class myvector
{
private:
	struct Node
	{
		T Data; // can be whatever data type, defined in main when object is created
		struct Node* next; //pointer to next node


	};

	int sz;
	struct Node* head;
	struct Node* tail;

	//This keeps track of the most recently visted node
	//acts as a kind of cache making it easier to traverse
	struct Node* lastNode;
	int lastIndex;

public:
	// default constructor, setting all values to default values
	myvector()
	{
		head = nullptr;
		tail = nullptr;
		sz = 0;

		lastNode = nullptr;
		lastIndex = -1;
	}

	// constructor which takes in an initial size. Push back the default value of T for the
	// given size via the parameter
	myvector(int initial_size)
	{
		head = nullptr;
		tail = nullptr;
		sz = 0; // size will change in the push back function when creating the linked list

		int i;
		for (i = 0; i < initial_size; i++)
		{
			push_back(T{});
		}
		lastNode = nullptr;
		lastIndex = -1;
	}

	// copy constructor for parameter passing:
	
	myvector(const myvector& other)
	{
		Node* temp = new Node;
		temp = other.head;
		this->head = nullptr;
		this->tail = nullptr;

		while (temp != nullptr)
		{
			push_back(temp->Data);
			temp = temp->next;
		}
		this->sz = other.sz;
	}
	
	//simple function, returns the current size of the vector
	int size()
	{
		return sz;
	}

	//at function, returns the data at whatever index given. This is also where the lastindex
	//and lastnode comes into play. It keeps track of the most recently visited node. So if you are
	//just traversing the Linked list, it give O(1) to the next node improving the run time
	T& at(int i)
	{
		if (i == 0)//checks if we are visited the first node
		{
			lastNode = head;
			lastIndex = 0;
			return head->Data;

		}
		else if (i == lastIndex + 1)// checks if the next node we are trying to visit is right next to
		{							// the previous node visited making it easier to access
			lastIndex++;
			lastNode = lastNode->next;
			return lastNode->Data;
		}
		else // else if lastnode and last index didn't work it will keep traverse the linked list normally
		{
			int index = 0;
			Node* temp = head;

			while (index != i)
			{
				temp = temp->next;
				index++;
			}
			lastIndex = index;
			lastNode = temp;
			return lastNode->Data;



		}
	}

	//a worse at function that will always start from the beginning of the LL
	//Does not keep track of the previous index reached. Used to test
	//run times compared to indexing the real at function

	T& worseat(int i)
	{
		int index = 0;
		Node* temp = head;

		while (index != i)
		{
			temp = temp->next;
			index++;
		}

		return temp->Data;
	}

	//override function for the [] operator. pretty much a clone of what at does. 
	//pretty much just a different way to access a particular element in the vector
	T& operator[](int i)
	{
		return at(i);
	}

	//push_back, takes in a value and puts it at the very end of the linked list.
	//it will create a new node and update the head(if it applies) and the tail accordingly and 
	//continues the chain of linked nodes using next
	void push_back(T value)
	{
		if (head == nullptr) // if the linked list is empty, it adds a new node and head and tail point to it
		{
			Node* newnode = new Node;
			newnode->Data = value;
			newnode->next = nullptr;
			head = newnode;
			tail = newnode;

		}
		else // if there is already a node, add one to the end and update the tail to now point to it
		{
			Node* newnode = new Node;
			newnode->Data = value;
			newnode->next = nullptr;
			tail->next = newnode;
			tail = newnode;
		}
		sz++;
	}


	//gives the elements between these two indexes. Will first test to see if valid parameters. It will
	//then create an array of the distance between the two and fill the array with the elements in the 
	//linked list. It will then return the pointer to the dynamic array
	T* rangeof(int i, int j)
	{
		int arrSize = j - i + 1; // subtracts the higher from the lower and adds one to properly allocate enough space
		
		T* arr = new T[arrSize]; // dynamic array from the calculated size
		
		int vpos = i; // keeps track of the index in the linked list

		for (int z = 0; z < arrSize; z++)
		{
			arr[z] = at(vpos); // assigns the array value to the linked list value
			vpos++; // updates the index for the linked list

		}
		
		return arr; //returning the dynamic array

	}

	//simple print function for testing purposes. Traverses through the linked list 
	//and prints the data at each node on a new line. Was mostly for me for personal test cases to see
	//if functions are working properly
	void print()
	{
		Node* temp = head;

		while (temp != nullptr)
		{
			cout << temp->Data << endl;
			temp = temp->next;

		}

	}

	//erase function. Takes in an index of the linked list and returns the value that was stored 
	// at that particular node. Also needed to free memory when deleting nodes to avoid memory leak
	//also need to keep track of what will happen to lastnode and lastindex if certain nodes are deleted.
	T erase(int i)
	{
		//Invalid index sent, exiting the function
		//if negative
		if (i < 0)
		{
			cout << "Negative value sent. Invalid parameter." << endl;
			return T{};
		}

		//if index sent is greater than the size of the vector
		if (i > sz)
		{
			cout << "Index is higer than the current size of the vector. Exiting function." << endl;
			return T{};

		}

		//if the vector is already empty
		if (head == nullptr)
		{
			cout << "Vector is empty." << endl;
			sz--;
			return T{};
		}
		Node* temp = new Node;
		Node* prev = new Node;

		T returnval;
		int counter = 0;

		//checking if the first index is the one being removed
		if (i == 0) 
		{
			//frees the memory for head and re-pairs the linked list and reassigns head
			temp = head->next;
			returnval = head->Data;
			delete head;
			head = temp;
			sz--;
			return returnval;
		}

		temp = head;
		prev = nullptr;
		Node* temp2 = temp;
		bool deleted = false;

		//now if the index is somewhere past the head, this wokrs if erasing tail, just need to check at the end
		if (counter < i)
		{
			while (counter != i) // traverses through the linked list until the index is reached
			{
				prev = temp;
				temp = temp->next;
				counter++;

			};
			//deletes the node in the middle and re-links the linked list
			temp2 = temp;
			returnval = temp2->Data;
			temp = temp->next;

			if (i + 1 == sz)//checks if the last number is being deleted. if so then updates the tail
			{
				delete tail;
				deleted = true;
				tail = prev;
			}

			prev->next = temp;

			if (lastIndex == i) // if the last index gets deleted, resets last index
			{
				lastIndex = -1;
				lastNode = nullptr;
			}
			else if (lastIndex > i)// shifts the index a previous node was deleted
			{
				lastIndex--;

			}
			//nothing happens if a node after lastNode gets deleted. No shift.

			
			if(deleted == false)
				delete temp2;
			//also needed to make sure to decrease the size of the linked list after a node was deleted.
			sz--;
			return returnval;

		}


	}
};