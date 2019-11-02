#include "dijkstra.hpp"
#include "halfway_of_farthest_algorithm.hpp"
#include <chrono>
#include <iostream>
#include <random>


void updateFarthestDistances(std::vector<long long> &farthestDistances,
	std::map<int, long long> &dijkstraDistances)
{
	for (int i = 0; i < farthestDistances.size(); ++i)
	{
		if (dijkstraDistances.at(i) > farthestDistances[i])
		{
			farthestDistances[i] = dijkstraDistances.at(i);
		}
	}
}


int findFarthestNotVisited(std::vector<long long> &farthestDistances,
	std::set<int> &visitedNodes)
{
	long long maxDistance = -1;
	int farthestIndex = -1;
	for (int i = 0; i < subsetOfVertices.size(); ++i) {
		if (farthestDistances[subsetOfVertices[i]] >= maxDistance
			&& visitedNodes.find(i) == visitedNodes.end())
		{
			maxDistance = farthestDistances[subsetOfVertices[i]];
			farthestIndex = i;
		}
	}
	return farthestIndex;
}


int hillClimbingAlgorithm(std::vector<long long> &farthestDistances)
{
	std::random_device					randDev;
	std::mt19937						generator(randDev());
	std::uniform_int_distribution<int>	distribution(0, subsetOfVertices.size() - 1);
	std::vector<int>					notPicked(subsetOfVertices);
	int									generated = distribution(generator);
	int									indexOfMinimum = notPicked[distribution(generator)];
	int									iterations;
	std::cout << "Enter number of iterations used for hill climbing: ";
	std::cin >> iterations;
	if (iterations > subsetOfVertices.size() - 1)
	{
		iterations = subsetOfVertices.size() - 1;
	}
	for (int i = 0; i < iterations; ++i)
	{
		int	generated = distribution(generator) % notPicked.size();
		int localMinimumIndex = notPicked[generated];
		notPicked.erase(notPicked.begin() + generated);

		while (true)
		{
			bool found = false;
			for (std::vector<std::pair<int, unsigned> >::iterator it
				= graph[localMinimumIndex].begin();
				it != graph[localMinimumIndex].end(); ++it)
			{
				if (farthestDistances[localMinimumIndex] > farthestDistances[it->first])
				{
					localMinimumIndex = it->first;
					found = true;
					break;
				}
			}
			if (!found)
			{
				break;
			}
		}
		if (farthestDistances[indexOfMinimum] > farthestDistances[localMinimumIndex])
		{
			indexOfMinimum = localMinimumIndex;
		}
	}
	return indexOfMinimum;
}


void halfwayOfFarthestAlgorithm()
{
	std::random_device					rd;
	std::mt19937						generator(rd());
	std::uniform_int_distribution<int>	distribution(0, subsetOfVertices.size() - 1);
	std::map<int, long long>			dijkstraDistances;
	std::vector<long long>				farthestDistances(graph.size());
	std::set<int>									visitedNodes;
	int														generated = distribution(generator);
	int														iterations;

	std::cout << "Enter number of iterations: ";
	std::cin >> iterations;
	if (iterations > subsetOfVertices.size() / 3)
	{
		iterations = subsetOfVertices.size() / 3;
	}
	auto timeStart = std::chrono::system_clock::now();

	for (int i = 0; i < iterations; ++i)
	{
		while (visitedNodes.find(generated) != visitedNodes.end())
		{
			generated = distribution(generator);
		}
		visitedNodes.insert(generated);

		dijkstra(dijkstraDistances, subsetOfVertices[generated], [](long long x) {return false;});
		updateFarthestDistances(farthestDistances, dijkstraDistances);

		int farthest = findFarthestNotVisited(farthestDistances, visitedNodes);
		visitedNodes.insert(farthest);
		dijkstra(dijkstraDistances, subsetOfVertices[farthest], [](long long x) {return false;});
		updateFarthestDistances(farthestDistances, dijkstraDistances);

		farthest = findFarthestNotVisited(farthestDistances, visitedNodes);
		visitedNodes.insert(farthest);
		dijkstra(dijkstraDistances, subsetOfVertices[farthest], [](long long x) {return false;});
		updateFarthestDistances(farthestDistances, dijkstraDistances);
	}
	auto timeEnd = std::chrono::system_clock::now();
	int node = hillClimbingAlgorithm(farthestDistances);

	std::cout << "\nOptimal meeting point is " << node << "." << std::endl;
	dijkstra(dijkstraDistances, node, [](long long x) {return false;});
	std::pair<int, long long> farthest = findFarthest(dijkstraDistances);

	std::cout << "The farthest node is at location: " << farthest.first
						<< ". Distance is: " << farthest.second << ".\n" << std::endl;
	std::cout << " Time = "
	          << std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd-timeStart).count()
	          << " nano sec.\n" << std::endl;
}
