//Dan Hrubec
//CS 251
//Project 6 - Graph Algorithms
//
//
//util.h

#pragma once


#include <iostream>
#include <string>

#include "graph.h"
#include "minqueue.h"

using namespace std;

void buildGraph(string filename, graph& g);
void outputGraph(graph& g);
vector<char> BFS(graph& g, char startV);
vector<char> DFS(graph& g, char startV);
vector<char> Dijkstra(graph& g, char startV, vector<int>& distance);
void outputAlgorithm(string prefix, vector<char> verticies);
void outputDijkstra(string prefix, vector<int> dist, vector<char> bestPath);