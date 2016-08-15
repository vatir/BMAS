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
	findAutomorphisms(graph); 
	std::cout << "" << std::endl; 
	print(); 
	

}

void reactions::makeMolecules(Structure graph) {

	boost::dynamic_bitset<> clashCheck; 
	boost::dynamic_bitset<> imageCheck;
	boost::dynamic_bitset<> imageCheckRev; 
	boost::dynamic_bitset<> newMolecule; 
	std::string tempStr; 

	int currentSize = 2; 
	int z = 0; 
	for (int i = 0; i < molecules.size(); i++) {
		for (int j = 0; j <graph.getSize(); j++) {
			clashCheck = molecules[i] & molecules[j]; 
			imageCheck = molecules[i] & images[j]; 
			imageCheckRev = molecules[j] & images[i]; 

			if (clashCheck.none() == true && ((imageCheck.any() == true) || (imageCheckRev.any() == true))) {
				newMolecule = molecules[i] | molecules[j]; 
				
				if (search(newMolecule) == false) {
					
					molecules.push_back(newMolecule);

					images.push_back(~newMolecule & (images[i] | images[j]));
					adjMatrix matrix2(newMolecule, images); 
					bitsetToMatrix[newMolecule]=matrix2; 


					if (newMolecule.count() != currentSize) {
						
						currentSize = newMolecule.count(); 
					}
					z++; 
				}
			}
		}
	}
	
}


void reactions::print() {
	
	std::string molecule;
	for (int i = 0; i < molecules.size(); i++) {
		
		to_string(molecules[i], molecule);
		std::reverse(molecule.begin(), molecule.end());
		std::cout << molecule<< std::endl; 
		
		
		bitsetToMatrix[molecules[i]].printMatrix(); 
		//std::cout << images[i] << std::endl; 
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



void reactions::findAutomorphisms(Structure graph) {

	int i = 0;
	
	while (i < molecules.size()) {

		int order = molecules[i].count();

		std::vector<std::string> automorphs;
		for (int j = i+1; j < molecules.size(); j++) {
			 
			if (molecules[j].count() == order) {
				if (checkTypes(molecules[i], molecules[j], graph)) {

					if (order == 1) {
						
						std::string bitset;
						std::string bitset2;
						to_string(molecules[i], bitset);
						to_string(molecules[j], bitset2);
						automorphs.push_back(bitset2);
						automorphisms[bitset] = automorphs;
						molecules.erase(molecules.begin() + j); 
						images.erase(images.begin() + j); 
						j--; 

						
					}
					else {
						if (isAutomorphism(molecules[i], molecules[j])) {
							
							std::string bitset;
							std::string bitset2;
							to_string(molecules[i], bitset);
							to_string(molecules[j], bitset2);
							automorphs.push_back(bitset2);
							automorphisms[bitset] = automorphs;
							molecules.erase(molecules.begin() + j);
							images.erase(images.begin() + j); 
							j--; 
							

							
						}
						else {
							continue;
						}
					}
				}

			}			
		}
		
		i++; 
	}
}


bool reactions::isAutomorphism(boost::dynamic_bitset<> bitset1, boost::dynamic_bitset<> bitset2) {
	
	
	nauty_graph cg1;
	nauty_graph cg2;
	nauty_graph tg1(bitsetToMatrix.find(bitset1)->second); 
	nauty_graph tg2(bitsetToMatrix.find(bitset2)->second); 
	nauty_env workspace;
	workspace.SetSize(bitset1.count()); 
	cg1.SetSize(bitset1.count()); 
	cg2.SetSize(bitset2.count()); 

	workspace.GetCanonical(tg2, cg2); 
	workspace.GetCanonical(tg1, cg1); 

	int k;
	for (k = 0; k < workspace.m*(size_t)workspace.n; ++k)
		if (cg1.cg[k] != cg2.cg[k]) break;
	if (k == workspace.m*(size_t)workspace.n)
	{
		return true;
	}
	else {
		return false;
	}
} 

bool reactions::checkTypes(boost::dynamic_bitset<> bitset1, boost::dynamic_bitset<> bitset2, Structure graph) {

	std::string bitset1Types = ""; 
	std::string bitset2Types = ""; 

	for (int i = 0; i < bitset1.size(); i++) {
		if (bitset1[i] == 1) {
			bitset1Types = bitset1Types + graph.subunits[i];
		}

		if (bitset2[i] == 1) {
			bitset2Types = bitset2Types + graph.subunits[i]; 
		}
		
	}

	if (bitset2Types != bitset1Types) {
		return false; 
	}
	else {
		return true; 
	}
} 

/*
void reactions::findDisassociations(boost::dynamic_bitset<> bitset) {
	adjMatrix graph = bitsetToMatrix[bitset];
	tree disassocs(graph);
	disassocs.buildTree(graph, 0);
	
	for (int i = 0; i < forest.size(); i++) {
		for(int j=0; j < forest[i].root->children.size(); j++)
		findBridges(forest[i], forest[i].root->children[j]);
	}

	std::string temp; 
	to_string(bitset, temp); 
	disassociations[temp] = bridges; 
}
*//*
void reactions::findBridges(tree current,node* start) {
	
	if (current.isBridge(start) == true) {
		bridge newBridge(start->previous->canonical, start->canonical); 
		bridges.push_back(newBridge); 
	}
	for (int i = 0; i < start->children.size(); i++) {
		findBridges(current, start->children[i]);
	}
}*/

