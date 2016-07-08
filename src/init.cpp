#include "init.hpp"
using namespace std;

void SubunitParser(string& line, string& subunit_name, int& subunit_count)
{
	string result[2];
	boost::regex e("^\\s*(\\S+)\\s*:\\s*(\\d+)\\s*$");
	std::string::size_type sz;   // alias of size_t
	boost::match_results<string::const_iterator> match_results;
	if (boost::regex_match(line, match_results, e, boost::match_all)) {
		subunit_name = match_results[1]; // Value in the first set of parenthesis
		subunit_count = stoi(match_results[2], &sz); // Value in the second set of parenthesis and convert to int 
	}
}

void BondTypeParser(string & line, string & type, double & bond_strength, string & bond_type)
{
	string result[3];
	boost::regex e("^\\s*(\\S+)\\s*:\\s*(\\S+)\\s*\\:\\s*(\\S+)\\s*$");
	std::string::size_type sz;   // alias of size_t
	boost::match_results<string::const_iterator> match_results;
	if (boost::regex_match(line, match_results, e, boost::match_all)) {
		type = match_results[1]; // Value in the first set of parenthesis
		bond_strength = stod(match_results[2], &sz); // Value in the second set of parenthesis and convert to double
		bond_type = match_results[3]; // Value in the third set of parenthesis
	}
}

void BondParser(string & line, Bond & bond)
{
	string result[3];
	boost::regex e("^\\s*([\\w\\d]+)\\s*:\\s*(\\w+)(\\d+)\\s*,\\s*(\\w+)(\\d+)\\s*$");
	boost::match_results<string::const_iterator> match_results;
	std::string::size_type sz;   // alias of size_t
	if (boost::regex_match(line, match_results, e, boost::match_all)) {
		bond.name = match_results[1]; // Value in the first set of parenthesis
		bond.node1_type = match_results[2]; // Value in the second set of parenthesis
		bond.node1_loc = stoi(match_results[3], &sz); // Value in the second set of parenthesis
		bond.node2_type = match_results[4]; // Value in the second set of parenthesis
		bond.node2_loc = stoi(match_results[5], &sz); // Value in the second set of parenthesis
			
	}
}

// --------------------------------- BitRep -------------------------------------------
BitRep::BitRep() {}
BitRep::BitRep(int Size) { SetSize(Size); }

BitRep::~BitRep() {}

void BitRep::SetSize(int x) {
	Representation.resize(x);
	for (auto BS : SubunitLocations) {
		SubunitLocations[BS.first].resize(x); // Don't use the second function as it seems to create a copy, whereas using map.first as a get works.
	}
}

void BitRep::PrintRepresentation() {
	cout << "Representation : " << Representation << endl;
}

void BitRep::PrintSubunitLocations() {
	for (auto BS : SubunitLocations) {
		cout << "Subunit Locations of type \"" << BS.first << "\" are : " << BS.second << endl;
	}
}

// --------------------------------- Structure -------------------------------------------
Structure::Structure() {}
Structure::Structure(ConfigHolder & ConfigSettings)
{
	size = 0;
	AddSubunitsFromConfig(ConfigSettings["Subunits"]);
	AddBondTypesFromConfig(ConfigSettings["BondTypes"]);
	AddBondsFromConfig(ConfigSettings["Bonds"]);
	
}

Structure::~Structure() {}

void Structure::AddSubunitsFromConfig(StringVector & Config) {
	int TotalSize = 0;
	int j = 0;

	string CurrentSubunitName;
	int CurrentSubunitCount;

	for (auto line : Config) {
		SubunitParser(line, CurrentSubunitName, CurrentSubunitCount);
		SubunitLocations[CurrentSubunitName]; // Add entry for subunit
		TotalSize += CurrentSubunitCount;
		string CurrentSubunit;
		
		for (int i = 1; i <= CurrentSubunitCount; i++) {
			j++; 			
			CurrentSubunit = CurrentSubunitName+char(i); 
			subunitPositions[CurrentSubunit] = j; 
		}

	}
	SetSize(TotalSize);
	size = TotalSize; 
	
}

void Structure::AddBondTypesFromConfig(StringVector & Config)
{
	BondType current_bond_type;
	for (auto line : Config) {
		BondTypeParser(
			line,
			current_bond_type.name,
			current_bond_type.strength,
			current_bond_type.type
		);
		bond_types[current_bond_type.name] = current_bond_type;
	}
}

void Structure::AddBondsFromConfig(StringVector & Config)
{

	Bond current_bond;
	for (auto line : Config) {
		BondParser(line, current_bond);
		current_bond.strength = bond_types[current_bond.name].strength;
		current_bond.type = bond_types[current_bond.name].type;
		if (current_bond.type == "Directed") { current_bond.symmetric = false; }
		bonds.push_back(current_bond);
		
		
	}
}

void Structure::PrintBondTypes()
{
	for (auto bond_type : bond_types) {
		bond_type.second.Print();
	}
}

void Structure::PrintBonds()
{
	int i = 1;
	for (auto bond : bonds) {
		cout << endl << "Bond Number: " << i << endl;
		bond.Print();
		i++;
	}
}

int Structure::getSize() {
	return size; 
}

std::vector<Bond> Structure::getBonds() {
	return bonds; 
}

void BondType::Print()
{
	cout
		<< "-----------------------------------" << endl
		<< "Bond Type: " 
		<< name << endl
		<< "Strength: "
		<< strength << endl
		<< "Type: "
		<< type << endl
		;
}

void Bond::Print()
{
	BondType::Print();
	cout
		<< "Node 1: "
		<< node1_type << " : " << node1_loc << endl
		<< "Node 2: "
		<< node2_type << " : " << node2_loc << endl
		;
}
