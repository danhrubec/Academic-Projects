//Dan Hrubec
//CS 251
//Project 6 - Graph Algorithms

//util.cpp



#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>
#include <stack>

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;



//
// outputGraph:
//
// Outputs graph g to the console.
//
// outputGraph function taken from zyBooks Lab 12
void outputGraph(graph& g)
{
	//printing out vertices
  vector<char> vertices = g.vertices();

  cout << "**Vertices: ";

  for (char c : vertices)
  {
    cout << c << " ";
  }

  cout << endl;
	//printing out edges
  cout << "**Edges: ";

  for (char v : vertices)
  {
    vector<char> neighbors = g.neighbors(v);

    for (char n : neighbors)
    {
      int weight = g.getweight(v, n);
      cout << "(" << v << "," << n << "," << weight << ") ";
    }
  }
	
  cout << endl;
}




//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
// buildGraph function taken from zyBooks Lab week 12.
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }
   
  //
  // Input vertices as single uppercase letters:  A B C ... #
  //
   string data;
   
   file >> data;
   
   while(data != "#")
   {
        char letter = data[0];
        g.addvertex(letter);
        file >> data;
      
   }
   
   
  //now we are done with the verticies. onto the edges.
  
  char toLet;
  char fromLet;
  int weight;
  
  file >> data;
  
  
  while (data!="#")
  {
     toLet = data[0];
      file >> data; 
      fromLet = data[0];
      file >> data;
      weight = stoi(data);
      file >> data;
      g.addedge(toLet, fromLet, weight);
  }


  
}


//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
// DFS function taken from zyBooks HW 14
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;

  frontierStack.push(startV);

  while(frontierStack.empty() == false)
  {
     char currentV = frontierStack.top();
     frontierStack.pop();
     
     if (visitedSet.find(currentV) == visitedSet.end())
     {
        vector<char> nbors = g.neighbors(currentV);
        visitedSet.insert(currentV);
        visited.push_back(currentV);
        for(unsigned int i = 0; i < nbors.size();i++)
        {
         frontierStack.push(nbors[i]);  
           
        }
        
     }
     
     
  }

  return visited;
}


//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
// BFS function taken from zyBooks Lab week 12
vector<char> BFS(graph& g, char startV)
{
  vector<char>  visited;
  queue<char>   frontierQueue;
  set<char>     discoveredSet;

  frontierQueue.push(startV);
  discoveredSet.insert(startV);
  
  while(frontierQueue.empty() == false)
  {
     char currentV = frontierQueue.front();
     frontierQueue.pop();
     
     vector<char> nbors = g.neighbors(currentV);
     visited.push_back(currentV);
     for(unsigned int i = 0; i < nbors.size();i++)
     {
        
         if (discoveredSet.find(nbors[i]) == discoveredSet.end())  // then v is not an element of the set
         {
            
            frontierQueue.push(nbors[i]);
            discoveredSet.insert(nbors[i]);
         }
        
     }
     
  }

  
  return visited;
}

//Dijkstra's Algorithm. Returns the shortest path to a vertice

vector<char> Dijkstra(graph& g, char startV, vector<int>& distance)
{
	vector<char> vertexz = g.vertices();
	vector<char> PathOverObstacles; //if you know, you know
	
	minqueue<char,int> unvisitedQueue;
	
	const int Inf = numeric_limits<int>::max();
	char currentV;
	//int distance[26];
	//int predecessor[26];
	
	
	
	for(char vtex : vertexz)
	{
		distance[(vtex - 'A')] = Inf;
		//predecessor[(vtex - 'A')] = -1;
		unvisitedQueue.pushinorder(vtex,Inf);
	}
	
	distance[(startV - 'A')] = 0;
	//PathOverObstacles.push_back(startV);
	unvisitedQueue.pushinorder(startV,0);
	
	while(unvisitedQueue.empty() == false)
	{
		currentV = unvisitedQueue.minfront();
		if(distance[currentV - 'A'] == Inf)
			break;
		PathOverObstacles.push_back(currentV);
		unvisitedQueue.minpop();
		
		vector<char> neighbors = g.neighbors(currentV);
		
		for(char vtex : neighbors)
		{
			int edgeWeight = g.getweight(currentV,vtex);
			int altPath = distance[(currentV - 'A')] + edgeWeight;
			
			
			if(altPath < distance[(vtex - 'A')])
			{
				distance[(vtex-'A')] = altPath;
				//predecessor[(vtex-'A')] = (currentV - 'A');
				//PathOverObstacles[ PathOverObstacles.size() - 1 ]= (predecessor[(vtex - 'A')] + 'A');
				unvisitedQueue.pushinorder(vtex, altPath);
				
			}
			
		}
		
		
	}
	
	return PathOverObstacles;
	
	
	
}

//helper function. Prints out the result of the given graph algorithm
void outputAlgorithm(string prefix, vector<char> verticies)
{
	cout << prefix;
	
	for( char index : verticies)
	{
		cout << index << " ";
	}
	
	cout << endl;
	
}


//helper function. Print outs the results for Dijkstra algorithm. Needed its own
//function because we needed to pass in the distance at each vertex as well.
void outputDijkstra(string prefix, vector<int> dist, vector<char> bestPath)
{
	cout << prefix;
	
	for( char index : bestPath)
	{
		cout << index << " ";
	}
	
	cout << endl;
	
	
	for(unsigned int i = 0; i < bestPath.size(); i++)
	{
		cout << "  " << bestPath[i] << ": " << dist[bestPath[i] - 'A'] << " via ";
		
		for(unsigned int j = 0; j <= i; j++)
		{
			cout << bestPath[j] << " ";
			
		}
		cout << endl;
		
		
		
	}
	
	cout << endl;
	
	
}

