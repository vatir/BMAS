#pragma once
#include "graphStructs.hpp"
#include "nauty.hpp"
#include <unordered_map>
#include <bitset>
#include <algorithm>
#include "tree.h"
class reactions
{
public:
	typedef std::pair<int, int> bridge; 
	
	reactions(Structure graph);
	~reactions();

	void buildMonomerBits(Structure graph);
	void listSubspecies(Structure graph);
	void makeMolecules(Structure graph);
	void print();
	bool search(boost::dynamic_bitset<> query); 
	void findAutomorphisms(Structure graph); 
	bool isAutomorphism(boost::dynamic_bitset<> bitset1, boost::dynamic_bitset<> bitset2);
	bool checkTypes(boost::dynamic_bitset<> bitset1, boost::dynamic_bitset<> bitset2, Structure graph);
	void findBridges(tree current, node* start); 
	void findDisassociations(boost::dynamic_bitset<> bitset);

private:
	std::vector<boost::dynamic_bitset<>> molecules;
	std::vector<boost::dynamic_bitset<>> images;
	std::vector<boost::dynamic_bitset<>> species;
	std::map<boost::dynamic_bitset<>, adjMatrix> bitsetToMatrix;
	std::unordered_map<std::string, std::vector<std::string>> automorphisms; 
	std::unordered_map<std::string, std::vector<bridge>> disassociations; 
	std::vector<bridge> bridges; 
}; 