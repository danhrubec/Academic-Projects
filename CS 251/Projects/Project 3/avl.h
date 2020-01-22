
//Dan Hrubec
//dhrube2
//avl.h taken from hw08 and added to it

#pragma once

#include <iostream>
#include <algorithm>  // std::max
#include <cstdlib>    // std::abs
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

template<typename TKey, typename TValue>
class avltree
{
private:
  struct NODE
  {
    TKey   Key;
    TValue Value;
    int    Height;
    NODE*  Left;
    NODE*  Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
	
	
	//helper function mainly used in the getDistance portion of
	//the program. it searches for a node and keeps a counter for
	//how many nodes it took to reach this point
	int searchNodeint(TKey key)
	{
			NODE* cur = Root;
			int counter = 0;
			while (cur != nullptr)
			{
      if (key == cur->Key)  // already in tree
      {
        return counter;
      }

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
				counter++;
      }
      else
      {
        cur = cur->Right;
				counter++;
      }
    }//while  

    // if get here, not found
    return -1;
	
	}
	
	//another helper function for the distance function. it uses recursion
	//to find the node in the tree and returns that node
	NODE* getDist(TKey key1, TKey key2, NODE* cur)
	{

		
		if(cur->Key < key1 && cur->Key < key2)
		{
			return getDist(key1, key2,cur->Right);
		}
		else if(cur->Key > key1 && cur->Key > key2)
		{
			return getDist(key1, key2, cur->Left);
		}
		
		return cur;
	
	}
	
	//same thing as the search function but made private. this will return the
	//node if found in the tree. used in the distance function.
	NODE* searchNode(TKey key)
	{
			NODE* cur = Root;
			while (cur != nullptr)
			{
      if (key == cur->Key)  // already in tree
      {
        return cur;
      }

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
	
	//simple function used to get the height of a particular node.
	//again i mainly used this in the distance function to get the heights
	//of the two nodes that we are trying to get the distance of.
	int _getHeight(NODE *cur)
	{
		if (cur == nullptr)
		{
			return -1;
		}

		int lh = _getHeight(cur->Left); 
		int rh = _getHeight(cur->Right);
		return 1 + max(lh, rh);
	}
	
	//this is the main part of the AVL. Rotate to fix is what rebalances the tree if it is breaking
	//it takes in three parameters, the parent,the place where it broke, and the key we are trying to
	//insert. it checks if it even needs to be rebalanced in the first place. then checks for all
	//cases of the tree, LR, RR, RR then LR or LR then RR.
	void _RotateToFix(NODE* Parent, NODE* N, TKey Key)
	{
		assert(N != nullptr);
		
		int leftHeight = -1;
		int rightHeight = -1;
		
		if(N->Left != nullptr)
		{
			leftHeight = N->Left->Height;
		}
		
		if(N->Right != nullptr)
		{
			rightHeight = N->Right->Height;
		
		}


		int heightDiff = abs(leftHeight - rightHeight);
		//cout << "Hdiff: " << heightDiff << endl;
		//cout << "HL: " << leftHeight << endl;
		//cout << "HR: " << rightHeight << endl;
	
		/*
		if(leftHeight > rightHeight && heightDiff > 1)
		{
			if(Key < N->Left->Key) // case 1.
			{
					_RightRotate(Parent,N);
			}
			else
			{
					//case 2
					_LeftRotate(N,N->Left);
					_RightRotate(Parent,N);
			}
		
		
		}
		else if(rightHeight > leftHeight && heightDiff > 1)
		{
				if(Key > N->Right->Key)
				{
					_LeftRotate(Parent, N);
				}
				else
				{
					_RightRotate(N, N->Right);
					_LeftRotate(Parent,N);
				
				}
		}
		*/
		
		
		if(rightHeight > leftHeight && heightDiff > 1)
		{
		if(N->Right != nullptr)
		{
				if(Key > N->Right->Key)
				{
					//cout << "enter case 1" << endl;
					_LeftRotate(Parent, N);
				}
				else
				{
					//cout << "enter case 2" << endl;
					_RightRotate(N, N->Right);
					
					_LeftRotate(Parent,N);
				
				}
		}
		
		}
		else if(leftHeight > rightHeight && heightDiff > 1)
		{
			if(N->Left != nullptr)
			{
				if(Key < N->Left->Key) // case 3.
				{
					//cout << "enter case 3" << endl;
						_RightRotate(Parent,N);
				}
				else
				{
					//case 4
						//cout << "enter case 4" << endl;
						//cout << "Nkey: " << N->Key << endl;
						//cout << "NLKey: " << N->Left->Key << endl;
						_LeftRotate(N,N->Left);
						_RightRotate(Parent,N);
				}
		
		}
		
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
      cout << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
      _inorder(cur->Right);
    }
  }

	//a helper function mainly used to test the functionality of the avltree
	//sets a vector equal to all of the keys of the tree in order
  void _inorder_keys(NODE* cur, std::vector<TKey>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_keys(cur->Left, V);
      V.push_back(cur->Key);
      _inorder_keys(cur->Right, V);
    }
  }
	
	//also a helper function used in the testing phase of the project. Given to us in HW08, it
	//will be used to to print out all the values of the nodes in the tree in order. Useful for testing
	//trees to make sure they are functioning as they should.
  void _inorder_values(NODE* cur, std::vector<TValue>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_values(cur->Left, V);
      V.push_back(cur->Value);
      _inorder_values(cur->Right, V);
    }
  }
	
	//helper function. As with the with other inorder functions this primarily helps during
	//testing to ensure that the heights are being updated and the tree is rotating. It helps
	//make sure the functionality of the avl is there.
	
  void _inorder_heights(NODE* cur, std::vector<int>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_heights(cur->Left, V);
      V.push_back(cur->Height);
      _inorder_heights(cur->Right, V);
    }
  }

  //
  // _copytree:
  //
  // Given a tree, inserts the (key, value) pairs into *this* tree.
  //
  void _copytree(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      //
      // to copy and build an exact copy, we need to "visit" cur
      // first and insert that (key, value) pair first.  That way
      // all the nodes to the left will properly go to the left,
      // all the node to the right will properly go to the right.
      //
      insert(cur->Key, cur->Value);

      _copytree(cur->Left);
      _copytree(cur->Right);
    }
  }

  //
  // _RightRotate
  // _LeftRotate
  //
  // Rotates the tree around the node N, where Parent is N's parent.  Note that
  // Parent could be null, which means N is the root of the entire tree.  If 
  // Parent denotes a node, note that N could be to the left of Parent, or to
  // the right.  You'll need to take all this into account when linking in the
  // new root after the rotation.  Don't forget to update the heights as well.
  //
  void _RightRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and L must exist
    assert(N->Left != nullptr);

    //
    // TODO
    //
    
		//cout << "start RR" << endl;
    //assigning parts of the trees per graphs in class
    NODE* partL = N->Left;
    //NODE* partA = partL->Left;
    NODE* partB = partL->Right;
    //NODE* partC = N->Right;
    
    N->Left = partB;
    partL->Right = N;
		
    
    if(Parent == nullptr)
    {
      Root = partL;
    }
    else if(partL->Key < Parent->Key)
    {
       Parent->Left = partL;
    }
    else
    {
       Parent->Right = partL;
    }
		
		
    
    if(N->Left == nullptr && N->Right == nullptr)
    {
        N->Height = 0;
    }
    else if(N->Left == nullptr)
    {
      N->Height = 1 + N->Right->Height;  
    }
    else if(N->Right == nullptr)
    {
      N->Height = 1+N->Left->Height;  
    }
    else
    {
       N->Height = 1+ max(N->Left->Height, N->Right->Height);
    }
    
		if(partL->Left == nullptr)
         partL->Height = 1 + N->Height;
    else
        partL->Height = 1+max(partL->Left->Height, N->Height);
  
    
  }

  void _LeftRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and R must exist
		assert(N->Right != nullptr);

    //
    // TODO
    //

    NODE* partR = N->Right;
		
    //NODE* partA = partR->Left;
    NODE* partB = partR->Left;
    //NODE* partC = N->Left;
    
    N->Right = partB;
    partR->Left = N;
    
    if(Parent == nullptr)
    {
      Root = partR;
    }
    else if(partR->Key < Parent->Key)
    {
       Parent->Left = partR;
    }
    else
    {
       Parent->Right = partR;
    }
    
   
    if(N->Left == nullptr && N->Right == nullptr)
    {
        N->Height = 0;
    }
    else if(N->Left == nullptr)
    {
      N->Height = 1 + N->Right->Height;  
    }
    else if(N->Right == nullptr)
    {
      N->Height = 1+N->Left->Height;  
    }
    else
    {
      N->Height = 1+ max(N->Left->Height, N->Right->Height);
    }
    
		
		if(partR->Right == nullptr)
		{
         partR->Height = 1 + N->Height;
		}
    else
		{
			
        partR->Height = 1+max(N->Height, partR->Right->Height);
		}


  }
	//very similar to the delete function for a regular BST,
	//it goes and deletes all the nodes and does a post order traversal
	//to free them all
	
	void deleteTree(NODE* cur)
	{
		if(cur == nullptr)
			return;
		
		//post order traversal for deleteTree
		
		deleteTree(cur->Left);
		deleteTree(cur->Right);
		delete cur;
	
	}

public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  avltree()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor:
  //
  avltree(avltree& other)
  {
    Root = nullptr;
    Size = 0;

    _copytree(other.Root);
  }
	
	//destuctor for the AVL tree. it calls the deleteTree helper function and
	//sends in the Root. It then will do a post order traversal for the tree and 
	//delete the current node only after all the leaf nodes have been deleted
	virtual ~avltree()
	{
	
		deleteTree(Root);
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
  // Returns the height of tree; the height of an empty tree is
  // defined as -1.
  //
  int height()
  {
			return(_getHeight(Root));
  }
	
	//same idea here as the destructor. The destructor automatically frees the memory
	//after the program is done, clear is if you want to do it somewhere in the middle of the 
	//program. it calls the deleteTree helper function. but after it is done, it resets
	//the size and the root
	void clear()
	{
		deleteTree(Root);
		Size = 0;
		Root = nullptr;
	
	}
	
	//one of the added functions to the avl tree class. tries to find the distance
	//between two nodes if they exist in the AVL. if either node does not exist, then
	//it will return -1. if it is the same node it will return 0. if it is two random nodes 
	//it will return the shortest distance between the two nodes.
	int distance (TKey k1, TKey k2)
	{

		//getting the distance from the two nodes in question to the root
		//adds the two values together and stores them into totaldist
		int dist1 = searchNodeint(k1);
		int dist2 = searchNodeint(k2);
		int totaldist = dist1+dist2;
		
		//cant use regular search as it returns the value
		//need to return the node so we need to use a helper function
		NODE* node1 = searchNode(k1);
		NODE* node2 = searchNode(k2);
		
		
		//some base cases. it checks if the two nodes we are
		//getting the distance of exists. if either do not exists then 
		//we exit the function as we could not take the distance of a node that
		//does not exist.
		if(node1 == nullptr || node2 == nullptr)
			return -1;
			
		if(k1==k2)
			return 0;
		
		NODE* nnode = getDist(k1,k2, Root);
		
		int totalHeight = height();
		int subHeight = _getHeight(nnode);
		subHeight = abs(totalHeight - subHeight);
		return abs(totaldist -2*subHeight);
	
	}
  // 
  // search:
  //
  // Searches the tree for the given key, returning a pointer to the 
  // value if found and nullptr if not.  We return a pointer so the caller
  // may update the underlying value if needed.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        return &cur->Value;
      }

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
  // Inserts the given (key, value) pair into the tree; if the key has 
  // already been inserted then the function returns without changing 
  // the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodes;


    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      nodes.push(cur);  // stack so we can return later:
	;

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
    newNode->Value = value;
    newNode->Height = 0;  // leaf node -> sub-tree of height 0:
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
      Root = newNode;
    else if (key < prev->Key)
      prev->Left = newNode;
    else
      prev->Right = newNode;

    // 
    // 4. update size:
    //
    Size++;

    //
    // 5. walk back up tree using stack and update heights.
    
		
    while (!nodes.empty())
    {
			
      cur = nodes.top();
      nodes.pop();
			
      int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
      int hCur = 1 + std::max(hL, hR);

      if (cur->Height == hCur)  // didn't change, so no need to go further:
        break;
      else  // height changed, update and keep going:
        cur->Height = hCur;
				
				
			//now checking if we need to rotate the tree. the node is already
			//inserted at this point in time, now we are climbing back up the tree
			//to see if it breaks at any point. if it does it will call rotate to fix
			//we do not need to check the different cases in this function. only in the rotate to fix function
			
			
			NODE* Nnode;
			if(nodes.size())
			{
				Nnode = nodes.top();
			
			}
			else
			{
				Nnode = nullptr;
			}
			_RotateToFix(Nnode, cur,key);

    }
	

    return;
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

	//calls private helper function to perform this task via recursion
  std::vector<TKey> inorder_keys()
  {
    std::vector<TKey>  V;

    _inorder_keys(Root, V);

    return V;
  }
	//along with the other also utilizes the private helper function to 
	//display the values of the nodes in order using in order traversal
  std::vector<TValue> inorder_values()
  {
    std::vector<TValue>  V;

    _inorder_values(Root, V);

    return V;
  }

	//same story here, provides the heights of the nodes and stores them in a vector
	//does this via recursion of a private helper function
  std::vector<int> inorder_heights()
  {
    std::vector<int>  V;

    _inorder_heights(Root, V);

    return V;
  }

  

};
