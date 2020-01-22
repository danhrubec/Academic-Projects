/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     << Dan Hrubec >>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include <string.h>

#include "ILplates.h"

using namespace std;



//bubbleSort
//
//With permission i actually get to use this sorting method. It feels like im back in 
//intro to coding classes. anyway, takes in the 2 vectors, one for the plates and the other
//for the charges/fees. Sorts them according to the keys and then updates the values for both vectors.
//by that the vectors will need to be passed by reference.
void bubbleSort(vector<string>& Keys, vector<int>& fees)
{
	string temp;
	int temp2;
	
	for(unsigned int i = 0; i < Keys.size();i++)
	{
		for(unsigned int j = i + 1; j < Keys.size(); j++)
		{
			if(Keys[i].compare(Keys[j]) > 0)
			{
				temp = Keys[i];
				Keys[i] = Keys[j];
				Keys[j] = temp;
				
				temp2 = fees[i];
				fees[i] = fees[j];
				fees[j] = temp2;		
			}		
			
		}
		
	}
	
}

//outputFile
//
//Takes in the vector of keys and values as well as the basename for the file.
//creates an ofstream object and appends -output.txt to it naming the file accordingly
//this is called after the vectors have been sorted properly. outputs the contents in the
//correct format per the project rules
void outputFile(vector<string> Keys, vector<int> fees,string basename)
{
	string filename = basename + "-output.txt";
	ofstream ofs(filename);
	
	unsigned int i;
	
	for(i = 0; i < Keys.size();i++)
	{
		ofs << "\""<< Keys[i] << "\"" << " $" << fees[i] << endl;
		
	}
	
	
	
}
//printKeys
//
//just a supporting function. prints the keys. i used this to make sure sort was working correctly
//
void printKeys(vector<string> Keys)
{
	for(unsigned int i = 0; i < Keys.size();i++)
		cout << "Index: " << i << "\tKey: " << Keys[i] << endl;
	
	
}
//
// hashInput:
//
//given to us as skeleton code. no changes were made to this function.
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
  //  cout << "Hash Value: " << hashplates.Hash(plate) << endl;
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}


int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();

	
	bubbleSort(plates, amounts);
	//printKeys(plates);
	outputFile(plates,amounts,basename);
	cout << endl << endl;

	
	
	
  //
  // done:
  //
  return 0;
}