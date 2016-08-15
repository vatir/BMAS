#pragma once

#include "init.hpp"

class adjMatrix
{
public:
	adjMatrix(); 
	adjMatrix(Structure graph);
	adjMatrix(boost::dynamic_bitset<> bitset, std::vector < boost::dynamic_bitset<>> images); 
	~adjMatrix();
	int** getMatrix(); 
	int getSize(); 
	void buildMatrix(Structure graph);
	void buildMatrix(boost::dynamic_bitset<> bitset, std::vector <boost::dynamic_bitset<>> images); 
	void printMatrix(); 
	int getNumEdges(); 

private: 
	int** matrix;
	int dim; 
	int numEdges; 
}; 



class adjList
{
public: 
	adjList(Structure graph);
	adjList(adjMatrix matrix); 
	~adjList(); 
	int getSize(); 
	std::vector<int>** getList(); 
	void buildList(Structure graph);
	void convert(adjMatrix matrix); 
	void printList(); 
private: 
	std::vector<int>** list; 
	int dim; 


}; 
