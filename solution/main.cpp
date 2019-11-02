#include "bees_algorithm.hpp"
#include "data_loader.hpp"
#include "halfway_of_farthest_algorithm.hpp"
#include <iostream>
#include <string>


int main(int argc, char *argv[])
{
	std::string answer;
	std::cout << "Please give me path of the graph: ";
	std::cin >> answer;
	loadGraph(answer);

	std::cout << "Please give me path of subset of vertices file: ";
	std::cin >> answer;
	loadSubsetOfVertices(answer);

	while (true)
	{
		std::cout << "Do you want to run halfway of the farthest algorithm?y/n" << std::endl;
		std::cin >> answer;
		if (answer.compare("y") == 0)
		{
			halfwayOfFarthestAlgorithm();
		}
		std::cout << "Do you want to run bees algorithm?y/n" << std::endl;
		std::cin >> answer;
		if (answer.compare("y") == 0)
		{
			beesAlgorithm();
		}
		std::cout << "Do you want to exit?y/n" << std::endl;
		std::cin >> answer;
		if (answer.compare("y") == 0)
		{
			return 0;
		}
		std::cout << "Do you want to give new path of the graph file?y/n" << std::endl;
		std::cin >> answer;
		if (answer.compare("y") == 0)
		{
			std::cout << "Please give me path of the graph file: ";
			std::cin >> answer;
			loadGraph(answer);
		}
		std::cout << "Do you want to give new path of subset of vertices file?y/n" << std::endl;
		std::cin >> answer;
		if (answer.compare("y") == 0)
		{
			std::cout << "Please give me path of subset of vertices file: ";
			std::cin >> answer;
			loadSubsetOfVertices(answer);
		}
	}
}
