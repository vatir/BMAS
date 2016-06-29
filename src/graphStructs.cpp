#include "graphStructs.h"

adjMatrix::adjMatrix(Structure graph)
{
	buildMatrix(graph); 
}

/*
adjMatrix::adjMatrix(adjList list) {
	convert(list); 
} */

adjMatrix::~adjMatrix()
{
	for (int i = 0; i < dim; i++) {
		delete[] matrix;
	}
}

void adjMatrix::buildMatrix(Structure graph) {
	dim = graph.getSize(); 
	
	matrix = new int*[dim]; 

	for (int i = 0; i < dim; i++) {
		matrix[i] = new int[dim];
	}

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			matrix[i][j] = 0; 
		}
	}
	std::vector<Bond> bond = graph.getBonds(); 

	Bond current; 
	std::string node1; 
	std::string node2; 
	numEdges = bond.size(); 
	for (int i = 0; i < bond.size(); i++) {
		current = bond[i];  
		//char(int) seems to convert it strangely, but i don't think it matters for my purposes here bc i just need an unique id
		node1 = current.node1_type + char(current.node1_loc); 
		 
		node2 = current.node2_type + char(current.node2_loc); 

		int pos1 = graph.subunitPositions.find(node1)->second - 1;
		int pos2 = graph.subunitPositions.find(node2)->second - 1;

		
		matrix[pos1][pos2] = 1; 

		if (current.symmetric) {
			matrix[pos2][pos1] = 1;
			numEdges++; 
		}
	}
}

int adjMatrix::getSize() {
	return dim; 
}

int** adjMatrix::getMatrix() {

	return matrix; 
}

int adjMatrix::getNumEdges() {
	return numEdges; 
}

/*
void adjMatrix::convert(adjList list) {
	dim = list.getSize(); 
	std::vector<int>** arrVec = list.getList(); 
	matrix = new int*[dim];

	for (int i = 0; i < dim; i++) {
		matrix[i] = new int[dim];
	}

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < arrVec[i]->size(); j++){
			matrix[i][j] = 1; 
		}
	}
} */

void adjMatrix::printMatrix() {

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			std::cout << matrix[i][j]; 
		}
		std::cout << "" << std::endl; 
	}
}

adjList::adjList(Structure graph) {
	buildList(graph); 
}

adjList::adjList(adjMatrix matrix) {

	convert(matrix);
}

adjList::~adjList() {
	delete[] list; 
}

int adjList::getSize() {
	return dim; 
}

std::vector<int>** adjList::getList() {
	return list; 
}

void adjList::buildList(Structure graph) {
	dim = graph.getSize(); 
	list = new std::vector<int>*[dim]; 

	std::vector<Bond> bond = graph.getBonds();

	Bond current;
	std::string node1;
	std::string node2;
	for (int i = 0; i < bond.size(); i++) {
		current = bond[i];
		//char(int) seems to convert it strangely, but i don't think it matters for my purposes here bc i just need an unique id
		node1 = current.node1_type + char(current.node1_loc);

		node2 = current.node2_type + char(current.node2_loc);

		int pos1 = graph.subunitPositions.find(node1)->second;
		int pos2 = graph.subunitPositions.find(node2)->second;

		list[pos1 - 1]->push_back(pos2); 

		if (current.symmetric) {
			list[pos2 - 1]->push_back(pos1); 
		}
	}

}

void adjList::convert(adjMatrix matrix) {
	dim = matrix.getSize(); 
	list = new std::vector<int>*[dim];
	int** arrays = matrix.getMatrix(); 
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (arrays[i][j]==1){
				list[i]->push_back(j + 1); 
			}
			else {
				continue; 
			}
		}
	}
}
void adjList::printList() {
	/*
	for (int i = 0; i < dim; i++) {
		std::cout << i + 1 << ": ";
		for (int j = 0; j < list[i]->size(); j++) {
			std::cout << list[i][j] << ", ";
		}
		std::cout << "" << std::endl; */
	//}
}