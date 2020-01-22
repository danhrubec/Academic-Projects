/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// << Dan Hrubec >>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <math.h>

#include "ILplates.h"

using namespace std;


//AllCaps
//
//Takes in a string as the parameter. It will loop through the string to check if all of the
//characters within the string are capital letters. It does this by determining the ascii value of each
//character and checks if it is in the range of capital letters. Function will return -1 if it contains characters
//that are not capital letters and return 1 iff all characters are capital letters. will return -1 if theres a space
//used in validating the license plate
int allCaps(string str)
{
	int length = str.length();
	int i;
	
	for(i =0 ;i<length;i++)
	{
		int asciiCheck = str[i] - 65;
		if(asciiCheck < 0 || asciiCheck > 26)
		{
			return -1;
			
		}
		
		
	}
	
	return 1;
	
}

//spaceIndex
//
//Similar to the allcaps/all digit functions. it will loop through the string checking each
//character and will return the index in which the first space character is found. if no spaces are
//found it will return negative 1. if there are multiple spaces it will only return the first one found.
//used in validating the license plate
int spaceIndex(string str)
{
	int length = str.length();
	int i;
	char space = ' ';
	for(i = 0; i < length;i++)
	{
		if(str[i] == space)
		{
			return i;
			
		}
		
		
	}
	return -1;
	
	
}

//allDigit
//
//literally the same thing. idea, process, and execution as allCaps.
//loops through the string to determine if it is all digits. if it is,
//returns 1 otherwise it returns -1.
//also used in validating the string.
int allDigit(string str)
{
	int length = str.length();
	int i;
	
	for(i =0; i < length;i++)
	{
		int asciiCheck = str[i] - 48;
		if( asciiCheck < 0 || asciiCheck > 9)
		{
			return -1;
			
		}
		
	}
	return 1;
	
	
}

//validatePlate
//
//One of the driving forces behind the hashing function. This function is called before the license plate gets hashed. It makes sure the 
//plate is in the correct format which can be 1 of 4 cases. A vanity plate of 1-3 numbers. a vanity plate of 1-7 letters. A personalized plate
//of 1-5 letters a space and 1-2 digits. A personalized plate of 6 letters a space and 1 digit. It it is invalid, it returns -1. if it is valid
//it returns 1
int validatePlate(string plate)
{
		int length = plate.length();
		//int i;
		// if the length of the plate > 8 it isnt a plate so invalid
		if(length > 8)
		{
			return -1;
		}
	
		//going to go case by case to make sure the plate is valid.
		
		//starting with vanity plates
		int vanityDigits = allDigit(plate);
		int vanityCaps = allCaps(plate);
	
		//Case 3, if the plate is all digits aka vanity
		if(vanityDigits == 1)
		{
			//check if the length is between 1 and three
			if(length >= 1 && length <= 3)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		
		}
	
	//case 4, vanity plate with all capitals
	if(vanityCaps == 1)
	{
		//check to see if length is valid
		if(length >= 1 && length <=7)
		{
			return 1;
		}
		else
		{
			return -1;
		}
		
		
	}
	
	//case 1, 1-5 letters, space, 1-2 digits
	int spacePos = spaceIndex(plate);
	if(spacePos == 0 || spacePos == -1)
	{
		return -1;
	}
	string letterHalf = plate.substr(0,spacePos);
	string digitHalf = plate.substr(spacePos + 1);
	int capCheck = allCaps(letterHalf);
	int digCheck = allDigit(digitHalf);
	int letterLength = letterHalf.length();
	int digitLength = digitHalf.length();
	
	//no illegal letters, now checking the length
	if(capCheck == 1 && digCheck == 1)
	{
		if( (letterLength >= 1 && letterLength <=5) && (digitLength == 1 || digitLength == 2))
		{
			return 1;
			
		}
		else if(letterLength == 6 && digitLength == 1)
		{
			return 1;
			
		}
		else
		{
			return -1;
		}
		
		
		
		
	}
	
	
	return -1;
	
}



//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int ILplates::Hash(string plate)
{
  int index = -1;
	
  //
  // TODO:
  //
  int len = plate.length();
	int i;
	
	int test = validatePlate(plate);
	//cout << "returned value: "  << test << endl;
	if(test == -1)
	{
		return -1;
	}
	
	
	
	
	
	
	
	
/*
	string phrase = "856";

	unsigned long long prev = 0;

	for(i = 0;i<len;i++)
	{
		
		unsigned long long c = plate[i];
		
		if(isalpha(plate[i]))
		{
			c = (c - 'A');
			if(i%2 == 0)
			{
				c = (c + 36 + i) % 99;
			}
	
		}
		else if(isdigit(plate[i]))
		{
			
			c = (c - '0' + 26);	
			
			if(i%2 == 0)
			{
				c = (c + 36 + i) % 99;
			}
	
			
		}
		
		
	
		//cout << c << endl;
		string indexnum = to_string(c);
		phrase = phrase +indexnum;
		prev = c;
		//cout << phrase << endl;
	}
	
	
	
	
	unsigned long long temp = stoll(phrase);
	//temp = temp / HT.Size();
	
	
	
	
	//cout << "Plate : " << plate << "\t Temp: " << temp  << "\tIndex: " << (temp%HT.Size()) << endl;


	
	
	
	*/
	
	
	//index = 1234624;
	
	char prev;
	int counter = 0;
	unsigned long long temp = 2542847;
	for(i = 0; i <len;i++)
	{
		char c = plate[i];
		if(prev == c)
		{
			counter++;
		}
		
		
		
		if(isalpha(plate[i]))
		{
			
			int alphaHash = (c-64);
		
			alphaHash = alphaHash * (pow(8,i)) * (i+3);

			temp = temp + alphaHash;
		}
		else if(isdigit(plate[i]))
		{
			int digitHash = (plate[i]+37);
			digitHash = digitHash * (pow(8,i)) * (i+3);
			temp = temp + digitHash;
		}
		prev = c;
		
	}
	
	index = temp % HT.Size();
	//cout << "Plate: " << plate << "\tIndex: " << (index%HT.Size() ) << endl;
  return index;
}


//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{

  int index = Hash(plate);
	int size = HT.Size();
	bool freeSpace;
	int plateFee;
	string plateIndex;
	
	HT.Get(index, freeSpace, plateIndex, plateFee);

	while(plateIndex != plate )
	{
		if(freeSpace == true)
		{
			return -1;
		}
		
		if(index == size -1)
		{
			index = 0;
		}
		else
		{
			index++;
		}
		
		HT.Get(index,freeSpace,plateIndex,plateFee);
	}
  
	if(freeSpace == true)
	{
		return -1;
		
	}
	else
		return plateFee;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
	
  int index = Hash(plate);
	if(index == -1)
	{
		return;
	}
	
	
	bool freeSpace;
	int oldValue;
	int size = HT.Size();
	string plateIndex;
	//int probes = 0;
	
	HT.Get(index, freeSpace, plateIndex, oldValue);
	
	
	while(freeSpace == false)
	{
		
		if(plateIndex == plate || freeSpace == true)
		{
			HT.Set(index,plate,newValue);
			return;
		}
			
		index = (index + 1) % size;
		
	HT.Get(index, freeSpace, plateIndex, oldValue);
	
	}
	
	//cout << "In Insert-> index = " << index << endl;
	HT.Set(index,plate,newValue);
		
	

}
