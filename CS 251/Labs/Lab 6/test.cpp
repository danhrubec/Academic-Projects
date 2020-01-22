/*test.cpp*/

//
// An AVL unit test based on Catch framework
//

#include <iostream>
#include <vector>
#include <string>

#include "avl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) AVL tree with 4 nodes") 
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 4 nodes:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);
  avl.insert(150, -150);
  avl.insert(125, -125);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 4);
  REQUIRE(avl.height() == 2);

  REQUIRE(keys[0] == 50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 125);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 150);
  REQUIRE(heights[3] == 1);
}

TEST_CASE("(2) Empty AVL Tree")
{
	avltree<int,int> avl;
	
	REQUIRE(avl.size() == 0);
	REQUIRE(avl.height() == -1);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	REQUIRE(keys.empty() == true);
	REQUIRE(values.empty() == true);
	REQUIRE(heights.empty() == true);
	
	
	
}

TEST_CASE("(3) AVL with 1 node")
{
	avltree<int,int> avl;
	
	avl.insert(50,10);
	
	REQUIRE(avl.size()==1);
	REQUIRE(avl.height()==0);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 50);
	REQUIRE(values[0] == 10);
	REQUIRE(heights[0] == 0);
}

TEST_CASE("(4) AVL height of root as LL")
{
	avltree<int,int> avl;
	
	avl.insert(0,10);
	avl.insert(10,20);
	avl.insert(20,30);
	avl.insert(30,40);
	avl.insert(40,50);
	avl.insert(50,60);
	avl.insert(60,70);
	avl.insert(70,80);
	
	REQUIRE(avl.size() == 8);
	REQUIRE(avl.height() == 7);
	
	vector<int> heights;
	heights = avl.inorder_heights();
	
	REQUIRE(heights[0] == 7);
}


TEST_CASE("(5) small AVL Tree")
{
	avltree<int,int> avl;
	
	avl.insert(50,1);
	avl.insert(30,2);
	avl.insert(20,3);
	avl.insert(35,4);
	avl.insert(75,5);
	avl.insert(70,6);
	avl.insert(80,8);
	
	REQUIRE(avl.size() == 7);
	REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 20);
	REQUIRE(values[0] == 3);
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 30);
	REQUIRE(values[1] == 2);
	REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 35);
	REQUIRE(values[2] == 4);
	REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 50);
	REQUIRE(values[3] == 1);
	REQUIRE(heights[3] == 2);
	
	REQUIRE(keys[4] == 70);
	REQUIRE(values[4] == 6);
	REQUIRE(heights[4] == 0);
	
	
}

TEST_CASE("(6) AVL with different data types")
{
	avltree<char,char> avl;
	
	avl.insert('d','z');
	avl.insert('a', 'y');
	avl.insert('n', 'w');
	
	vector<int> heights;
	vector<char> keys, values;
	
	keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 'a');
	REQUIRE(values[0] == 'y');
	REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 'd');
	REQUIRE(values[1] == 'z');
	REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 'n');
	REQUIRE(values[2] == 'w');
	REQUIRE(heights[2] == 0);
	
	
}

TEST_CASE("(7) Larger AVL")
{
	avltree<int,int> avl;
	
	int i;
	
	//tree with 100 elements
	for(i=0;i<100;i++)
	{
		avl.insert(i,i);
	}
	
	
	
	REQUIRE(avl.size() == 100);
	REQUIRE(avl.height() == 99);
	
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	REQUIRE(keys[42] == 42);
	REQUIRE(values[42] == 42);
	REQUIRE(heights[42] == 57);
	
}

TEST_CASE("(8) Duplicates in AVL")
{
	avltree<int,int> avl;
	
	avl.insert(20,5);
	avl.insert(20,4);
	avl.insert(20,4);
	avl.insert(20,4);
	avl.insert(20,4);
	avl.insert(20,4);
	avl.insert(20,4);
	avl.insert(20,4);
	
	REQUIRE(avl.size() == 1);
	REQUIRE(avl.height() == 0);
	
	
	
}
