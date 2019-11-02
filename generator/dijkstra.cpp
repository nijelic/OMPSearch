#include "dijkstra.hpp"
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

void initializeDistances(std::map<int, long long> &dijkstraDistances)
{
	for (auto it = graph.begin(); it != graph.end(); ++it)
	{
		dijkstraDistances[it->first] = INF;
	}
}

void dijkstra(std::map<int, long long> &dijkstraDistances, int startNode)
{
	initializeDistances(dijkstraDistances);
	auto comparator = [](std::pair<int, long long>&p1, std::pair<int, long long>&p2)
	{
		return p1.second > p2.second;
	};
	std::priority_queue<std::pair< int, long long >, std::vector< std::pair< int, long long > >,
		decltype(comparator)> pq(comparator);
	pq.push(std::make_pair(startNode, 0));

	while (!pq.empty()) {
		int currentNode = pq.top().first;
		long long distance = pq.top().second;
		pq.pop();

		if (distance < dijkstraDistances[currentNode])
		{
			dijkstraDistances[currentNode] = distance;
		}
		else
		{
			continue;
		}
		for (std::vector<std::pair<int, unsigned> >::iterator it = graph[currentNode].begin();
			it != graph[currentNode].end(); ++it)
		{
			if (it->second + distance < dijkstraDistances[it->first])
			{
				pq.push(std::make_pair(it->first, it->second + distance));
			}
		}
	}
}
