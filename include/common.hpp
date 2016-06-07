#pragma once

// --------------------------------------------------
// Quick import of all standard packages
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>

// Import Everything Else
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/random.hpp>
#include <boost/dynamic_bitset.hpp>

// Setup namespaces for easier usage
namespace po = boost::program_options;

// Short names for readability, All typedef statements should go here.
typedef std::map<std::string, std::vector<std::string> > ConfigHolder;
typedef std::pair<std::string, std::vector<std::string> > ConfigHolderEntry;
typedef std::vector<std::string> StringVector;
typedef std::map<std::string, boost::dynamic_bitset<> > BitsetMap;
typedef std::pair<std::string, boost::dynamic_bitset<> > BitsetMapEntry;

// ----------------------------------------------------------------------

template<class T>
std::ostream& operator<<(std::ostream&, const std::vector<T>&);

void StripComments(std::string &);

bool FindHeaderName(std::string &, std::string &);

ConfigHolder ParseBMASConfigFile(StringVector&);

po::variables_map ParseCommandLineArgs(int, char * []);

ConfigHolder ParseConfigData(std::string);

void PrintConfigData(ConfigHolder);
