//
// Lab Week 05: working with valgrind to detect memory leaks
// and pointer errors.
//

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <cmath>

#include "bst.h"

using namespace std;


//
// buildBST
//
// Builds a binary search tree with N nodes; it is assumed you
// declare an empty tree locally and then pass it as a parameter.
// This avoids the need for copying the tree, and having a copy
// constructor.
//
void buildBST(binarysearchtree<int>& tree, int N)
{
  std::random_device random_device;
  std::mt19937 random_engine(random_device());
  std::uniform_int_distribution<int> distributionAgent(1, N*10);

  while (tree.size() < N)
  {
    int ranInt = distributionAgent(random_engine);
    tree.insert(ranInt);
  }
}


//
// timeOneBST
//
// Builds a binary search tree filled with N random integers.
// Outputs the time it takes to build this tree, along with
// tree height.
//
void timeOneBST(int N)
{
  binarysearchtree<int>  tree;

  cout << "N=" << N << ": ";

  auto start = chrono::high_resolution_clock::now();

  buildBST(tree, N);

  auto end = chrono::high_resolution_clock::now();
  auto diff = end - start;
  auto timeInMs = chrono::duration <double, milli>(diff).count();

  cout << " Time: " << std::round(timeInMs) << " ms" << ",";
  cout << " Height: " << tree.height() << endl;
}


int main(int argc, char* argv[])
{
  int  lower, upper;

  if (argc < 3)
  {
    cout << "Please enter lower-bound> ";
    cin >> lower;

    cout << "Please enter upper-bound> ";
    cin >> upper;
  }
  else
  {
    lower = std::stoi(argv[1]);
    upper = std::stoi(argv[2]);
  }


  //
  // BST:
  //
  cout << "Binary Search Tree: " << endl;
  for (int N = lower; N <= upper; N = N * 2)
  {
    timeOneBST(N);
  }
  cout << endl;


  //
  // test out clearing the tree:
  
  binarysearchtree<int> T;
  
  buildBST(T, 100);
  
  cout << "Before clear:" << endl;
  cout << " Size: " << T.size() << endl;
  cout << " Height: " << T.height() << endl;
  
  T.clear();
  
  cout << "After clear:" << endl;
  cout << " Size: " << T.size() << endl;
  cout << " Height: " << T.height() << endl;


  //
  // done:
  //
  return 0;
}
