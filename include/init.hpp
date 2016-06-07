#pragma once

#include <common.hpp>

class BitRep
{
public:
	boost::dynamic_bitset<> Representation;
	BitsetMap SubunitLocations;

	BitRep();
	void AddSubunitsfromConfig(StringVector &);
	BitRep(ConfigHolder &);

	virtual ~BitRep();
	void SetSize(int);
	void PrintRepresentation();
	void PrintSubunitLocations();
};

