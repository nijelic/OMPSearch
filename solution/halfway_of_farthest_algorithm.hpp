#ifndef HALFWAY_OF_FARTHEST_ALGORITHM_HPP
#define HALFWAY_OF_FARTHEST_ALGORITHM_HPP

#include <map>
#include <set>
#include <utility>
#include <vector>

extern std::map< int, std::vector< std::pair<int, unsigned> > >	graph;
extern std::vector<int>	subsetOfVertices;

int		findFarthestNotVisited(std::vector<long long> &, std::set<int> &);
void	halfwayOfFarthestAlgorithm();
int		hillClimbingAlgorithm(std::vector<long long> &);
void	updateFarthestDistances(std::vector<long long> &, std::map<int, long long> &);
#endif