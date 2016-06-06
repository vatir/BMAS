#include "init.hpp"
using namespace std;


boost::dynamic_bitset<> Representation;
map<string, boost::dynamic_bitset<> > SubunitLocations;

void BitRep::AddSubunitsfromConfig(std::vector<std::string>& SubunitConfig) {
	int TotalSize = 0;
	string CurrentSubunitName;
	int CurrentSubunitCount;

	for (string line : SubunitConfig) {
		SubunitParser(line, CurrentSubunitName, CurrentSubunitCount);
		SubunitLocations[CurrentSubunitName]; // Add entry for subunit
		TotalSize += CurrentSubunitCount;
	}
	SetSize(TotalSize);
}

BitRep::BitRep(std::map<std::string, std::vector<std::string>>& ConfigSettings)
{
	AddSubunitsfromConfig(ConfigSettings["Subunits"]);
}

BitRep::BitRep() {}

BitRep::~BitRep()
{
}

void BitRep::SetSize(int x) {
	Representation.resize(x);
	for (pair<string, boost::dynamic_bitset<> > BS : SubunitLocations) {
		SubunitLocations[BS.first].resize(x); // Don't use the second function as it seems to create a copy, whereas using the first as a get works.
	}
}

void BitRep::PrintRepresentation() {
	cout << "Representation : " << Representation << endl;
}

void BitRep::PrintSubunitLocations() {
	for (pair<string, boost::dynamic_bitset<> > BS : SubunitLocations) {
		cout << "Subunit Locations of type \"" << BS.first << "\" are : " << BS.second << endl;
	}
}
