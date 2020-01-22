//
// <<Daniel Hrubec>>
// Danny Boi on the leaderboards btw
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>

#include "bst.h"

// the value portion to the key value pair, will hold all the movie information
// also stores the name and the movie id while inputting data. this makes the end portion easier
// when it comes to the user input. no matter if they put in the id or the name when outputting the review
// data is will display both of them

struct MovieData 
  {
		string name = "";
		int movID = 0;
	  int pubYear = 0;
	  int fiveStar = 0;
	  int fourStar = 0;
	  int threeStar = 0;
	  int twoStar = 0;
	  int oneStar = 0;
  
  };


using namespace std;


//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
//function given at start of project. no extra modifications have been made
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
// after inputting all the data from a given line, it will create a MovieData struct
// inside and insert them into 2 trees, one sorted by movieid the other by name
// also passed the bst by reference from main so that a copy is not made and changes are kept after the function call
void InputMovies(string moviesFilename, binarysearchtree<int, MovieData>& idmovies, binarysearchtree<string, MovieData>& byName)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;
	int counter = 0;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name);  

    // debugging:
    //cout << id << "," << pubYear << "," << name << endl;
		//commenting out now that i know this is functional
		//
		//creating a struct and inputting the data into it
		MovieData value;
		value.pubYear = pubYear;
		value.name = name;
		value.movID = id;
		//inserting the newly made struct with data into both of the bst
		idmovies.insert(id, value);
		byName.insert(name, value);
		
		//created a counter variable that increments once per line so after the function is called.
		//it will display the total amount of movies that were read in
		counter++;
		
    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
	cout << "Num movies: " << counter << endl;
}

//Input Reviews function
//
//very similar to how the input movies function worked. it will take in three parameters. first a string which is the name of the file
//holding all the data. it will be opened and read using ifstream. next are two bst sorted by name and by id. after reading in the information
//about one review, it will search the bst to find the given movie, and then update the ratings keeping a total of each one. it takes in one 
//movie id but writes to both of the bst.
void InputReviews(string reviewFile, binarysearchtree<int, MovieData>& idmovies, binarysearchtree<string, MovieData>& byName )
{
	ifstream theReviews(reviewFile);
	int id; // movie id, will use this to search the trees
	int rating; // either a 5,4,3,2,1 will increment the appropriate rating in the struct
	int reviewID; // not really that important
	int counter = 0; // additonal counter variable to keep track of the total number of reviews
	
	//checks to see if the file is in the current directory. the function will exit here if it was not able
	//to find the file.
	if(!theReviews.good())
	{
		cout << "Error. Unable to open review file. Exiting." << endl;
		return;
		
	}
	
	theReviews >> reviewID; // uses the same logic as the movie reviews, gets the first ID
	
	while(!theReviews.eof())
	{
		//collecting the movie id and the rating
		theReviews >> id;
		theReviews >> rating;
		
		//test output
		//cout << reviewID << "," << id << "," << rating << endl;
		//
		//commenting this out as i know now that the function operates as it should
		
		//creates a new struct and uses the search function to find the given struct in the tree
		MovieData* ids;
		ids = idmovies.search(id);
		if(ids != nullptr) //checks to see if the search is valid. if it wasnt search returns nullptr
		{
			//now that i know search was valid, i take the name and search the other tree creating another struct
			string nm = ids->name;
			MovieData* ins = byName.search(nm);
			
			//will check the value of rating, kinda longish if else if structure to find out which
			//rating variable to update. and will update to both, it is updating both bst sorted by id
			//and name at the same time
			if(rating == 5)
			{
				ids->fiveStar++;
				ins->fiveStar++;
			}
			else if(rating == 4)
			{
				ids->fourStar++;
				ins->fourStar++;
			
			}
			else if(rating == 3)
			{
			
				ids->threeStar++;
				ins->threeStar++;
			}
			else if(rating == 2)
			{
			
				ids->twoStar++;
				ins->twoStar++;
			}
			else if(rating == 1)
			{
				ids->oneStar++;
				ins->oneStar++;
			}
			else
			{
					//if for whatever reason that the review happened to be like 6 or something
					// made the else case to note that an invalid review was read
					cout << "Error. Invalid review." << endl;
			}
			
			//same idea as before, keeps track of the total number of reviews that were read in from the file
			counter++;
		}
		
		
		
		//gets the next id or sets the End of file flag
		theReviews >> reviewID;
	}
	
	cout << "Num reviews: " << counter << endl;
}

//helper function. it takes in a movie struct and calculates the average. then cout the average
//as a double. nothing too special going on here, just some basic math.
void getAverage(MovieData* data)
{
	double average = 0.0;
	if(data->fiveStar == 0 && data->fourStar == 0 && data->threeStar == 0 && data->twoStar == 0 && data->oneStar == 0)
	{
		cout << "Avg rating: " << 0 << endl;
	}
	else
	{
		int total = data->fiveStar + data->fourStar + data->threeStar + data->twoStar + data->oneStar;
		average = (data->fiveStar)*5 + (data->fourStar)*4 + (data->threeStar)*3 + (data->twoStar)*2 + data->oneStar;
		average = average / total;
		cout << "Avg rating: " << average << endl;
		
		
	}

	
}

//another helper function. takes in a moviedata struct and prints out all of variable values as well as calls the 
//getaverage function to compute the average. Used to print out the data after a search was made and confirmed to be valid.
//basically a print function for the moviedata struct
void printReviews(MovieData* datas)
{
	cout << "Movie ID: "   << datas->movID << endl;
	cout << "Movie Name: " << datas->name << endl;
	getAverage(datas);
	cout << "5 stars: "   << datas->fiveStar  << endl;
	cout << "4 stars: "   << datas->fourStar  << endl;
	cout << "3 stars: "   << datas->threeStar << endl;
	cout << "2 stars: "   << datas->twoStar   << endl;
	cout << "1 star: "   << datas->oneStar   << endl;
	
	
}



//
// main
//
int main()
{
	
  string moviesFilename; // = "movies1.txt";
  string reviewsFilename; // = "reviews1.txt";

  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;

  string junk;
  getline(cin, junk);  // discard EOL following last input:
	
	//creating two trees, one sorted by a movie id and the other sorted by name
	//the purpose being that the user would be able to input either or to find a movie
	//and output its reviews
	binarysearchtree<int, MovieData> movieByID;
	binarysearchtree<string, MovieData> movieByName;

	
	//now it will read in all the information from the files and store them into the two bst
  InputMovies(moviesFilename, movieByID, movieByName);
	InputReviews(reviewsFilename, movieByID, movieByName);
	
	//after all the data has been read in, quick print of some of the bst data.
	cout << endl;
	cout << "Tree by movie id: size=" << movieByID.size()   << ", height=" << movieByID.height()   << endl;
	cout << "Tree by movie name: size=" << movieByName.size() << ", height=" << movieByName.height() << endl <<endl;
	


	//now it is time for the user input
	string input;
	cout << "Enter a movie id or name (or # to quit)> ";
	getline(cin,input);
	
	//i made a flag variable here. i am initially setting it to be true, and assuming that the input that was 
	//read in was an int aka a movieid and not a name.
	
	bool isInt = true;
	
	while(input !="#") // loops for the user until the sentinel is read in
	{
		//now this will loop through the entire string of input character by character and will test to see 
		//if a character is not a numerical number. if there is a letter inside, then you know it has to be a name
		//because the name can have numbers in the title, but the movieid cannot have an letter inside
		for(unsigned int i = 0; i < input.length() - 1;i++)
		{
			if(isalpha(input[i]))
			{
				isInt = false; // sets the flag to be false if a letter is found
			}
		}
		
		//goes into this if the input was all numbers meaning it must have been a movieid
		if (isInt == true)
		{
			MovieData* values = movieByID.search(stoi(input));
			if(values == nullptr) // checks to see if the node was found in the tree
			{
				cout << "not found..." << endl;
			}
			else
			{
				printReviews(values); //prints all the data about the moviedata struct
			}
			
		}
		else if(isInt== false) // a letter was found in the input so it must have been a name
		{
			MovieData* values = movieByName.search(input);
			if(values == nullptr)// checks to see if the node was found inside the tree
			{
				cout << "not found..." << endl;
			}
			else
			{
				printReviews(values); //prints all the data about the moviedata struct
			}
		}
		//continues to loop and resets the flag
		isInt = true;
		cout << "\nEnter a movie id or name (or # to quit)> ";
		getline(cin,input);
		
	};
	
	//after the sentinel is reached, the program has reached the end.
	//done.

	cout << endl;
  return 0;
}
