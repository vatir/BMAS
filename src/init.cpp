#include "init.hpp"
using namespace std;

boost::dynamic_bitset<> Representation;
BitsetMap SubunitLocations;

void BitRep::AddSubunitsfromConfig(StringVector & SubunitConfig) {
	int TotalSize = 0;
	string CurrentSubunitName;
	int CurrentSubunitCount;

	for (auto line : SubunitConfig) {
		SubunitParser(line, CurrentSubunitName, CurrentSubunitCount);
		SubunitLocations[CurrentSubunitName]; // Add entry for subunit
		TotalSize += CurrentSubunitCount;
	}
	SetSize(TotalSize);
}

BitRep::BitRep(ConfigHolder & ConfigSettings)
{
	AddSubunitsfromConfig(ConfigSettings["Subunits"]);
}

BitRep::BitRep() {}

BitRep::~BitRep()
{
}

void BitRep::SetSize(int x) {
	Representation.resize(x);
	for (auto BS : SubunitLocations) {
		SubunitLocations[BS.first].resize(x); // Don't use the second function as it seems to create a copy, whereas using the first as a get works.
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
