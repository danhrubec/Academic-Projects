/*bsh.h*/

//
// Binary search tree
//


//Dan Hrubec
//project 2
//cs 251


#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std;



template<typename TKey, typename TValue>
class binarysearchtree
{
private:
  struct NODE
  {
    TKey  Key;
	TValue value; // adding the value part to the key value pair of the tree
    NODE* Left;
    NODE* Right;
  };
  

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  //
  // _height does the actual work of computing height, recursively.
  //
  int _height(NODE* cur)
  {
    if (cur == nullptr)
      return -1;
    else
    {
      int heightL = _height(cur->Left);
      int heightR = _height(cur->Right);

      return 1 + std::max(heightL, heightR);
    }
  }

  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
  void _inorder(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder(cur->Left);
      cout << "Key: " << cur->Key << " Value: " << cur->value << endl;
      _inorder(cur->Right);
    }
  }
  
  //free tree is used for properly deallocating all the memory in the tree
  //it does a post order traversal of the tree and after the recursive call it deletes the current node
  //so in theory it will delete all the leaves of the tree first, then the branches and ultimately the root
  void _freeTree(NODE* cur)
  {
	  if(cur == nullptr)
		  return;
      else
	  {
		 _freeTree(cur->Left);
		 _freeTree(cur->Right);
		 delete cur;
	  }
  
  
  }
  
  //copy helper is private function that does all the background work for the copy constructor
  //like the other public functions that we have had. so this does a pre order traversal of the tree
  //and inserts the node from the old tree into the new tree and then goes to the left and right and does the same
  //also taking advantage of the insert function that we already wrote.
  void copyHelper(NODE* current)
  {
	  if(current == nullptr) // exits the recursive call if the current node is null
		  return;
	  else
	  {//pre order traversal of the tree using the insert function to copy it
		  insert(current->Key, current->value);
		  copyHelper(current->Left);
		  copyHelper(current->Right);
	  }
  
  }

public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }
  
  //Copy constructor!!! YAY
  //Takes a different tree and stores it into this tree. In the case that the tree is already full
  //i delete whatever was in the tree before i start the copy constructor process
  
  binarysearchtree(binarysearchtree& copyTree)
  {
	  _freeTree(Root); //freeing the tree if anything was left in it before the copy constructor
	  Root = nullptr; // reseting the root back to null
	  
	  copyHelper(copyTree.Root); // sending in the root of the one being copied
	  
	  Size = copyTree.Size; // copies the size as well
  
  }

  //
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~binarysearchtree()
  {
    _freeTree(Root);
  }

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  //
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  //
  int height()
  {
    return _height(Root);
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return &(cur->value);

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  

    // if get here, not found
    return nullptr;
  }


	
	
  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  void insert(TKey key, TValue val)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 
    NODE* newNode;
    newNode = new NODE();
    newNode->Key = key;
	newNode->value = val;
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr)
	{
      Root = newNode;
	  
	}
    else if (key < prev->Key)
	{
      prev->Left = newNode;
	  
	}
    else
	{
		prev->Right = newNode;
	}
      

    // 
    // 4. update size and we're done:
    //
    Size++;
  }

  //
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder()
  {
    cout << "Inorder: ";

    _inorder(Root);

    cout << endl;
  }

  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    //
    // Re-initialize root pointer and size to "empty":
    //
    
	_freeTree(Root); // this is the private helper function that is doing the work in the background
    Root = nullptr;
    Size = 0;
    
   
  }

};
