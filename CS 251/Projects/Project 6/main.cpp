//Dan Hrubec
//CS 251
//Project 6 - Graph algorithms


#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>
#include <stack>
#include <limits>

#include "graph.h" 
#include "util.h"
#include "minqueue.h"


using namespace std;





int main()
{
	graph  g;
  string filename;

  cout << "Enter filename containing graph data> ";
  cin >> filename;
	
  buildGraph(filename, g);
  outputGraph(g);
	
	cout << endl;
	
	char startingV;
	cout << "Enter a starting vertex or #> ";
	cin >> startingV;
	
	
	
	
	
	string NPrefix = "Neighbors: ";
	string BFSPrefix = "BFS: ";
	string DFSPrefix = "DFS: ";
	string Dprefix = "Dijkstra: ";
	
	
	while(startingV != '#')
	{
		bool correctIndex = g.isvertex(startingV);
		if(correctIndex == true)
		{
			//printing out neighbors
			vector<char> neighbors = g.neighbors(startingV);
			outputAlgorithm(NPrefix,neighbors);
		
			//printing out the result of BFS
			vector<char> BFSVertices = BFS(g,startingV);
			outputAlgorithm(BFSPrefix, BFSVertices);
		
			//printing out the result of DFS
			vector<char> DFSVertices = DFS(g,startingV);
			outputAlgorithm(DFSPrefix, DFSVertices);
		
			//printing out the result of Dijsktra
		
			vector<int> distance(26);
			vector<char> path = Dijkstra(g,startingV,distance);
			outputDijkstra(Dprefix,distance,path);
			distance.clear();
			path.clear();
		}
		else
		{
			cout << "Not a vertex in graph, ignored..." << endl;
			cout << endl;
		}
		
		cout << "Enter a starting vertex or #> ";
		cin >> startingV;
	}
	
	return 0;
}