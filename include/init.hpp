#pragma once

#include <common.hpp>

class BitRep
{
public:
	boost::dynamic_bitset<> Representation;
	std::map<std::string, boost::dynamic_bitset<> > SubunitLocations;

	BitRep();
	void AddSubunitsfromConfig(std::vector<std::string>&);
	BitRep(std::map<std::string, std::vector<std::string> >&);

	virtual ~BitRep();
	void SetSize(int);
	void PrintRepresentation();
	void PrintSubunitLocations();
};

