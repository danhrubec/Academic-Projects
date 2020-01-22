//Dan Hrubec
//dhrube2
//test.cpp taken from lab7

#include <iostream>
#include <vector>

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
  REQUIRE(values[0] == -50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(values[1] == -100);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 125);
  REQUIRE(values[2] == -125);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 150);
  REQUIRE(values[3] == -150);
  REQUIRE(heights[3] == 1);
	
  // Distance between for all values
  REQUIRE(avl.distance(100, 50) == 1);
  REQUIRE(avl.distance(50, 100) == 1);
  REQUIRE(avl.distance(100, 150) == 1);
  REQUIRE(avl.distance(150, 100) == 1);
  REQUIRE(avl.distance(100, 125) == 2);
  REQUIRE(avl.distance(125, 100) == 2);
  REQUIRE(avl.distance(125, 50) == 3);
  REQUIRE(avl.distance(50, 125) == 3);
  REQUIRE(avl.distance(50, 150) == 2);	
  REQUIRE(avl.distance(150, 50) == 2);
  REQUIRE(avl.distance(100, 100) == 0);


}

TEST_CASE("(2) empty tree") 
{
  avltree<int, int>  avl;

  //REQUIRE(avl._getRoot() == nullptr);
  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);
  REQUIRE(avl.distance(100, 50) == -1);
	
}

TEST_CASE("(3) just one node") 
{
  avltree<int, int>  avl;
	
	avl.insert(123, 88);

  REQUIRE(avl.size() == 1);
  REQUIRE(avl.height() == 0);
  REQUIRE(avl.distance(123, 123) == 0);
  REQUIRE(avl.distance(123, 125) == -1);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 123);
	REQUIRE(values[0] == 88);
    REQUIRE(heights[0] == 0);
}

TEST_CASE("(4) LR at the root")
{
	avltree<int,int> avl;
	
	avl.insert(69,1);
	avl.insert(420,100);
	REQUIRE(avl.distance(69, 420) == 1);
	REQUIRE(avl.distance(100, 50) == -1);
	avl.insert(42069,150);
	REQUIRE(avl.distance(42069, 420) == 1);
	REQUIRE(avl.distance(69, 420) == 1);
    REQUIRE(avl.distance(42069, 69) == 2);

  
  
	
	
	REQUIRE(avl.size() == 3);
    REQUIRE(avl.height() == 1);
	
	vector<int>  keys, values, heights;
	keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	
	REQUIRE(keys[0] == 69);
	REQUIRE(values[0] == 1);
    REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 420);
	REQUIRE(values[1] == 100);
    REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 42069);
	REQUIRE(values[2] == 150);
    REQUIRE(heights[2] == 0);
	REQUIRE(avl.distance(42069, 420) == 1);
	REQUIRE(avl.distance(69, 420) == 1);
    REQUIRE(avl.distance(42069, 69) == 2);
}

TEST_CASE("(5) RR at Root")
{
	avltree<int,int> avl;
	
	
	
	avl.insert(42069,150);
	avl.insert(420,100);
	avl.insert(69,1);
	
	REQUIRE(avl.distance(100, 50) == -1);

	
	REQUIRE(avl.distance(42069, 420) == 1);
	REQUIRE(avl.distance(69, 420) == 1);
    REQUIRE(avl.distance(42069, 69) == 2);
	
	REQUIRE(avl.size() == 3);
  REQUIRE(avl.height() == 1);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	
	REQUIRE(keys[0] == 69);
	REQUIRE(values[0] == 1);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 420);
	REQUIRE(values[1] == 100);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 42069);
	REQUIRE(values[2] == 150);
  REQUIRE(heights[2] == 0);
	
}

TEST_CASE("(6) LR then RR w/ bigger tree")
{
	
	avltree<int,int> avl;
	
	avl.insert(256,256);
	avl.insert(202,202);
	avl.insert(310,310);
	avl.insert(157,157);
	avl.insert(302,302);
	avl.insert(222,222);
	avl.insert(319,319);
	avl.insert(109,109);
	avl.insert(162,162);
	avl.insert(177,177);
	
	REQUIRE(avl.distance(999, 177) == -1);
	REQUIRE(avl.distance(177, 999) == -1);
	
	REQUIRE(avl.distance(998, 999) == -1);
	REQUIRE(avl.distance(999, 999) == -1);
	
	REQUIRE(avl.size() == 10);
	REQUIRE(avl.height() == 3);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	REQUIRE(keys[0] == 109);
	REQUIRE(values[0] == 109);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 157);
	REQUIRE(values[1] == 157);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 162);
	REQUIRE(values[2] == 162);
  REQUIRE(heights[2] == 2);
	
	REQUIRE(keys[3] == 177);
	REQUIRE(values[3] == 177);
  REQUIRE(heights[3] == 0);
	
	REQUIRE(keys[4] == 202);
	REQUIRE(values[4] == 202);
  REQUIRE(heights[4] == 1);
	
	REQUIRE(keys[5] == 222);
	REQUIRE(values[5] == 222);
  REQUIRE(heights[5] == 0);
	
	REQUIRE(keys[6] == 256);
	REQUIRE(values[6] == 256);
  REQUIRE(heights[6] == 3);
	
	REQUIRE(keys[7] == 302);
	REQUIRE(values[7] == 302);
  REQUIRE(heights[7] == 0);
	
	REQUIRE(keys[8] == 310);
	REQUIRE(values[8] == 310);
  REQUIRE(heights[8] == 1);
	
	REQUIRE(keys[9] == 319);
	REQUIRE(values[9] == 319);
  REQUIRE(heights[9] == 0);
	
	REQUIRE(avl.distance(256, 162) == 1);
	REQUIRE(avl.distance(256, 310) == 1);
	REQUIRE(avl.distance(256, 157) == 2);
	REQUIRE(avl.distance(256, 202) == 2);
	REQUIRE(avl.distance(256, 177) == 3);
	REQUIRE(avl.distance(256, 222) == 3);
	REQUIRE(avl.distance(256, 109) == 3);
	REQUIRE(avl.distance(256, 302) == 2);
	REQUIRE(avl.distance(256, 319) == 2);
	REQUIRE(avl.distance(1000, 989) == -1);
	
	
}


TEST_CASE("(7) Double rotate left")
{
	
	avltree<int,int> avl;
	
	avl.insert(55,55);
	avl.insert(42,42);
	avl.insert(65,65);
	avl.insert(60,60);
	avl.insert(88,88);
	avl.insert(62,62);
	
	
	REQUIRE(avl.distance(55, 55) == 0);
	REQUIRE(avl.distance(42, 55) == 1);
	REQUIRE(avl.distance(65, 55) == 2);
	REQUIRE(avl.distance(60, 55) == 1);
	REQUIRE(avl.distance(62, 55) == 3);
	REQUIRE(avl.distance(1000, 989) == -1);
	
	REQUIRE(avl.distance(999, 177) == -1);
	REQUIRE(avl.distance(177, 999) == -1);
	
	REQUIRE(avl.distance(998, 999) == -1);
	REQUIRE(avl.distance(999, 999) == -1);

	
	
	
	REQUIRE(avl.size() == 6);
  REQUIRE(avl.height() == 2);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	
	REQUIRE(keys[0] == 42);
	REQUIRE(values[0] == 42);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 55);
	REQUIRE(values[1] == 55);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 60);
	REQUIRE(values[2] == 60);
  REQUIRE(heights[2] == 2);
	
	REQUIRE(keys[3] == 62);
	REQUIRE(values[3] == 62);
  REQUIRE(heights[3] == 0);
	
	REQUIRE(keys[4] == 65);
	REQUIRE(values[4] == 65);
  REQUIRE(heights[4] == 1);
	
	REQUIRE(keys[5] == 88);
	REQUIRE(values[5] == 88);
  REQUIRE(heights[5] == 0);
	
}

TEST_CASE("(8) duplicate node check")
{
	
	avltree<int,int> avl;
	
	avl.insert(69,69);
	avl.insert(69,69);
	avl.insert(69,69);
	avl.insert(69,69);
	avl.insert(69,69);
	avl.insert(69,69);
	avl.insert(69,69);
	
	REQUIRE(avl.distance(69, 69) == 0);
	REQUIRE(avl.distance(69, 69) == 0);
	
	
	REQUIRE(avl.distance(999, 177) == -1);
	REQUIRE(avl.distance(177, 999) == -1);
	
	REQUIRE(avl.distance(998, 999) == -1);
	REQUIRE(avl.distance(999, 999) == -1);
	
	
	REQUIRE(avl.size() == 1);
  REQUIRE(avl.height() == 0);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 69);
	REQUIRE(values[0] == 69);
  REQUIRE(heights[0] == 0);
	
}

TEST_CASE("(9) Inserting in Ascending Order")
{
	avltree<int,int> avl;
	
	avl.insert(0,0);
	avl.insert(1,1);
	avl.insert(2,2);
	avl.insert(3,3);
	avl.insert(4,4);
	avl.insert(5,5);
	avl.insert(6,6);
	avl.insert(7,7);
	avl.insert(8,8);
	avl.insert(9,9);
	
	REQUIRE(avl.distance(1, 1) == 0);
	REQUIRE(avl.distance(5, 9) == 3);
	
	
	REQUIRE(avl.distance(999, 177) == -1);
	REQUIRE(avl.distance(177, 999) == -1);
	
	REQUIRE(avl.distance(998, 999) == -1);
	REQUIRE(avl.distance(999, 999) == -1);
	
	
	REQUIRE(avl.size() == 10);
  REQUIRE(avl.height() == 3);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	
	REQUIRE(keys[0] == 0);
	REQUIRE(values[0] == 0);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 1);
	REQUIRE(values[1] == 1);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 2);
	REQUIRE(values[2] == 2);
  REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 3);
	REQUIRE(values[3] == 3);
  REQUIRE(heights[3] == 3);
	
	REQUIRE(keys[4] == 4);
	REQUIRE(values[4] == 4);
  REQUIRE(heights[4] == 0);
	
	REQUIRE(keys[5] == 5);
	REQUIRE(values[5] == 5);
  REQUIRE(heights[5] == 1);
	
	REQUIRE(keys[6] == 6);
	REQUIRE(values[6] == 6);
  REQUIRE(heights[6] == 0);
	
	REQUIRE(keys[7] == 7);
	REQUIRE(values[7] == 7);
  REQUIRE(heights[7] == 2);
	
	REQUIRE(keys[8] == 8);
	REQUIRE(values[8] == 8);
  REQUIRE(heights[8] == 1);
	
	REQUIRE(keys[9] == 9);
	REQUIRE(values[9] == 9);
  REQUIRE(heights[9] == 0);
	
}

TEST_CASE("(10) Copy Constructor")
{
	avltree<int,int> avl;
	
	avl.insert(0,0);
	avl.insert(1,1);
	avl.insert(2,2);
	avl.insert(3,3);
	avl.insert(4,4);
	avl.insert(5,5);
	avl.insert(6,6);
	avl.insert(7,7);
	avl.insert(8,8);
	avl.insert(9,9);
	
	avltree<int, int> avl2 = avl;
	
	
	REQUIRE(avl2.distance(1, 1) == 0);
	REQUIRE(avl2.distance(5, 9) == 3);
	
	
	REQUIRE(avl2.distance(999, 177) == -1);
	REQUIRE(avl2.distance(177, 999) == -1);
	
	REQUIRE(avl2.distance(998, 999) == -1);
	REQUIRE(avl2.distance(999, 999) == -1);
	
	
	REQUIRE(avl2.size() == 10);
  REQUIRE(avl2.height() == 3);
	
	vector<int>  keys, values, heights;
	
	keys = avl2.inorder_keys();
  values = avl2.inorder_values();
  heights = avl2.inorder_heights();
	
	
	REQUIRE(keys[0] == 0);
	REQUIRE(values[0] == 0);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 1);
	REQUIRE(values[1] == 1);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 2);
	REQUIRE(values[2] == 2);
  REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 3);
	REQUIRE(values[3] == 3);
  REQUIRE(heights[3] == 3);
	
	REQUIRE(keys[4] == 4);
	REQUIRE(values[4] == 4);
  REQUIRE(heights[4] == 0);
	
	REQUIRE(keys[5] == 5);
	REQUIRE(values[5] == 5);
  REQUIRE(heights[5] == 1);
	
	REQUIRE(keys[6] == 6);
	REQUIRE(values[6] == 6);
  REQUIRE(heights[6] == 0);
	
	REQUIRE(keys[7] == 7);
	REQUIRE(values[7] == 7);
  REQUIRE(heights[7] == 2);
	
	REQUIRE(keys[8] == 8);
	REQUIRE(values[8] == 8);
  REQUIRE(heights[8] == 1);
	
	REQUIRE(keys[9] == 9);
	REQUIRE(values[9] == 9);
  REQUIRE(heights[9] == 0);
	
}

TEST_CASE("(10) Copy Constructor & Clear")
{
	avltree<int,int> avl;
	
	avl.insert(0,0);
	avl.insert(1,1);
	avl.insert(2,2);
	avl.insert(3,3);
	avl.insert(4,4);
	avl.insert(5,5);
	avl.insert(6,6);
	avl.insert(7,7);
	avl.insert(8,8);
	avl.insert(9,9);
	
	avltree<int, int> avl2 = avl;
	
	avl.clear();
	
	REQUIRE(avl.distance(1, 2) == -1);
	REQUIRE(avl.distance(2, 3) == -1);
	
	REQUIRE(avl.distance(3, 4) == -1);
	REQUIRE(avl.distance(4, 5) == -1);
	
	REQUIRE(avl.size() == 0);
	//REQUIRE(avl._getRoot() == nullptr);
	REQUIRE(avl.height() == -1);
	REQUIRE(avl2.size() == 10);
    REQUIRE(avl2.height() == 3);
	
	avl.insert(1,1);
	avltree<int, int> avl3 = avl;
	
	REQUIRE(avl.size() == 1);
	REQUIRE(avl3.size() == 1);
	
	
	vector<int>  keys, values, heights;
	
	keys = avl2.inorder_keys();
  values = avl2.inorder_values();
  heights = avl2.inorder_heights();
	
	
	REQUIRE(keys[0] == 0);
	REQUIRE(values[0] == 0);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 1);
	REQUIRE(values[1] == 1);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 2);
	REQUIRE(values[2] == 2);
  REQUIRE(heights[2] == 0);
	
	REQUIRE(keys[3] == 3);
	REQUIRE(values[3] == 3);
  REQUIRE(heights[3] == 3);
	
	REQUIRE(keys[4] == 4);
	REQUIRE(values[4] == 4);
  REQUIRE(heights[4] == 0);
	
	REQUIRE(keys[5] == 5);
	REQUIRE(values[5] == 5);
  REQUIRE(heights[5] == 1);
	
	REQUIRE(keys[6] == 6);
	REQUIRE(values[6] == 6);
  REQUIRE(heights[6] == 0);
	
	REQUIRE(keys[7] == 7);
	REQUIRE(values[7] == 7);
  REQUIRE(heights[7] == 2);
	
	REQUIRE(keys[8] == 8);
	REQUIRE(values[8] == 8);
  REQUIRE(heights[8] == 1);
	
	REQUIRE(keys[9] == 9);
	REQUIRE(values[9] == 9);
  REQUIRE(heights[9] == 0);
	
}

TEST_CASE("(14) Tree rotated at root")
{
	
	avltree<int,int> avl;
	
	avl.insert(100,100);
	avl.insert(50,50);
	avl.insert(75,75);
	
	REQUIRE(avl.size() == 3);
  REQUIRE(avl.height() == 1);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();
	
	
	REQUIRE(keys[0] == 50);
	REQUIRE(values[0] == 50);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 75);
	REQUIRE(values[1] == 75);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 100);
	REQUIRE(values[2] == 100);
  REQUIRE(heights[2] == 0);
}