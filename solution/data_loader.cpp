#include "data_loader.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

std::map< int, std::vector< std::pair<int, unsigned> > > graph;
std::vector<int> subsetOfVertices;


void saveNode(int firstNode, int secondNode, unsigned edgeWeight)
{
	std::pair<int, unsigned> p;
	p.first = secondNode;
	p.second = edgeWeight;
	if (graph.find(firstNode) == graph.end()) {
		std::vector< std::pair<int, unsigned> > v;
		v.push_back(p);
		graph[firstNode] = v;
	}
	else {
		graph[firstNode].push_back(p);
	}
}


void loadGraph(std::string filename)
{
	std::ifstream myfile(filename);
	graph.clear();
	if (myfile.is_open())
	{
		int numberOfEdges;
		myfile >> numberOfEdges;
		for (int i = 0; i < numberOfEdges; ++i)
		{
			int firstNode;
			int secondNode;
			int edgeWeight;
			myfile >> firstNode >> secondNode >> edgeWeight;
			saveNode(firstNode, secondNode, edgeWeight);
			saveNode(secondNode, firstNode, edgeWeight);
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file " << filename;
	}
}


void loadSubsetOfVertices(std::string filename)
{
	std::ifstream myfile(filename);
	subsetOfVertices.clear();
	if (myfile.is_open())
	{
		int numberOfNodes;
		myfile >> numberOfNodes;
		for (int i = 0; i < numberOfNodes; ++i)
		{
			int node;
			myfile >> node;
			subsetOfVertices.push_back(node);
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file " << filename;
	}
}
