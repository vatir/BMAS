#include "graphStructs.hpp"
#include <queue>
#pragma once

class node {
public:
	node();
	node(int num);
	~node();

	int canonical;
	int preorder; 
	std::vector<node*> children; 
	
	
}; 


class tree {
public: 
	tree();
	tree(adjMatrix matrix);
	~tree();
	node* addNode(int num, node* parent); 
	void preOrder(node* start); 
	void buildTree(adjMatrix matrix, int currentNode); 
	bool isBridge(node* start); 
	int nd(node* start); 
	int l(node* start); 
	int h(node* start); 
	node* root = nullptr; 
	node* parent = nullptr;
	int nodes = 0;
	int preorder = 0; 
	bool* isAdded;
	
	
	


};

std::vector<tree> forest; 
