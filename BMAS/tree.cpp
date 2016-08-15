#include "tree.h"

node::node() {


}

node::node(int num) {
	canonical = num; 

}

node::~node() {

}

tree::tree() {
	forest.push_back(*this); 
}

tree::tree(adjMatrix matrix) {
	forest.push_back(*this); 
	isAdded = new bool(matrix.getSize());
	for (int i = 0; i < matrix.getSize(); i++) {
		isAdded[i] = false; 

	}
}

tree::~tree(){}

node* tree::addNode(int num, node* parent){

	if (parent == nullptr) {
		root = new node(num); 
		root->previous = nullptr; 
		return root;
	}
	else {
		node* tempNode = new node(num); 
		tempNode->previous = parent; 
		parent->children.push_back(tempNode); 
		return tempNode; 

	}

}

void tree::preOrder(node* start){
	start->preorder = preorder; 
	preorder++; 
	for (int i = 0; i < start->children.size(); i++) {
		preOrder(start->children[i]);
	}
}

void tree::buildTree(adjMatrix matrix, int currentNode) {
	int** graph = matrix.getMatrix();
	int index = currentNode;
	int addedNodes; 

	if (nodes < matrix.getSize()-addedNodes) {
		node* temp = addNode(index, parent);
		isAdded[index] = true; 
		nodes++;
		forest[forest.size() - 1] = *this; 

		for (int j = index + 1; j < matrix.getSize(); j++) {
			if (graph[index][j] == 1 && isAdded[j] == false) {
				parent = temp; 
				delete temp;
				buildTree(matrix, j);
			}
			else {
				tree newTree(); 
				parent = nullptr; 
				addedNodes = nodes; 
				nodes = 0; 
				buildTree(matrix, nodes - 1); 
			}

		}

	}
}

bool tree::isBridge(node* start) {

	int ndv = nd(start); 
	int lv= l(start); 
	int hv = h(start); 

	if (lv == start->preorder && hv < start->preorder + ndv) {
		return true; 
	}
	else {
		return false; 
	}




}

int tree::nd(node* start) {
	int ndv; 
	ndv++;
	for (int i = 0; i < start->children.size(); i++) {
		nd(start->children[i]); 

	}
	return ndv-start->children.size(); 
}

int tree::l(node* start) {
	return root->preorder; 
}

int tree::h(node* start) {
	int h = start->preorder; 
	for (int i = 0; i < start->children.size(); i++) {
		preOrder(start->children[i]);
	}

	return h; 
}