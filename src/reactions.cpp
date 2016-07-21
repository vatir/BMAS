#include "reactions.h"



reactions::reactions(Structure graph)
{
	listSubspecies(graph); 
}


reactions::~reactions()
{
}


void reactions::buildMonomerBits(Structure graph) {
	adjMatrix matrix(graph); 

	for (int i = 0; i < graph.getSize(); i++) {
		boost::dynamic_bitset<> bs(graph.getSize());
		boost::dynamic_bitset<> bs2(graph.getSize());
		bs[i] = 1;
		molecules.push_back(bs);
		zero.push_back(0); 
		for (int j = 0; j < graph.getSize(); j++) {
			if (matrix.getMatrix()[i][j] == 1) {
				bs2[j] = 1;
			}
		}
		images.push_back(bs2);
	}

}

void reactions::listSubspecies(Structure graph) {
	buildMonomerBits(graph); 
	makeMolecules(graph); 
	print(); 
	

}

void reactions::makeMolecules(Structure graph) {

	boost::dynamic_bitset<> clashCheck; 
	boost::dynamic_bitset<> imageCheck;  
	boost::dynamic_bitset<> newMolecule; 
	for (int i = 0; i < molecules.size(); i++) {
		for (int j = 0; j <molecules.size(); j++) {
			clashCheck = molecules[i] & molecules[j]; 
			imageCheck = molecules[i] & images[j]; 

			if (clashCheck == zero && (imageCheck > zero)) {
				newMolecule = molecules[i] | molecules[j]; 
				
				if (search(newMolecule) == false) {
					//want to save them as bitsets and structures? bitset key maps to structure?
					molecules.push_back(newMolecule);
					images.push_back(~newMolecule & (images[i] | images[j]));
				}
			}
		}
	}
}


void reactions::print() {
	for (int i = 0; i < molecules.size(); i++) {
		std::cout << molecules[i]<< std::endl; 
		std::cout << images[i] << std::endl; 
		std::cout << " " << std::endl; 
	}
}

bool reactions::search(boost::dynamic_bitset<> query) {

	for (int i = 0; i < molecules.size(); i++) {
			if (molecules[i] == query) {
				return true;
			}
		
	}
	return false; 
}