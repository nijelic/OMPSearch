#include "bees_algorithm.hpp"
#include "dijkstra.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <set>

std::set<int> visitedVertices;
int foodNumber;
int maxTrail;
const int BOUNDARY = 0;

std::vector<BeeProperty> nectarSource; // best local solutions
std::vector<BeeProperty> employedBee;	 // employed bees -search for best local solution
std::vector<BeeProperty> onlookerBee;	 // onlooker bees -process the best local solution
BeeProperty bestFoodSource;


void initialize() {
	visitedVertices.clear();
	nectarSource.clear();
	nectarSource.resize(foodNumber);
	employedBee.clear();
	employedBee.resize(foodNumber);
	onlookerBee.clear();
	onlookerBee.resize(foodNumber);

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, graph.size() - 1);

	//initialized the best food
	bestFoodSource.node = -1;
	bestFoodSource.trueFit = INF;

	for (int i = 0; i < foodNumber; i++) {
		int generated = distribution(generator);
		while (visitedVertices.find(generated) != visitedVertices.end())
		{
			generated = distribution(generator);
		}

		nectarSource[i].node = generated;
		employedBee[i].node = generated;
		onlookerBee[i].node = generated;

		// initialized nectarSource
		nectarSource[i].trueFit = calculateTrueFit(nectarSource[i]);
		nectarSource[i].fitness = calculateFitness(nectarSource[i].trueFit);
		nectarSource[i].probability = 0;
		nectarSource[i].trail = 0;

		// initialized the employed
		employedBee[i].trueFit = nectarSource[i].trueFit;
		employedBee[i].fitness = nectarSource[i].fitness;
		employedBee[i].probability = nectarSource[i].probability;
		employedBee[i].trail = nectarSource[i].trail;

		// initialized the onlooker
		onlookerBee[i].trueFit = nectarSource[i].trueFit;
		onlookerBee[i].fitness = nectarSource[i].fitness;
		onlookerBee[i].probability = nectarSource[i].probability;
		onlookerBee[i].trail = nectarSource[i].trail;
	}
	bestFoodSource.node = nectarSource[0].node;
	bestFoodSource.trueFit = nectarSource[0].trueFit;
}


double calculateTrueFit(BeeProperty bee)
{
	long long			trueFit = 0;
	static long long	maxTrueFit = 0;
	if (visitedVertices.find(bee.node) == visitedVertices.end())
	{
		visitedVertices.insert(bee.node);
		bool							predicateTrue = false;
		std::map<int, long long>		dijkstraDistances;
		std::function<bool(long long)>	predicate = [&trueFit, &predicateTrue](long long distance)
		{
			if (distance > bestFoodSource.trueFit) {
				trueFit = distance;
				predicateTrue = true;
				return true;
			}
			return false;
		};
		dijkstra(dijkstraDistances, bee.node, predicate);
		if (!predicateTrue)
		{
			trueFit = findFarthest(dijkstraDistances).second;
		}
		if (trueFit > maxTrueFit)
		{
			maxTrueFit = trueFit;
		}
	}
	else
	{
		trueFit = maxTrueFit;
	}
	return trueFit;
}


double calculateFitness(long long trueFit)
{
	if (trueFit >= 0) {
		return 1.0 / (trueFit + 1);
	}
	return 1 + abs(trueFit);
}


void searchForBetterNeighbor(BeeProperty &property, BeeProperty &source)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, graph[source.node].size()-1);
	int randomGeneratedNeighbor = distribution(generator);

	property.node = graph[source.node][randomGeneratedNeighbor].first;
	if (property.node < BOUNDARY) {
		property.node = BOUNDARY;
	}
	property.trueFit = calculateTrueFit(property);
	property.fitness = calculateFitness(property.trueFit);

	// new solution better than old one
	if (property.trueFit < source.trueFit) {
		source.node = property.node;
		source.trail = 0;
		source.trueFit = property.trueFit;
		source.fitness = property.fitness;
	}
	else {
		source.trail++;
	}
}


/********************************************/
//           EMPLOYED BEES PHASE
/*********************************************/

void sendEmployedBees() {
	for (int i = 0; i < foodNumber; i++) {
		searchForBetterNeighbor(employedBee[i], nectarSource[i]);
	}
}


/********************************************/
//           ONLOOKER BEES PHASE
/*********************************************/

void sendOnlookerBees() {
	int i = 0;
	int  t = 0;
	std::uniform_real_distribution<double> uniform(0, 1);
	std::default_random_engine re;
	double rateChoosed = uniform(re);
	while (t < foodNumber) {
		// A food source is chosen with the probability
		// which is proportional to its quality
		if (rateChoosed < nectarSource[i].probability) {
			t++;
			searchForBetterNeighbor(onlookerBee[i], nectarSource[i]);
		}
		i++;
		if (i == foodNumber)
		{
			rateChoosed = uniform(re);
			i = 0;
		}
	}
}


/********************************************/
//           SCOUT BEES PHASE
/*********************************************/

void sendScoutBees() {
	for (int i = 0; i < foodNumber; i++) {
		// new source will be generated if trail is greater than maxTrail
		if (nectarSource[i].trail >= maxTrail) {
			std::random_device rd;
			std::mt19937 generator(rd());
			std::uniform_int_distribution<int> distrubutuin(0, graph.size() - 1);

			nectarSource[i].node = distrubutuin(generator);
			nectarSource[i].trail = 0;
			nectarSource[i].trueFit = calculateTrueFit(nectarSource[i]);
			nectarSource[i].fitness = calculateFitness(nectarSource[i].trueFit);
		}
	}
}


void memorizeBestSource() {
	for (int i = 0; i < foodNumber; i++) {
		if (nectarSource[i].trueFit < bestFoodSource.trueFit) {
			bestFoodSource.node = nectarSource[i].node;
			bestFoodSource.trueFit = nectarSource[i].trueFit;
		}
	}
}


void calculateProbabilities() {
	double maxfit = nectarSource[0].fitness;
	for (int i = 1; i < foodNumber; i++) {
		if (nectarSource[i].fitness > maxfit)
		{
			maxfit = nectarSource[i].fitness;
		}
	}
	if (maxfit == 0)
	{
		maxfit = 1;
	}
	for (int i = 0; i < foodNumber; i++) {
		nectarSource[i].probability = 0.9*(nectarSource[i].fitness / maxfit) + 0.1;
	}
}


void beesAlgorithm() {
	std::cout << "Please set foodNumber: ";
	std::cin >> foodNumber;
	std::cout << "Please set maxTrail: ";
	std::cin >> maxTrail;
	auto timeStart = std::chrono::system_clock::now();

	initialize();
	memorizeBestSource();

	int cycle = 0;
	int iterations;
	std::cout << "Please set iterations: ";
	std::cin >> iterations;

	while (cycle < iterations) {
		sendEmployedBees();
		calculateProbabilities();
		sendOnlookerBees();
		memorizeBestSource();
		sendScoutBees();
		memorizeBestSource();
		cycle++;
	}
	auto timeEnd = std::chrono::system_clock::now();

	std::cout << "\nOptimal meeting point is " << bestFoodSource.node << "." << std::endl;
	std::map<int, long long> dijkstraDistances;
	dijkstra(dijkstraDistances, bestFoodSource.node, [](long long x) {return false; });
	std::pair<int, long long> farthest = findFarthest(dijkstraDistances);

	std::cout << "The farthest node is at location: " << farthest.first
						<< ". Distance is: " << farthest.second << ".\n" << std::endl;
	std::cout << " Time = "
	          << std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd-timeStart).count()
	          << " nano sec.\n" << std::endl;
}
