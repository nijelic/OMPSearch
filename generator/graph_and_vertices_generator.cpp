#include "dijkstra.hpp"
#include "graph_and_vertices_generator.hpp"
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <vector>

std::map< int, std::vector< std::pair<int, unsigned> > > graph;
std::vector<int> subsetOfVertices;
int numberOfEdges = 0;

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

std::pair<int, int> createPair(int firstNode, int secondNode)
{
	if(firstNode < secondNode)
	{
		return std::make_pair(firstNode, secondNode);
	}
	else
	{
		return std::make_pair(secondNode, firstNode);
	}
}

void makeBaseGraph(int numberOfNodes, int valency) 
{
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>	distribution(0, numberOfNodes - 1);
	std::set<std::pair<int, int>> generated;

	for (int firstNode = 0; firstNode < numberOfNodes; ++firstNode)
	{
		for (int k = 0; k < valency; ++k)
		{
			int secondNode = distribution(generator);
			auto pair = createPair(firstNode, secondNode);
			while (generated.find(pair) != generated.end() or firstNode == secondNode)
			{
				secondNode = distribution(generator);
				pair = createPair(firstNode, secondNode);
			}
			generated.insert(pair);
			unsigned edgeWeight = abs(firstNode - secondNode);
			saveNode(firstNode, secondNode, edgeWeight);
			saveNode(secondNode, firstNode, edgeWeight);
			++numberOfEdges;
		}
	}
}


void makeItConnected(int startNode, int numberOfNodes) 
{
	std::map<int, long long> dijkstraDistances;
	dijkstra(dijkstraDistances, startNode);

	for (std::map<int, long long>::const_iterator it = dijkstraDistances.begin(); it != dijkstraDistances.end(); ++it)
	{
		if (it->second == INF)
		{
			std::random_device                  rand_dev;
			std::mt19937                        generator(rand_dev());
			std::uniform_int_distribution<int> 	distribution(0, numberOfNodes - 1);

			int secondNode = distribution(generator);
			while (dijkstraDistances[secondNode] == INF)
			{
				secondNode = distribution(generator);
			}
			unsigned edgeWeight = abs(it->first - secondNode);
			saveNode(it->first, secondNode, edgeWeight);
			saveNode(secondNode, it->first, edgeWeight);
			++numberOfEdges;
		}
	}
}

void markEdge(int firstNode, int secondNode)
{
	for(auto it = graph[firstNode].begin(); it != graph[firstNode].end(); it++)
	{
		if(it->first == secondNode)
		{
			it->second = UINT_MAX;
		}
	}
}

void saveGraph(std::string filename) 
{
	std::ofstream myfile(filename);
	if (myfile.is_open())
	{
		myfile << numberOfEdges << std::endl;
		for (auto nodeIt = graph.begin(); nodeIt != graph.end(); ++nodeIt)
		{
			for (auto edgeIt = nodeIt->second.begin(); edgeIt != nodeIt->second.end(); ++edgeIt)
			{
				if(edgeIt->second != UINT_MAX)
				{
					myfile << nodeIt->first << " " << edgeIt->first << " " << edgeIt->second << std::endl;

					for (auto it = graph[edgeIt->first].begin(); it != graph[edgeIt->first].end(); ++it)
					{
						if (it->first == nodeIt->first)
						{
							it->second = UINT_MAX;
							break;
						}
					}
					edgeIt->second = UINT_MAX;
				}
			}
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file " << filename;
	}
}


void saveVertices(std::string filename, int numberOfVertices, int numberOfNodes)
{
	std::ofstream myfile(filename);
	if (myfile.is_open())
	{
		myfile << numberOfVertices << std::endl;
		std::set<int> generated;
		for (int i = 0; i < numberOfVertices; ++i)
		{
			std::random_device                  rand_dev;
			std::mt19937                        generator(rand_dev());
			std::uniform_int_distribution<int>	distribution(0, numberOfNodes - 1);
			int gen = distribution(generator);
			while (generated.find(gen) != generated.end())
			{
				gen = distribution(generator);
			}
			generated.insert(gen);
		}
		for(auto gen:generated)
		{
			myfile << gen << std::endl;
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file " << filename << std::endl;
	}
}


int main(int argc, char *argv[]) 
{
	int numberOfNodes, valency;
	std::string answer;

	std::cout << "Enter number of nodes: ";
	std::cin >> numberOfNodes;
	std::cout << "Enter minimal valency: ";
	std::cin >> valency;
	std::cout << "Enter name of graph file: ";
	std::cin >> answer;

	makeBaseGraph(numberOfNodes, valency);
	makeItConnected(0, numberOfNodes);
	saveGraph(answer);

	std::cout << "Do you want to generate subset of vertices?y/n" << std::endl;
	std::cin >> answer;

	while (answer == "y")
	{
		int numberOfVertices;
		std::cout << "Enter number of vertices: ";
		std::cin >> numberOfVertices;
		std::cout << "Enter name of file: ";
		std::cin >> answer;

		saveVertices(answer, numberOfVertices, numberOfNodes);

		std::cout << "Do you want to generate another subset of vertices?y/n" << std::endl;
		std::cin >> answer;
	}
	return 0;
}
