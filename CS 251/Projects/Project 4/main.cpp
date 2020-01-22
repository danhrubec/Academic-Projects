/*main.cpp*/

//
// myDB project using AVL trees
//
// <<Dan Hrubec>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

#include "avl.h"
#include "util.h"

using namespace std;


//
// tokenize
//
// Given a string, breaks the string into individual tokens (words) based
// on spaces between the tokens.  Returns the tokens back in a vector.
//
// Example: "select * from students" would be tokenized into a vector
// containing 4 strings:  "select", "*", "from", "students".
//
vector<string> tokenize(string line)
{
  vector<string> tokens;
  stringstream  stream(line);
  string token;

  while (getline(stream, token, ' '))
  {
    tokens.push_back(token);
  }

  return tokens;
}



//this is a function to help assist during the portion of the project where
//we are reading in the meta data. some of the code was based off of the given\
//echo data function in util.cpp. it reads in the data line by line of a .meta file and creates
//a vector of strings to hold the data that is being stored in each column. for example: uin, firstname,
//lastname, etc...
vector<string> getDataPieces(string tablenm)
{
	vector<string> mdata;
	
	string   filename = tablenm + ".meta";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return mdata;
  }
	
	//going to read in the first two lines first as they are arbitrary to this function
	//this function specifically returns the metadata of whether a set of info will be indexed
	//or not. the other two pieces of data will be handled in their own functions
	
	string value;
	
	data >> value; //reading in the offset
	data >> value; //reading in the number of columns
	
	//first read in the piece of data
	data >> value;
	mdata.push_back(value);
	while(!data.eof())
	{
		//this is a number 0/1 to see if it is indexed or not
		data >> value;
		
		//now this is the data being stored
		data >> value;
		mdata.push_back(value);
	}
	
	return mdata;
}

//another driving force in the reading of the metadata file. it assumes that the order 
//of the meta file follows the format given in the writeup and the given students.meta. it reads in
//the other information, but this function only returns one thing, so it doesnt do anything with that data
//it just create a vector of ints 0 or 1 to signify if a given column will have an index tree or not.
vector<int> getMetaData(string tablenm)
{
	vector<int> mdata;
	
	string   filename = tablenm + ".meta";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return mdata;
  }
	
	//going to read in the first two lines first as they are arbitrary to this function
	//this function specifically returns the metadata of whether a set of info will be indexed
	//or not. the other two pieces of data will be handled in their own functions
	
	string value;
	
	data >> value; //reading in the offset
	data >> value; //reading in the number of columns
	
	//first read in the piece of data
	data >> value;
	while(!data.eof())
	{
	
		
		//next read if it will be indexed or not
		data >> value;
		
		if(value == "1")
		{
			mdata.push_back(1);
		}
		else if (value == "0")
		{
			mdata.push_back(0);
		}
		
		//should reach the nextline/eof with this statement
		data >> value;
	}
	
	return mdata;
}


//also still reading in information from the metadata file. To kind of reiterate here, one function-one purpose
//it will take the tablename as the parameter. open the corresponding .meta file for the given tablename and return how offset
//or the first number in the meta file. for example 82 in students.meta or 80 in stations.meta. not returning it as an int]
//but as an offset as we will be building the trees using offset pairs
streamoff getOffset(string tablenm)
{
	string   filename = tablenm + ".meta";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return 0;
  }
	
	//reading in the first value. First value of the metadata file is always the offset
	streamoff value;
	data >> value;
	
	return value;
}


//same idea, this is the last bit of data that i would need to get from the metadata files
//its the second line in the meta file assuming it follows the proper format given in the writeup
//reads in the number of columns for the tablename. only takes the string tablename as the parameter
//which is the first line that you read in when the program starts up
int getColumns(string tablenm)
{
	string   filename = tablenm + ".meta";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return 0;
  }
	
	//reading in the first value. First value of the metadata file is always the offset
	string value;
	data >> value;
	
	//reading in the second value which should now give the number of columns
	data >> value;
	int converted = std::stoi(value);
	
	return converted;
	
	
	
}

//building and populating the index trees. it is meant to take in an unknown number of index trees and
//this is the function that build them. it goes in and opens up that data file and reads in line by line
//or in this case record by record. instead of storing all of the data in the tree, we store the offset or an
//int so to speak of where in the file the data is being located. technically this is inserting in ascending order in 
//terms of the streamoffs, but that really doesnt matter too much as it is an avl tree so it will rebalance as 
//new items get insert.
avltree<string,streamoff> buildTree(streamoff offset, string tablenm, int position)
{
	avltree<string,streamoff> btavl;
	
	string   filename = tablenm + ".data";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return btavl;
  }

	
	
	//copied this section from echodata, it is essentially performing the same action.
	//go through the data file line by line(record) and put the data into the tree.
  data.seekg(0, data.end);  // move to the end to get length of file:
  streamoff length = data.tellg();

  streamoff pos = 0;  // first record at offset 0:
  string    value;

  while (pos < length)
  {
    data.seekg(pos, data.beg);  // move to start of record:

    getline(data,value);
		vector<string> dataline = tokenize(value);
		btavl.insert(dataline.at(position),pos);
		
    pos += offset;  // move offset to start of next record:
  }
	//btavl.inorder();
	return btavl;
}

//a helper function. it takes in a string and searches through the vector of strings to 
//see if the string exists in the vector. mainly used in the validate input function to see
//if a given search column for example is valid and exists in the tree and data. it returns 1
//if it is able to find it, or returns 0 if it did not find the string within the vector
int checkExist(string input, vector<string> query)
{
	for(unsigned int i = 0; i < query.size();i++)
	{
		if(input == query.at(i) || input == "*")
			return 1;
		
	}
	return 0;
	
	
}

//a function that is used during the query input section of the program. after a line of input is put in 
//for example select * from students where uin = 556178. it then uses the tokenize function to turn 
//the line of input into a vector of strings. this function makes sure that the input is valid. if it is
//not valid, it returns 0 and outputs what area of the input that didnt pass the tests. if it passes all the 
//tests, or if statements, it returns 1 and it means that the given input is valid and we can search the tree for it
int validateInput(vector<string> input, vector<string> qry, string tablenm)
{
	//seeing if the key words match up like select, from, where and '='
	if(input.at(0) != "select")
	{
		cout << "Unknown query, ignored..." << endl;
		return 0;
	}
	if(input.size() != 8)
	{
		cout << "Invalid select query, ignored..." << endl;
		return 0;
	}
	
	int column1Exists = checkExist(input.at(1), qry);
	
	if(column1Exists == 0)
	{
		cout << "Invalid select column, ignored..." << endl;
		return 0;
	}
	
	if(input.at(3) != tablenm)
	{
		cout << "Invalid table name, ignored..." << endl;
		return 0;
	}

int column2Exists = checkExist(input.at(5), qry);
	
	if(column2Exists == 0)
	{
		cout << "Invalid where column, ignored..." << endl;
		return 0;
	}
	
	return 1;
}

int getCol(string query, vector<string> data)
{
	for(unsigned int i = 0;i < data.size();i++)
	{
		if(data.at(i) == query)
			return i;
		
	}
	return 0;
	
}
//takes in the input, as well as the vector of strings of the data parts like the uin, netid, etc..
//as well as the vector of ints to determine if the column has an index tree or not. used right after 
//the input is validated. this determines if the input has an index tree for it or not. if it does, it 
//returns the column number where it is found. if it doesnt, then it returns -1 and we do not have an 
//index tree for the given input
int checkIndexTree(vector<string> query, vector<string> data, vector<int> metadata)
{
	int counter = -1;

	for(unsigned int i = 0; i < metadata.size();i++)
	{
		if(metadata.at(i) == 1)
		{
			counter++;
		}
		
		if(query.at(5) == data.at(i) && metadata.at(i) == 1)
		{
			return counter;
		}
		
	}
	return -1;
	
}


int main()
{
  string tablename; // = "students";

  cout << "Welcome to myDB, please enter tablename> ";
  getline(cin, tablename);
	//beginning portion of the program. now that the metadata has been read in, it will now 
	//extract all the data and put them in the appropriate variables. function calls to each of the
	//respective functions for this purpose
  cout << "Reading meta-data..." << endl;
	streamoff offset = getOffset(tablename);
	int numCol = getColumns(tablename);
	vector<string> dataPieces = getDataPieces(tablename);
  vector<int> mdata = getMetaData(tablename);
	


  cout << "Building index tree(s)..." << endl;
  //now since there is an unknown number of index trees, we will have to create a vector
  //of index trees in order to store them as there can be only 1, or 500 hypothetically.
  
	//to start this process off, we will loop through the metadata vector until we reach a 1, aka a value
	//that we know we will make a tree for. if we read a zero, nothing happens. we dont care
	
	vector<avltree<string,streamoff>> indexTrees;
	//loop through the metadata vector. if we find a 1, build an indextree for it.
	//since there definitely will be more than 1 indextree and an unknown amount actually, we have
	//a vector of indextrees as the size is unpredictable.
	for(unsigned int i = 0; i < mdata.size();i++)
	{
			if(mdata.at(i) == 1)
			{
				avltree<string,streamoff> avl;
				avl = buildTree(offset, tablename,i);
				indexTrees.push_back(avl);
			}
	
		
	}
	
	//now outputting data after all the trees have been built. formatted correctly.

	for(unsigned int i = 0; i < mdata.size();i++)
	{
		int counter = 0;
		if(mdata.at(i) == 1)
		{
			cout << "Index column: " << dataPieces.at(i) << endl;
			cout << "  Tree size: " << indexTrees.at(counter).size() << endl;
			cout << "  Tree height: " << indexTrees.at(counter).height() << endl;
			counter++;
		}
		
	}

	
	
  //
  // Main loop to input and execute queries from the user:
  //
  string query;
  
  cout << endl;
  cout << "Enter query> ";
  getline(cin, query);

  while (query != "exit")
  {
		//first, now that we read in a line from the user, "tokenize" it as in every word seperated by a space
		//is its own element in the vector.
    vector<string> tokens = tokenize(query);
		
    //validates the input by calling this function. returns 1 if valid else returns not 1 (0)
    
		int num = validateInput(tokens, dataPieces, tablename);
		//now we know if the input is valid or not. time to out put the results accordinly. if it is not a valid input,
		//we do not want to go through and output the data. so if its not valid it will skip all of this.
		if(num == 1)
		{
			//first check if we have an index tree for the data
		
			int indexFound = checkIndexTree(tokens,dataPieces,mdata);
			
			//if the input has an index tree, will use this decision structure to output the data
			if(indexFound != -1)
			{
					//we found an index for the input
					//first time to see what we are outputting. if we have a *, we need to output everything.
					if(tokens.at(1) == "*")
					{
						//searches the tree for the what we said to search for. aka the part after the =
						//but search returns a pointer to the data type. so we need to use streamoff*
						streamoff* adjustedOffset = indexTrees.at(indexFound).search(tokens.at(7));
						vector<string> recordData;// getting a vector of strings ready for GetRecord
						if(adjustedOffset == nullptr)
						{
					
						}
						else
						{
							streamoff temp = *adjustedOffset;//convert the pointer to just a reg variable.
							recordData = GetRecord(tablename,temp,numCol);//uses the getrecord function to get the output from the data file
						}
					// if record data doesnt hold anything, then nothing was found.
					if(recordData.size() == 0)
					{
							cout << "Not found..." << endl;
			
					}
					else
					{
						// out put the contents from record data.
							for(unsigned int i = 0; i < recordData.size();i++)
							{
								cout << dataPieces.at(i) << ": " << recordData.at(i) << endl;
							}
					}
					}
					else
					{
						//cout << "hello world" << endl;
						string qry = tokens.at(1);
						int colIndex = getCol(qry,dataPieces);
				
						streamoff* adjustedOffset = indexTrees.at(indexFound).search(tokens.at(7));
						vector<string> recordData;
						if(adjustedOffset == nullptr)
						{
					
						}
						else
						{
							streamoff temp = *adjustedOffset;
							recordData = GetRecord(tablename,temp,numCol);
						}
			
				
						if(recordData.size() == 0)
						{
							cout << "Not found..." << endl;
					
						}
						else
						{
							cout << dataPieces.at(colIndex) << ": " << recordData.at(colIndex) << endl;
						}
				
					}
		}
		else //it will enter here if the given query does not have an index tree
		{
			//so now we are in the case where we do not have an index tree for the input
			//the solution to this is to use the linear search function in the util.cpp file.
			//this returns a vector of streamoff numbers of where the data given is located in the file.
			//the twist to the is that it can definitely have more than one location where a certain string is located in.
		
			int rSize = (int)offset;
			
			string qry = tokens.at(5);
			//gives vector position. we still need to add 1 for linear search to work
			int colIndex = getCol(qry,dataPieces) + 1;
			/*
			cout << "tablename: " << tablename << endl;
			cout << "recordsize: " << rSize << endl;
			cout << "number of col: " << numCol << endl;
			cout << "match string: " << tokens.at(7) << endl;
			cout << "match column: " << colIndex << endl;
			*/			
			vector<streamoff> linearIndex = LinearSearch(tablename,rSize,numCol,tokens.at(7),colIndex);
			//cout << "size:" << linearIndex.size() << endl;
			
			//if the linear index does not hold anything, means the linear search couldnt find
			//anything in the data file, meaning that data was not found. outputs accordingly.
			if(linearIndex.size() == 0)
			{
				cout << "Not found..." << endl;
			}
			else
			{
				//pretty much the same logic as before. if we encounter a * we need to output everything, else just
				//the certain data piece. only difference is this is all in a loop to account for the potential of having
				//multiple streamoff location of where the data is.
				if(tokens.at(1) == "*")
				{
					
					for(unsigned int i = 0; i < linearIndex.size();i++)
					{
						
						vector<string> recordData;
						recordData = GetRecord(tablename,linearIndex.at(i),numCol);
						if(recordData.size() == 0)
						{
								cout << "Not found..." << endl;
				
						}
						else
						{
							for(unsigned int i = 0; i < recordData.size();i++)
							{
								cout << dataPieces.at(i) << ": " << recordData.at(i) << endl;
							}
						}
					}
				
					
				}
				else
				{
					//same story here. prints out the according data to the input. loop for linearIndex.size as
					//the linear search can find multiple locations of where input was found in the file.
						for(unsigned int i = 0;i<linearIndex.size();i++)
						{
							string qry = tokens.at(1);
							int colIndex = getCol(qry,dataPieces);
							vector<string> recordData;
							recordData = GetRecord(tablename,linearIndex.at(i),numCol);	
							if(recordData.size() == 0)
							{
								cout << "Not found..." << endl;
					
							}
							else
							{
								cout << dataPieces.at(colIndex) << ": " << recordData.at(colIndex) << endl;
							}
						}
				}
				
				
			}
			
			
			
		}
			
			
			
			
			
			
			
			
		}
		
		//resets to get more input or "exit"
    cout << endl;
    cout << "Enter query> ";
		
    getline(cin, query);
  }

  //
  // done:
  //
  //finally. freedom.

	
  return 0;
}


