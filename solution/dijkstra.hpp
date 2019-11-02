#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#define INF LLONG_MAX
#include <climits>
#include <functional>
#include <map>
#include <utility>
#include <vector>

extern std::map< int, std::vector< std::pair<int, unsigned> > >	graph;
extern std::vector<int>	subsetOfVertices;

void	dijkstra(std::map<int, long long> &, int, std::function<bool(long long)>);
std::pair<int, long long> findFarthest(std::map<int, long long> &);
void	initializeDistances(std::map<int, long long> &);
#endif
