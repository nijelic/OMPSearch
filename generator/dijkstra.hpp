#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#define INF LLONG_MAX
#include <climits>
#include <map>
#include <utility>
#include <vector>

extern std::map< int, std::vector< std::pair<int, unsigned> > >	graph;

void	dijkstra(std::map<int, long long> &, int);
void	initializeDistances(std::map<int, long long> &);
#endif
