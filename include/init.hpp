#pragma once

#include <common.hpp>

class BondType
{
public:
	std::string	name;
	double strength;
	std::string	type;
	void Print();
};
typedef std::map<std::string, BondType > BondTypeMap;

class Bond : public BondType
{
public:
	std::string node1_type;
	int node1_loc;
	std::string node2_type;
	int node2_loc;
	bool symmetric = true;
	void Print();
};

void SubunitParser(std::string & line, std::string & SubunitName, int & SubunitCount);
void BondTypeParser(std::string & line, std::string & type, double & bond_strength, std::string & bond_type);
void BondParser(std::string & line, Bond& bond);

class BitRep
{
public:
	// Member Variables
	boost::dynamic_bitset<> Representation;
	BitsetMap SubunitLocations;
	// Constructor(s)
	BitRep();
	BitRep(int);
	// Destructor(s)
	virtual ~BitRep();
	// Member functions
	void SetSize(int);
	void PrintRepresentation();
	void PrintSubunitLocations();
};

class Structure : public BitRep
{
//friend class BitRep;
public:
	// Member Variables
	std::vector<Bond> bonds;
	BondTypeMap bond_types;
	// Constructor(s)
	Structure();
	Structure(ConfigHolder &);
	// Destructor(s)
	virtual ~Structure();
	// Member functions
	void AddSubunitsFromConfig(StringVector &);
	void AddBondTypesFromConfig(StringVector &);
	void AddBondsFromConfig(StringVector &);

	void PrintBondTypes();
	void PrintBonds();
};
