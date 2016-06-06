#pragma once

// --------------------------------------------------
// Quick import of all standard packages
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>

// --------------------------------------------------
// Import Eveything Else
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/random.hpp>
#include <boost/dynamic_bitset.hpp>

// Setup namespaces for easier usage

namespace po = boost::program_options;

template<class T>
std::ostream& operator<<(std::ostream&, const std::vector<T>&);

void SubunitParser(std::string &, std::string &, int &);

void StripComments(std::string &);

bool FindHeaderName(std::string &, std::string &);

std::map<std::string, std::vector<std::string> > ParseBMASConfigFile(std::vector<std::string>&);

po::variables_map ParseCommandLineArgs(int, char * []);

std::map<std::string, std::vector<std::string>> ParseConfigData(std::string);

void PrintConfigData(std::map<std::string, std::vector<std::string> >);
