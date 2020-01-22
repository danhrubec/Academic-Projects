//
// Lab week 06: AVL testing, example of visual testing vs. unit testing
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "avl.h"

using namespace std;


int main()
{
  avltree<int, int>  avl;

  //
  // build tree:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);
  avl.insert(150, -150);
  avl.insert(125, -125);

  //
  // output for visual inspection:
  //
  cout << "Size: " << avl.size() << endl;
  cout << "Height: " << avl.height() << endl;
  avl.inorder();

  cout << endl;

  //
  // run unit tests and output results:
  //
  vector<int>  keys, values, heights;

  int passed = 0;
  int failed = 0;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  if (avl.size() == 4) passed++; else failed++;
  if (avl.height() == 2) passed++; else failed++;

  if (keys[0] == 50) passed++; else failed++;
  if (heights[0] == 0) passed++; else failed++;

  if (keys[1] == 100) passed++; else failed++;
  if (heights[1] == 2) passed++; else failed++;

  if (keys[2] == 125) passed++; else failed++;
  if (heights[2] == 0) passed++; else failed++;

  if (keys[3] == 150) passed++; else failed++;
  if (heights[3] == 1) passed++; else failed++;

  cout << "# tests: " << (passed + failed) << endl;
  cout << "Passed: " << passed << endl;
  cout << "Failed: " << failed << endl;

  //
  // done:
  //
  return 0;
}
