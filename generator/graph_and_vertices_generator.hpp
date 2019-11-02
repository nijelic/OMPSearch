#ifndef GRAPH_AND_VERTICES_GENERATOR_HPP
#define GRAPH_AND_VERTICES_GENERATOR_HPP

#include <string>
#include <utility>

std::pair<int, int> createPair(int, int);

void makeBaseGraph(int, int);
void markEdge(int, int);
void makeItConnected(int, int);
void saveGraph(std::string);
void saveNode(int, int, unsigned);
void saveVertices(std::string, int, int);
#endif
