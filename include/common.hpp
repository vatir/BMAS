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
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);

void StripComments(std::string & line);

bool FindHeaderName(std::string & line, std::string & HeaderName);

std::map<std::string, std::vector<std::string>> ParseBMASConfigFile(std::vector<std::string>& ConfigData);

po::variables_map ParseCommandLineArgs(int input_arg_number, char * input_args[]);

std::map<std::string, std::vector<std::string>> ParseConfigData(std::string ConfigFilename);

void PrintConfigData(std::map<std::string, std::vector<std::string>> ConfigSettings);
