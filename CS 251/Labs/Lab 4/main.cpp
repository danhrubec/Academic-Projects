//
// Lab Week 04: inserting into binary search trees, and 
// computing the height.  Then timing the efficiency of 
// BST vs. vector and deque.
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <random>
#include <chrono>
#include <cmath>

#include "bst.h"

using namespace std;


//
// timeOneBST
//
// Builds a binary search tree filled with N random integers.
// Outputs the time it takes to build this tree, along with
// tree height.
//
void timeOneBST(unsigned long long N)
{
  binarysearchtree<int>  tree;

  cout << "N=" << N << ": ";

  std::random_device random_device;
  std::mt19937 random_engine(random_device());
  std::uniform_int_distribution<int> distributionAgent(1, 1000000000);

  auto start = chrono::high_resolution_clock::now();

  for (unsigned long long i = 0; i < N; ++i)
  {
    int ranInt = distributionAgent(random_engine);
    tree.insert(ranInt);
  }

  auto end = chrono::high_resolution_clock::now();
  auto diff = end - start;
  auto timeInMs = chrono::duration <double, milli>(diff).count();

  cout << " Time: " << std::round(timeInMs) << " ms" << ",";
  cout << " Height: " << tree.height() << endl;
}


//
// timeOneVector
//
// Builds a vector filled with N random integers, in order.
// Outputs the time it takes to fill the vector.
//
void timeOneVector(unsigned long long N)
{
  std::vector<int>  V;

  cout << "N=" << N << ": ";

  std::random_device random_device;
  std::mt19937 random_engine(random_device());
  std::uniform_int_distribution<int> distributionAgent(1, 1000000000);

  auto start = chrono::high_resolution_clock::now();

  for (unsigned long long i = 0; i < N; ++i)
  {
    int ranInt = distributionAgent(random_engine);

    std::vector<int>::iterator pos;
    pos = std::lower_bound(V.begin(), V.end(), ranInt);
    V.insert(pos, ranInt);
  }

  auto end = chrono::high_resolution_clock::now();
  auto diff = end - start;
  auto timeInMs = chrono::duration <double, milli>(diff).count();

  cout << " Time: " << std::round(timeInMs) << " ms" << endl;
}



//
// timeOneDeque
//
// Builds a deque filled with N random integers, in order.
// Outputs the time it takes to fill the deque.
//
// Recall that a deque is a vector-like data structure implemented
// using a linked-list of array chunks.
//
void timeOneDeque(unsigned long long N)
{
  std::deque<int>  DQ;

  cout << "N=" << N << ": ";

  std::random_device random_device;
  std::mt19937 random_engine(random_device());
  std::uniform_int_distribution<int> distributionAgent(1, 1000000000);

  auto start = chrono::high_resolution_clock::now();

  for (unsigned long long i = 0; i < N; ++i)
  {
    int ranInt = distributionAgent(random_engine);

    std::deque<int>::iterator pos;
    pos = std::lower_bound(DQ.begin(), DQ.end(), ranInt);
    DQ.insert(pos, ranInt);
  }

  auto end = chrono::high_resolution_clock::now();
  auto diff = end - start;
  auto timeInMs = chrono::duration <double, milli>(diff).count();

  cout << " Time: " << std::round(timeInMs) << " ms" << endl;
}


int main(int argc, char* argv[])
{
  unsigned long long  lower, upper;

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

  string netid = "MY UIC NETID: dhrube2";

  cout << endl;
  cout << "** " << netid << " **" << endl;
  cout << endl;
  
  //
  // BST:
  //
  cout << "Binary Search Tree: " << endl;
  for (unsigned long long N = lower; N <= upper; N = N * 2)
  {
    timeOneBST(N);
  }
  cout << endl;

  //
  // Vector:
  //
  cout << "Vector: " << endl;
  for (unsigned long long N = lower; N <= upper; N = N * 2)
  {
    timeOneVector(N);
  }
  cout << endl;

  //
  // Deque:
  //
  cout << "Deque: " << endl;
  for (unsigned long long N = lower; N <= upper; N = N * 2)
  {
		// Deque is MUCH slower, so we have to skip longer runs:
		if (N > 500000)
		{
			cout << "N=" << N << ": skipping" << endl;
		}
		else
		{
			timeOneDeque(N);
		}
  }
  cout << endl;
	
	//
	// Observed complexity?
	//
	cout << "Building a data structure of N elements, in order:" << endl;
	cout << " BST:    appears to be O(N)" << endl;
	cout << " Vector: appears to be O(NlogN)" << endl;
	cout << " Deque:  appears to be O(N^2)" << endl;
	cout << endl;
	
  return 0;
}
