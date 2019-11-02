#ifndef BEES_ALGORITHM_HPP
#define BEES_ALGORITHM_HPP

#include <map>
#include <utility>
#include <vector>

extern std::map< int, std::vector< std::pair<int, unsigned> > >	graph;
extern std::vector<int>	subsetOfVertices;

struct BeeProperty {
	int			node;           // current food
	int			trail;          // number of times we tried to search better neighbor
	long long	trueFit;			// dijkstra result
	double		fitness;			// kinda reciprocal to trueFit
	double		probability;	// probability that this is the best solution
};

void	beesAlgorithm();
double	calculateFitness(long long);
double	calculateTrueFit(BeeProperty);
void	calculateProbabilities();
void	initialize();
void	memorizeBestSource();
void	searchForBetterNeighbor(BeeProperty &, BeeProperty &);
void	sendEmployedBees();
void	sendOnlookerBees();
void	sendScoutBees();
#endif
