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
using namespace std;
namespace po = boost::program_options;


template<class T>
ostream& operator<<(ostream& os, const vector<T>& v);

void StripComments(string & line);

bool FindHeaderName(string & line, string & HeaderName);

map<string, vector<string>> ParseBMASConfigFile(vector<string>& ConfigData);

po::variables_map ParseCommandLineArgs(int input_arg_number, char * input_args[]);

map<string, vector<string>> ParseConfigData(string ConfigFilename);

void PrintConfigData(map<string, vector<string>> ConfigSettings);
