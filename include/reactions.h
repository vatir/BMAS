#pragma once
#include "graphStructs.hpp"
class reactions
{
public:
	reactions(Structure graph);
	~reactions();

	void buildMonomerBits(Structure graph);
	void listSubspecies(Structure graph);
	void makeMolecules(Structure graph); 
	void print(); 
	bool search(boost::dynamic_bitset<>); 

private: 
	std::vector<boost::dynamic_bitset<>> molecules; 
	std::vector<boost::dynamic_bitset<>> images; 
	std::vector<boost::dynamic_bitset<>> species; 
	boost::dynamic_bitset<> zero; 
};

